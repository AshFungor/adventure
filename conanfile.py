import typing

from conan import ConanFile
from conan.tools.cmake import cmake_layout


class AdventureGame(ConanFile):
    generators: typing.List[str] = ['CMakeToolchain', 'CMakeDeps']
    settings: typing.List[str] = ['os', 'compiler', 'build_type', 'arch']

    def __init__(self: typing.Self, display_name: str = '') -> None:
        self._requirements = {
            'plog': '1.1.10',
            'gtest': '1.14.0',
            'nlohmann_json': '3.11.3',
            'boost': '1.85.0'
        }
        super().__init__(display_name)

    def requirements(self: typing.Self) -> None:
        for req, version in self._requirements.items():
            self.requires(f'{req}/{version}')

    def layout(self):
        cmake_layout(self)
