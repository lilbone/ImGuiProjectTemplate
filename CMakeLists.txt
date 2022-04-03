cmake_minimum_required(VERSION 3.16)

project("CppTemplate" VERSION 1.0.0 LANGUAGES C CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD              17)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)

# Options
option(ENABLE_WARNINGS      "Enable to add warnings to a target."   ON)
option(ENABLE_CLANG_TIDY    "Enable to add clang tidy."             OFF)
option(ENABLE_CPPCHECK      "Enable to add cppcheck."               OFF)
option(ENABLE_LTO           "Enable to add Link Time Optimization." OFF)
option(ENABLE_CCACHE        "Enable to add Ccache."                 OFF)

### CMAKE MODULES

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(ConfigSafeGuards)
include(Warnings)
include(AddGitSubmodule)
include(FetchContent)

include(StaticAnalyzers)
include(LTO)
include(Ccache)

if (ENABLE_LTO)
    find_lto(CXX)
endif()

### EXTERNAL LIBRARIES

add_git_submodule(external/glfw)
add_git_submodule(external/glad)
add_git_submodule(external/json)

FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
    GIT_TAG v3.0.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(cxxopts)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 8.1.1
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG v1.9.2
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(spdlog)

### SUB DIRECTORIES

add_subdirectory(configured)
add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(app)