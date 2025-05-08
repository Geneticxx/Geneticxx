cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.29.20240416")
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
    #    set(CMAKE_CXX_MODULE_STD 1)
endif ()

project(Genetic
        LANGUAGES CXX
)

#
# Set language version used
#


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
#set(CMAKE_CXX_EXTENSIONS OFF)

#
# Enable modules in CMake
#

if (CMAKE_VERSION VERSION_LESS "3.28.0")
    if (CMAKE_VERSION VERSION_LESS "3.27.0")
        set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
    else ()
        set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
    endif ()
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
else ()
    cmake_policy(VERSION 3.28)
endif ()

if (DEFINED CMAKE_CXX_COMPILER_IMPORT_STD)
    message(STATUS "Support for 'import std;' is enabled with the active toolchain.")
else ()
    message(WARNING "Toolchain does not explicitly support 'import std;'. Experimental feature might not work.")
endif ()

#
# Check compilers' version
#

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # require at least gcc 14.8
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 15.0)
        message(FATAL_ERROR "GCC version must be at least 15.0!")
    endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # require at least clang 18.1.2

    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18.1.2)
        message(FATAL_ERROR "Clang version must be at least 18.1.2!")
    endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # require at least MSVC 14.36 (Visual Studio 17.6 Preview 2+)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.35)
        message(FATAL_ERROR "MSVC version must be at least 19.35!")
    endif ()
else ()
    message(WARNING "You are using an unsupported compiler! Compilation has only been tested with Clang and MSVC.")
endif ()
message(NOTICE "A build system supporting modules is required, such as ninja 1.11 or newer.")


#
# Add the project
#

# Create a library for core functionality
add_library(GeneticLib STATIC)


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(GeneticLib PUBLIC #this seems to cause project rebuilds to fail? when rebuilding all projects it works, also only MSVC works with this
            /std:c++latest
            /EHsc
            /W4
            /U _DEBUG
            /experimental:module
    )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    #
    # Import the modules from libc++
    #
    include(FetchContent)
    FetchContent_Declare(
            std
            URL "file://${LIBCXX_BUILD}/modules/c++/v1/"
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
            SYSTEM
    )
    FetchContent_MakeAvailable(std)
endif ()

# Define interfaces
file(GLOB_RECURSE CORE_INTERFACES "${PROJECT_SOURCE_DIR}/Core/*.ixx"
        "${PROJECT_SOURCE_DIR}/Implementations/*.ixx"
)

# Define implementations
file(GLOB_RECURSE CORE_IMPLEMENTATIONS "${PROJECT_SOURCE_DIR}/Core/*.cppm"
        "${PROJECT_SOURCE_DIR}/Implementations/*.cppm"
)

# Exclude specific files
#list(FILTER CORE_INTERFACES EXCLUDE REGEX ".*GenomeSimpleTree\\.ixx$")
#list(FILTER CORE_IMPLEMENTATIONS EXCLUDE REGEX ".*GenomeSimpleTree\\.cppm$")

# Add the source files to the target
target_sources(GeneticLib
        PRIVATE
        ${CORE_IMPLEMENTATIONS}
)

# Add the module interface files to a FILE_SET
target_sources(GeneticLib PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_SOURCE_DIR}
        FILES
        ${CORE_INTERFACES}
)

target_compile_features(GeneticLib PRIVATE cxx_std_23)

# Define the executable target
add_executable(Genetic main.cpp)
target_link_libraries(Genetic PRIVATE GeneticLib)

# Ensure dependencies on standard library modules
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_dependencies(Genetic std.compat)
    target_link_libraries(Genetic std.compat)
endif ()

#
# Adding Tests
#

add_subdirectory(Tests)


# Adding example problems

add_subdirectory(Examples)

