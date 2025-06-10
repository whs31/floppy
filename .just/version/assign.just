[positional-arguments]
[script]
[working-directory('../..')]
assign *ARGS:
    # /// [script]
    # requires-python = ">=3.11"
    # dependencies=["termcolor", "pyyaml"]
    # ///

    import os
    import sys
    import re
    import yaml
    import argparse
    import pathlib
    from termcolor import colored, cprint

    class Config:
      def __init__(self, path: pathlib.Path):
        with open(path) as f:
          self.__config = yaml.safe_load(f)
          self.version_header = dict()
          self.version_header['enabled'] = self.__config['config']['version_header']['enabled']
          if self.version_header['enabled']:
            self.version_header['path'] = pathlib.Path(self.__config['config']['version_header']['path'])
            self.version_header['stem'] = self.version_header['path'].stem
            self.version_header['fullname'] = f"{self.version_header['path'].stem}{self.version_header['path'].suffix}"
            self.version_header['macro_prefix'] = self.__config['config']['version_header']['macro_prefix']

      def __str__(self):
        return str(self.__config)

    def strip_version(version: str) -> str:
      """
      Strips version from "X.Y.Z[.*]" to "X.Y.Z"
      :param version: specified version
      :return: stripped version
      """
      sp = version.split(".")[0:3]
      return f"{sp[0]}.{sp[1]}.{sp[2]}"

    def patch_cmake(version: str, path: pathlib.Path):
      cprint(f'- patching CMakeLists.txt ({version})', "cyan")
      try:
        with open(path, "r") as f:
          lines = f.readlines()
          for i, line in enumerate(lines):
            if re.search(r"VERSION (\d+\.)?(\d+\.)?(\*|\d+)", line) and not line.startswith("cmake_"):
              lines[i] = re.sub(r"VERSION (\d+\.)?(\d+\.)?(\*|\d+)", f"VERSION {version}", line)
          with open(path, "w") as f:
            f.writelines(lines)
      except FileNotFoundError:
        raise FileNotFoundError(f"File not found in {path}")


    def patch_conanfile(version: str, path: pathlib.Path):
      cprint(f'- patching conanfile.py ({version})', "cyan")
      try:
        with open(path, "r") as f:
          lines = f.readlines()
          for i, line in enumerate(lines):
            if re.search(r"version\s*=\s*\"(.*)\"", line):
              lines[i] = re.sub(r"version\s*=\s*\"(.*)\"", f"version = \"{version}\"", line)
          with open(path, "w") as f:
            f.writelines(lines)
        return True
      except FileNotFoundError:
        raise FileNotFoundError(f"File not found in {path}")

    def patch_include_version(version: str, config: Config) -> None:
      try:
        cprint(f'- patching {config.version_header["fullname"]} ({version})', "cyan")
        prefix = config.version_header['macro_prefix']
        major = version.split(".")[0]
        minor = version.split(".")[1]
        patch = version.split(".")[2]
        with open(config.version_header['path'], "r") as f:
          lines = f.readlines()
          for i, line in enumerate(lines):
            if re.search(fr'#\s*define\s+{prefix}_VERSION_MAJOR\s+(\d+)', line):
              lines[i] = re.sub(fr'#\s*define\s+{prefix}_VERSION_MAJOR\s+(\d+)',
                                f'#define {prefix}_VERSION_MAJOR {major}', line)
            if re.search(fr'#\s*define\s+{prefix}_VERSION_MINOR\s+(\d+)', line):
              lines[i] = re.sub(fr'#\s*define\s+{prefix}_VERSION_MINOR\s+(\d+)',
                                f'#define {prefix}_VERSION_MINOR {minor}', line)
            if re.search(fr'#\s*define\s+{prefix}_VERSION_PATCH\s+(\d+)', line):
              lines[i] = re.sub(fr'#\s*define\s+{prefix}_VERSION_PATCH\s+(\d+)',
                                f'#define {prefix}_VERSION_PATCH {patch}', line)
          with open(config.version_header['path'], "w") as f:
            f.writelines(lines)
      except FileNotFoundError:
        raise FileNotFoundError(f"File not found in {config.version_header['path']}")


    def main():
      parser = argparse.ArgumentParser()
      parser.add_argument("version", type=str, help="version to patch")
      args = parser.parse_args()

      CONFIG_PATH = pathlib.Path('./.versionrc.yml')
      if not CONFIG_PATH.exists() or not CONFIG_PATH.is_file():
        cprint("Config file not found. Place .versionrc.yml in the root directory.", "red")
        return 1

      config = Config(CONFIG_PATH)
      try:
        sversion = strip_version(args.version)
        version = args.version
        patch_cmake(sversion, pathlib.Path("./CMakeLists.txt"))
        patch_conanfile(version, pathlib.Path("./conanfile.py"))
        if config.version_header['enabled']:
          patch_include_version(sversion, config)
        return 0
      except Exception as e:
        cprint(f"Error: {e}", "red")
        return 1

    if __name__ == "__main__":
      sys.exit(main())
