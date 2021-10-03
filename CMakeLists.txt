cmake_minimum_required(VERSION 3.17)

project(playground)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# Set compiler / linker flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -fdiagnostics-color=always")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=lld")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fuse-ld=lld")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")                # reasonable and standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")               # warn the user if a variable declaration shadows one from a parent context
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-virtual-dtor")     # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")           # warn for potential performance problem casts
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused")               # warn on anything being unused
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual")   # warn if you overload (not override) a virtual function
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")             # warn if non-standard C++ is used
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion")           # warn on type conversions that may lose data
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnull-dereference")     # warn if a null dereference is detected
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2")             # warn on security issues around functions that format output (ie printf)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wimplicit-fallthrough") # warn on switch with fallthrough
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-zero-variadic-macro-arguments") # gives error with GMock macros
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shorten-64-to-32") # too aggressive considering how often this happens
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Werror") # Warnings as errors

add_subdirectory(src)