[script]
[working-directory('../..')]
show:
    # /// [script]
    # requires-python = ">=3.11"
    # dependencies=["termcolor", "pyyaml"]
    # ///

    import os
    import sys
    import re
    import yaml
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

    def read_version_header(config: Config):
      def extract_define(line: str, prefix: str, suffix: str) -> str:
        return re.search(fr'#\s*define\s+{prefix}_VERSION_{suffix}\s+(\d+)', line).group(1)

      if not config.version_header['enabled']:
        return None

      try:
        prefix = config.version_header['macro_prefix']
        with open(config.version_header['path'], "r") as f:
          lines = f.readlines()
          for i, line in enumerate(lines):
            if re.search(fr'#\s*define\s+{prefix}_VERSION_MAJOR\s+(\d+)', line):
              major = extract_define(line, prefix, "MAJOR")
            if re.search(fr'#\s*define\s+{prefix}_VERSION_MINOR\s+(\d+)', line):
              minor = extract_define(line, prefix, "MINOR")
            if re.search(fr'#\s*define\s+{prefix}_VERSION_PATCH\s+(\d+)', line):
              patch = extract_define(line, prefix, "PATCH")
          return f"{major}.{minor}.{patch}"
      except Exception as e:
        cprint(f"Error reading version header: {e}", "yellow")
        return None

    def extract_semver_impl(string: str) -> str:
      return re.search(r"(\d+\.)?(\d+\.)?(\*|\d+)", string).group(0)

    def extract_semver(path: pathlib.Path, regex: str) -> str:
      try:
        with open(path, "r") as f:
          lines = f.readlines()
          for i, line in enumerate(lines):
            if re.search(regex, line) and not line.startswith("cmake_"):
              return extract_semver_impl(line)
      except Exception as e:
        cprint(f"Error reading {path}: {e}", "yellow")
        return None


    def main():
      CONFIG_PATH = pathlib.Path('./.versionrc.yml')
      if not CONFIG_PATH.exists() or not CONFIG_PATH.is_file():
        cprint("Config file not found. Place .versionrc.yml in the root directory.", "red")
        return 1

      config = Config(CONFIG_PATH)

      def print_version(name: str, version):
        if version is None:
          cprint(f"- {name:<30}: not found", "yellow")
        else:
          cprint(f"- {name:<30}: {version}", "green")

      if config.version_header['enabled']:
        print_version(config.version_header['fullname'], read_version_header(config))
      print_version("CMakeLists.txt", extract_semver(pathlib.Path("./CMakeLists.txt"), r"VERSION (\d+\.)?(\d+\.)?(\*|\d+)"))
      print_version("conanfile.py", extract_semver(pathlib.Path("./conanfile.py"), r"version\s*=\s*\"(.*)\""))


    if __name__ == "__main__":
      sys.exit(main())

