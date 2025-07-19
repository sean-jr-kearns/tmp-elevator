from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy as conan_copy
import os

class Elevator(ConanFile):
    name = "elevator"
    version = "1.0.2"

    settings = "os", "compiler", "build_type", "arch"
    
    options = {
        "with_tests": [True, False],
    }
    default_options = {
        "with_tests": False,
    }
    
    generators = "CMakeDeps"
    exports_sources = "CMakeLists.txt", "src/*", "tests/*"
    test_type = "explicit"
    
    def requirements(self):
        self.requires("spdlog/1.15.0")
        if self.options.with_tests:
            self.requires("gtest/1.15.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        # Ensure CMake installs to Conan's package folder
        tc.cache_variables["CMAKE_INSTALL_PREFIX"] = self.package_folder
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(variables={"WITH_TESTS": self.options.with_tests})
        cmake.build()
        
        if self.options.with_tests:
            self.run("ctest --output-on-failure", cwd=self.build_folder)

    def test(self):
        if not self.conf.get("tools.build:skip_test", default=False):
            self.run("ctest --output-on-failure", cwd=self.build_folder)

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["main"]
        
    def deploy(self):
        conan_copy(self, "*", 
            src=os.path.join(self.package_folder, "bin"), 
            dst=os.path.join(self.deploy_folder, "bin"))

        conan_copy(self, "*.a", 
            src=os.path.join(self.package_folder, "lib"), 
            dst=os.path.join(self.deploy_folder, "lib"))
        
        conan_copy(self, "*.hpp", 
            src=os.path.join(self.package_folder, "include"), 
            dst=os.path.join(self.deploy_folder, "include"))
        
