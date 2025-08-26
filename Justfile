import '.just/modules.just'

alias v := version

default:
    @echo "Usage: just <command> [options]"
    @just --list

set unstable := true
set script-interpreter := ['uv', 'run', '--script']

[positional-arguments]
[script]
[working-directory('.')]
version *ARGS:
    # /// script
    # requires-python = ">=3.11"
    # dependencies=["just-utils", "semver"]
    #
    # [tool.uv.sources]
    # just-utils = { git = "https://github.com/whs31/just-utils", branch = "main" }
    # ///

    import os
    import sys
    import argparse
    import semver
    import just_utils as ju

    parser = argparse.ArgumentParser()
    parser.add_argument("-s", "--show", action="store_true")
    parser.add_argument("-a", "--assign", type=str, help="version to patch")
    parser.add_argument("-p", "--bump-patch", action="store_true")
    parser.add_argument("-m", "--bump-minor", action="store_true")
    parser.add_argument("-M", "--bump-major", action="store_true")
    args = parser.parse_args()

    if args.show:
      ju.show_version()
      sys.exit(0)

    if args.assign:
      ju.patch_version(semver.Version.parse(args.assign))
      sys.exit(0)

    if args.bump_patch:
      ju.bump_version_patch()
      sys.exit(0)

    if args.bump_minor:
      ju.bump_version_minor()
      sys.exit(0)

    if args.bump_major:
      ju.bump_version_major()
      sys.exit(0)