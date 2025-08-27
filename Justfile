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

    actions = {
        args.show: ju.show_version,
        args.assign: lambda: ju.patch_version(semver.Version.parse(args.assign)),
        args.bump_patch: ju.bump_version_patch,
        args.bump_minor: ju.bump_version_minor,
        args.bump_major: ju.bump_version_major,
    }

    for key, fn in actions.items():
        if key:
            fn()
            sys.exit(0)
