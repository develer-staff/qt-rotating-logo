#!/usr/bin/env python3
#
# script/build.py - Build script.
#

import argparse
import contextlib
import os
import multiprocessing
import pathlib
import shutil
import subprocess
import sys

TOP_LEVEL = pathlib.Path(__file__).parent.parent

DEFAULT_BUILD_DIR = "build"
DEFAULT_CMAKE_PRESET = "default-linux"


def main():
    args = parse_args()

    cmake_preset = args.preset  # type: str
    build_dir = TOP_LEVEL / args.build_dir  # type: pathlib.Path
    if (jobs := args.jobs) <= 0:
        jobs = multiprocessing.cpu_count()

    # Diagnostics
    print("Build directory:", build_dir)
    print("CMake preset:", cmake_preset)
    print("Jobs:", jobs)

    # Clean?
    if args.clean and build_dir.exists():
        shutil.rmtree(build_dir)

    # Create build directory
    build_dir.mkdir(exist_ok=True)

    # Configure
    call(
        "cmake",
        "--preset",
        cmake_preset,
        "-S",
        str(TOP_LEVEL),
        "-B",
        str(build_dir),
    )

    # Build
    call("cmake", "--build", str(build_dir), "--", f"-j{jobs}")

    # Test
    with chdir(build_dir):
        call("ctest", "--output-on-failure")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("-d", "--build_dir", type=str, default=DEFAULT_BUILD_DIR)
    parser.add_argument("-c", "--clean", action="store_true")
    parser.add_argument("-p", "--preset", default=DEFAULT_CMAKE_PRESET)
    parser.add_argument("-j", "--jobs", type=int, default=0)

    return parser.parse_args()


def call(*args: str) -> int:
    print()
    print("[call]", *args)
    print()
    return subprocess.check_call(args)


@contextlib.contextmanager
def chdir(path: pathlib.Path):
    oldcwd = os.getcwd()
    try:
        os.chdir(path)
        yield
    finally:
        os.chdir(oldcwd)


if __name__ == "__main__":
    main()
