#!/usr/bin/env python3
#
# script/print-version.py - Prints a computed version number.
#
# If this script exits successfully (status code zero), it MUST print a version number and ONLY a
# version number.
#
# The script can print anything if it exits with a non-zero status code.
#
# VERSIONING LOGIC:
#
# Git tags must be in the format "MAJOR.MINOR.PATCH.MICRO".
#
# If we are building a tag then the final version number is the tag itself.
#
# In all other cases we use "0.0.0.0".

import re
import subprocess
import sys
import typing

# https://learn.microsoft.com/en-us/windows/win32/msi/productversion
RE_VERSION = re.compile(r"\d{1,3}\.\d{1,3}\.\d{1,5}\.\d{1,10}")


def main():
    version = git_describe_tags()
    if version is None:
        version = "0.0.0.0"

    if not RE_VERSION.fullmatch(version):
        print(f"Invalid version: {version}")
        sys.exit(1)

    print(version, end=None)


def git_describe_tags() -> typing.Optional[str]:
    try:
        # Either we are exactly on a tagged commit...
        return output("git", "describe", "--exact-match", "--tags")
    except subprocess.CalledProcessError:
        # ... or we don't (or another error occurred - unfortunately we can't easily distinguish
        # between not being on a tag or getting another error without parsing the error message
        # itself).
        return None


def output(*args: str) -> str:
    return subprocess.check_output(args, encoding="utf-8").strip()


if __name__ == "__main__":
    main()
