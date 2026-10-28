cmake_minimum_required(VERSION 3.30)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "25d6f6aa-be65-4692-b44e-87b23e96d4e1")

project(Chip8Emulator LANGUAGES CXX)

# Tell CMake that we explicitly want `import std`. This will initialize the
# property on all targets declared after this to 1
set(CMAKE_CXX_MODULE_STD 1)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(raylib REQUIRED)

include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

add_library(Chip8)
target_compile_features(Chip8
    PRIVATE cxx_std_23
    INTERFACE cxx_std_20)
target_sources(Chip8
    PUBLIC FILE_SET CXX_MODULES FILES
        src/chip8/chip8.cppm
    PRIVATE
        src/chip8/chip8_impl.cpp)

set(SOURCE_FILES
    src/hello.cpp
)
add_executable(hello
    ${SOURCE_FILES}
)
target_compile_features(hello PUBLIC cxx_std_23)
target_link_libraries(hello Chip8 raylib argparse)
