alias v := version

default:
    @echo "Usage: just <command> [options]"
    @just --list

graph:
    conan graph info . --format=html > graph.html
    mkdir -p docs
    mv graph.html docs

version *ARGS='--show':
    @wucc version {{ ARGS }}

set unstable := true
set script-interpreter := ['uv', 'run', '--script']

[script]
clean:
    # /// [script]
    # requires-python = ">=3.11"
    # ///
    import os
    import shutil

    if os.path.exists("target"):
        shutil.rmtree("target")
    if os.path.exists("build"):
        shutil.rmtree("build")
    if os.path.exists("CMakeUserPresets.json"):
        os.remove("CMakeUserPresets.json")

[positional-arguments]
[script]
build *ARGS:
    # /// script
    # requires-python = ">=3.11"
    # dependencies=["just-utils", "termcolor", "pyyaml"]
    #
    # [tool.uv.sources]
    # just-utils = { git = "https://github.com/whs31/just-utils", branch = "main" }
    # ///
    import os
    import sys
    import argparse
    from pathlib import Path
    from termcolor import cprint, colored
    from just_utils import ConanFileMetadata, Conan, Manifest, default_cmake_parser, clean_build_directory

    parser = default_cmake_parser(["test"])
    args, conan_args = parser.parse_known_args()

    meta = ConanFileMetadata(Path('.').parent / "conanfile.py")
    meta.pretty_print(args.verbose)

    def print_arg(name, value, color="yellow"):
        arg = colored(f"{value}", color, attrs=["bold"])
        print(f"{name:<25}: {arg:<25}")

    print_arg("build_type", args.build, "green")
    print_arg("verbose", args.verbose, "cyan")
    print_arg("configure", args.configure, "cyan")
    print_arg("clean", args.clean, "red")
    print()
    cprint(f"conan args: {' '.join(conan_args)}", "magenta")

    conan = Conan(meta.name, args.build, args.verbose)
    if args.clean:
        conan.clean()
    conan.run("install" if args.configure else "build", {
      "test": args.test
    }, conan_args)
    conan.fix_presets()
    cprint("done", "green")
