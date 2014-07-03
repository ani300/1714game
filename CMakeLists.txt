
# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# For generators with multiple configurations (like VS), only allow Debug and Release
if(CMAKE_CONFIGURATION_TYPES)
        set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
        mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

# Project name
project(1714game)

# Configuration options
set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML librares")

# General compiler options
if (SFML_STATIC_LIBRARIES)
        add_definitions(-DSFML_STATIC)
endif()

# Specific compiler options - set C++11 flag for g++ and clang
if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

        # Mac OS X: clang uses libc++ standard library
        if(${CMAKE_SYSTEM_NAME} MAIOTCHES "Darwin")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
        endif()
endif()

cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src SRC_LIST)

# Add directory containing FindSFML.cmake to module path
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/;${CMAKE_MODULE_PATH}")

# Find SFML
# Note: SFML_STATIC_LIBRARIES determines which libraries are found by find_package()
find_package(SFML 2 COMPONENTS audio graphics window system network)

# If found, include and link; otherwise output error message
if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
else()
        set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
        message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
        message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

# Executable: Add only Main.cpp, set name without _EXE postfix
add_executable(${PROJECT_NAME} ${SRC_LIST})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME 1714game)

# Build static or shared libraries? Set chapter-specific DLL import macro
if(SFML_STATIC_LIBRARIES)
        set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITNS "SFML_STATIC")
endif()

# Link SFML
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
