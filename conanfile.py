from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy as conan_copy
import os

class Elevator(ConanFile):
    name = "elevator"
    version = "1.0.0"

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    exports_sources = "CMakeLists.txt", "src/*", "tests/*"
    requires = "gtest/1.14.0"
    test_type = "explicit"

    def layout(self):
        cmake_layout(self)
        # Optional: explicitly set where libs and includes go
        #self.cpp.package.libdirs = ["lib"]
        #self.cpp.package.includedirs = ["include"]

    def generate(self):
        tc = CMakeToolchain(self)
        # Ensure CMake installs to Conan's package folder
        tc.cache_variables["CMAKE_INSTALL_PREFIX"] = self.package_folder
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if not self.conf.get("tools.build:skip_test", default=False):
            self.run(os.path.join(self.cpp.build.bindir, "test_elevator"), env="conanrun")

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
        
