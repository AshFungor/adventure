from conan import ConanFile
from conan.tools.cmake import cmake_layout

class AdventureGame(ConanFile):
    version = '0.0'
    generators = 'CMakeToolchain', 'CMakeDeps'
    settings = 'os', 'compiler', 'build_type', 'arch'

    def requirements(self):
        for req in [
            'plog/1.1.10',
            'gtest/1.14.0',
            'nlohmann_json/3.11.3',
            'boost/1.85.0'
        ]:
            self.requires(req)

    def layout(self):
        cmake_layout(self)
