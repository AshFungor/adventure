#!/usr/bin/env python3

import json
import argparse

from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description='update manifest with new build configuration')
    parser.add_argument('key', help='feature pack to set (essentially build configuration name, composed of parameters)')
    parser.add_argument('value', help='absolute path to binary file')
    parser.add_argument('output_file', type=Path, help='path to manifest.json')
    args = parser.parse_args()

    if args.output_file.is_file():
        with open(args.output_file, 'r') as manifest_file:
            manifest = json.load(manifest_file)
    else:
        manifest = {}

    manifest[args.key] = args.value

    with open(args.output_file, 'w') as manifest_file:
        json.dump(manifest, manifest_file, indent=4)


if __name__ == "__main__":
    main()
