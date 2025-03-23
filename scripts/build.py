#!/usr/bin/env python3

import os
import sys
import errno
import shutil
import typing
import inspect
import argparse
import subprocess
import multiprocessing

from pathlib import Path
from dataclasses import dataclass, field
from typing import Callable, Iterable, Union, Tuple

DESCRIPTION = '''
    CLI build helper for Dead Tomato.
'''


@dataclass
class Config:
    build_directory: Path = field(default_factory=lambda: Path.cwd().joinpath('build'))
    build_configs: Iterable[str] = field(default_factory=lambda: ['Debug'])
    cores: int = multiprocessing.cpu_count()
    profile: Union[Path, str] = 'default'
    generator: str = 'Ninja'


def routine(priority: int) -> Callable:
    def decorator(method):
        method.priority = priority
        method.is_routine = True
        return method

    return decorator


class Routines:
    def __init__(self, params: Config):
        self.__params = params

    def routines(self) -> Iterable[Tuple[str, Callable]]:
        def key(pair):
            _, member = pair
            return member.priority if hasattr(member, 'priority') else 0

        members = inspect.getmembers(self, predicate=inspect.ismethod)
        for name, method in sorted(members, key=key, reverse=True):
            if hasattr(method, 'is_routine'):
                yield name, method

    @routine(5)
    def remove(self):
        for config in self.__params.build_configs:
            directory = self.__params.build_directory.joinpath(config)
            if directory.is_dir():
                print(f'removing directory for CMake build config \'{config}\'')
                shutil.rmtree(directory)
            else:
                print(f'build directory for config \'{config}\' was not found or was not a directory')

    @routine(4)
    def conan_install(self):
        print(f'running Conan install command')
        self.__run([
            'conan',
            'install',
            '--build=missing',
            f'-pr:a={self.__params.profile}',
            str(Path.cwd())
        ])

    @routine(3)
    def configure(self):
        if not self.__params.build_directory.is_dir():
            self.__params.build_directory.mkdir()

        use_presets = Path.cwd().joinpath('CMakeUserPresets.json').is_file()
        print('configuring for CMake build configs: ' + ', '.join(self.__params.build_configs))

        for config in self.__params.build_configs:
            source = Path.cwd()
            binary = self.__params.build_directory.joinpath(config)
            command = [
                'cmake',
                # TODO: handle conan configs differently in
                # multi-config scenario
                '--preset', f'conan-{config.lower()}',
                '-G', self.__params.generator,
                '-B', str(binary),
                '-S', str(source),
                self.__decorate_cmake_variable('CMAKE_EXPORT_COMPILE_COMMANDS', 'ON', 'BOOL'),
                self.__decorate_cmake_variable('CMAKE_BUILD_TYPE', config)
            ] if use_presets else [
                'cmake',
                '-G', self.__params.generator,
                '-B', str(binary),
                '-S', str(source),
                self.__decorate_cmake_variable('CMAKE_EXPORT_COMPILE_COMMANDS', 'ON', 'BOOL'),
                self.__decorate_cmake_variable('CMAKE_BUILD_TYPE', config)
            ]

            print(f'running configure command for CMake config {config}')
            self.__run(command)

    @routine(2)
    def build(self):
        if not self.__params.build_directory.is_dir():
            sys.exit(f'build directory \'{self.__params.build_directory}\' was not found')

        print(f'using {self.__params.cores} threads')
        for config in self.__params.build_configs:
            directory = self.__params.build_directory.joinpath(config)
            print(f'building for CMake configuration \'{config}\'')
            self.__run([
                'cmake',
                '--build', str(directory),
                '--parallel', str(self.__params.cores)
            ])

    @routine(1)
    def symlink_compile_commands(self: 'Routines') -> None:
        if 'Debug' in self.__params.build_configs:
            path = self.__params.build_directory.joinpath('Debug').joinpath('compile_commands.json')
            print(f'creating symlink for path \'{path}\'')

        if 'Release' in self.__params.build_configs:
            path = self.__params.build_directory.joinpath('Release').joinpath('compile_commands.json')
            print(f'creating symlink for path \'{path}\'')

        if path is None:
            sys.exit('no supported CMake configs detected')

        symlink = Path.cwd().joinpath('compile_commands.json')
        if symlink.is_symlink():
            symlink.unlink()

        Path.cwd().joinpath('compile_commands.json').symlink_to(path)

    def __run(self: 'Routines', command: typing.List[str]) -> None:
        print('running command: ' + ' '.join(command))
        code = subprocess.run(command, encoding='UTF-8', stderr=subprocess.STDOUT, env=os.environ).returncode
        if code:
            sys.exit(f'error: subprocess failed: {errno.errorcode[code]} (code: {code})')

    def __decorate_cmake_variable(self: 'Routines', var: str, value: str, type: Union[str, None] = None) -> str:
        if type is not None:
            return f'-D{var.upper()}:{type}={value}'
        return f'-D{var.upper()}={value}'


def parse_cli_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=DESCRIPTION, formatter_class=argparse.RawDescriptionHelpFormatter)
    # Routines
    parser.add_argument('-b', '--build', action='store_true', dest='build')
    parser.add_argument('-c', '--configure', action='store_true', dest='configure')
    parser.add_argument('-i', '--conan-install', action='store_true', dest='conan_install')
    parser.add_argument('-r', '--remove', action='store_true', dest='remove')
    parser.add_argument('-l', '--symlink-compile-commands', action='store_true', dest='symlink_compile_commands')
    # Environment
    parser.add_argument('--build-dir', action='store', dest='build_directory')
    parser.add_argument('--config', action='append', dest='configs', choices=['Debug', 'Release'])
    parser.add_argument('--parallel', action='store', dest='cores')
    parser.add_argument('--generator', action='store', dest='generator')
    parser.add_argument('--profile', action='store', dest='profile')
    return parser.parse_args()


def main():
    args = parse_cli_args()

    params = Config()
    if getattr(args, 'build_directory') is not None:
        params.build_directory = Path.cwd().joinpath(args.build_directory)
        print(f'config: user-provided build directory: \'{params.build_directory}\'')
    if getattr(args, 'configs') is not None:
        params.build_configs = args.configs
        print(f'config: user-provided build configs: \'{params.build_directory}\'')
    if getattr(args, 'cores') is not None:
        params.cores = int(args.cores)
        print(f'config: user-provided threads, that will be run in parallel: \'{params.cores}\'')
    if getattr(args, 'profile') is not None:
        params.profile = args.profile
        print(f'config: user-provided conan profile: \'{params.profile}\'')
    if getattr(args, 'generator') is not None:
        params.generator = args.generator
        print(f'config: user-provided generator: \'{params.generator}\'')

    r = Routines(params)
    for routine, f in r.routines():
        if not hasattr(args, routine):
            print(f'routine \'{routine}\' is not configured for CLI, skipping')
            continue
        if getattr(args, routine):
            print(f'running {routine}')
            f()

    print('done!')


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('exited by user')
