#!/usr/bin/env python3

import json
import logging
import argparse
import configparser

from pathlib import Path
from typing import Optional, Iterable, TypeAlias, Tuple


FeaturePack: TypeAlias = str
BinaryPath: TypeAlias = str


def read_manifest(
    in_path: Path,
    base_dir: Path
) -> Iterable[Tuple[FeaturePack, BinaryPath]]:
    with open(in_path) as in_file:
        manifest = json.load(in_file)

    for features, binary in manifest.items():
        resolved = Path(binary).relative_to(base_dir) 
        yield features, f'res://{resolved}'


def gdextension_config(
    output_path: Path,
    binaries: Iterable[Tuple[FeaturePack, BinaryPath]],
    entry_symbol: str,
    compatibility_minimum: str,
    compatibility_maximum: Optional[str],
    reloadable: bool
):
    parser = configparser.ConfigParser()

    # script is invoked per-configuration, so in multi-config scenario
    # we just add manifest diff to libraries section
    if output_path.is_file():
        logging.info('found configuration: only updating libraries')
        parser.read(output_path)

        for features, binary in binaries:
            if features not in parser['libraries']:
                parser['libraries'][features] = f'"{binary}"'

    else:
        parser['configuration'] = {
            'entry_symbol': f'"{entry_symbol}"',
            'compatibility_minimum': compatibility_minimum,
            'reloadable': str(reloadable).lower()
        }

        if compatibility_maximum is not None:
            parser['configuration']['compatibility_maximum'] = compatibility_maximum

        parser['libraries'] = {
            features: f'"{binary}"' for features, binary in binaries
        }

    with open(output_path, 'w') as out_file:
        logging.info(f'writing gdextension configuration: {output_path.stem}')
        parser.write(out_file)

    
def main():
    parser = argparse.ArgumentParser(description='Utility for generating dynamic gdextension configurations')
    parser.add_argument('--manifest', type=Path, required=True, help='path to input manifest.json')
    parser.add_argument('--base-dir', type=Path, required=True, help='base game directory')
    parser.add_argument('--output', type=Path, required=True, help='path to output .gdextension file')
    parser.add_argument('--entry-symbol', type=str, required=True, help='entry symbol for the extension')
    parser.add_argument('--compat-min', type=str, required=True, help='minimum Godot compatibility version')
    parser.add_argument('--compat-max', type=str, help='maximum Godot compatibility version')
    parser.add_argument('--reloadable', action='store_true', help='set shared library as reloadable')

    args = parser.parse_args()
    
    libraries = read_manifest(args.manifest, args.base_dir)
    gdextension_config(
        output_path=args.output,
        binaries=libraries,
        entry_symbol=args.entry_symbol,
        compatibility_minimum=args.compat_min,
        compatibility_maximum=args.compat_max,
        reloadable=args.reloadable
    )


if __name__ == '__main__':
    main()
