import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout, CMakeDeps
from conan.tools.build import check_min_cppstd
from conan.tools.files import rmdir, copy


class RollyRecipe(ConanFile):
    name = "rolly"
    version = "2.6.6"
    description = "Radar open-source library"
    author = "whs31 <whs31@github.io>"
    topics = ("coreutils", "utility")

    settings = "os", "arch", "compiler", "build_type"
    options = {
        "shared": [True, False],
        "test": [True, False],
        "serde": [True, False]
    }
    default_options = {
        "shared": True,
        "test": False,
        "serde": True
    }
    exports = "CMakeLists.txt", "conanfile.py"
    exports_sources = "*", "!build/*"

    @property
    def _min_cppstd(self):
        return "17"

    def requirements(self):
        self.requires("fmt/10.2.1", transitive_headers=True, transitive_libs=True)
        self.requires("ipaddress/1.1.0", transitive_headers=True, transitive_libs=True)
        self.requires("nlohmann_json/[>=3.11.3]", transitive_headers=True, transitive_libs=True)
        if self.settings.os != "Windows":
            self.requires("libuuid/1.0.3")
        if self.options.test:
            self.requires("catch2/[=3.7.1]")

    def layout(self):
        cmake_layout(self)

    def validate(self):
        if self.settings.get_safe("compiler.cppstd"):
            check_min_cppstd(self, self._min_cppstd)

    def configure(self):
        self.options["fmt/*"].shared = self.options.shared

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.cache_variables["BUILD_SHARED_LIBS"] = self.options.shared
        tc.cache_variables["ROLLY_TESTS"] = self.options.test
        tc.cache_variables["ROLLY_SERDE"] = self.options.serde
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "res"))
        rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "rolly")
        self.cpp_info.set_property("cmake_target_name", "rolly::rolly")
        self.cpp_info.libs = ["rolly"]
        self.cpp_info.requires = ["fmt::fmt", "ipaddress::ipaddress",
                                  "nlohmann_json::nlohmann_json"]
        if self.settings.os != "Windows":
            self.cpp_info.requires.append("libuuid::libuuid")
        if self.options.test:
            self.cpp_info.requires.append("catch2::catch2")
        if not self.options.shared:
            self.cpp_info.defines = ["ROLLY_STATIC_LIBRARY"]
        if self.options.serde:
            self.cpp_info.defines = ["ROLLY_SERDE"]
