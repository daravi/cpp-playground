add_executable(app main.cpp)
target_link_libraries(app PRIVATE CONAN_PKG::boost)
target_link_libraries(app PRIVATE CONAN_PKG::fmt)
target_link_libraries(app PRIVATE CONAN_PKG::spdlog)