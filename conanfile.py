from conans import ConanFile, CMake, tools

class PlaygroundConan(ConanFile):
    name = "playground"
    description = "For QML dev"
    settings = "os", "compiler", "build_type", "arch"
    generators = ["cmake", "virtualenv", "VirtualRunEnv"]
    
    requires = (
        "boost/1.74.0@3rdparty/stable",
        "fmt/8.0.1@3rdparty/stable",
        "spdlog/1.9.2@3rdparty/stable"
    )
    build_requires = (
        "cmake/3.19.2@3rdparty/stable",
        "ninja/1.10.2@3rdparty/stable"
    )
    
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = { "shared": False, "fPIC": True }
    
    def build_requirements(self):
        self.build_requires("gtest/1.10.0@3rdparty/stable", force_host_context=True)
    
    def requirements(self):
        # Add conditional requirements (e.g. OS based requirements) here
        pass
