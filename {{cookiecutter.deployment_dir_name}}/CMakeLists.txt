####
# {{cookiecutter.deployment_display_name}} Deployment:
#
# This sets up the  {{cookiecutter.deployment_display_name}} deployment using CMake
# for use with F prime.
#
# This file has several sections.
#
# 1. Header Section: define basic properties of the build
# 2. F´ core: includes all F´ core components, and build-system properties
# 3. Local subdirectories: contains all deployment specific directory additions
####

##
# Section 1: Basic Project Setup
#
# This contains the basic project information. Specifically, a cmake version and
# project definition.
#
# The project name does need to take into account the path to the deployment folder,
# if it is not at the F Prime root, e.g.: path_to_{{cookiecutter.deployment_dir_name}}
# not having this will confuse the `fprime-util` tool.
##
project({{cookiecutter.deployment_path|replace('/','_')}}_{{cookiecutter.deployment_dir_name}} C CXX ASM)
cmake_minimum_required(VERSION 3.5)

set(FPRIME_FRAMEWORK_PATH "${CMAKE_CURRENT_LIST_DIR}/../{{cookiecutter.path_to_fprime_root}}" CACHE PATH "Location of F prime framework" FORCE)
set(FPRIME_PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/../{{cookiecutter.path_to_fprime_root}}" CACHE PATH "Root path of F prime project" FORCE)

set(BAREMETAL_SCHEDULER CACHE BOOL ON "Uses the baremetal scheduler")

# Use file hashes instead of full file paths in the compiled binary.  This can be
# converted back to a filename with the `fprime-util hashes` tool.
add_definitions(-DFW_ASSERT_LEVEL=2)


##
# Section 2: F´ Core
#
# This includes all of the F´ core components, and imports the make-system. F´ core
# components will be placed in the F-Prime binary subdirectory to keep them from
# colliding with deployment specific items.
##
include("${CMAKE_CURRENT_LIST_DIR}/../{{cookiecutter.path_to_fprime_root}}/cmake/FPrime.cmake")
# NOTE: register custom targets between these two lines
include("${CMAKE_CURRENT_LIST_DIR}/../{{cookiecutter.path_to_fprime_root}}/cmake/FPrime-Code.cmake")
# Note: when building a deployment outside of the F´ core directories, then the
# build root must be re-mapped for use with the standard build system components.
#
# In this way, the module names can be predicted as an offset from the (new) build
# root, without breaking the standard locations of F´.
#
# Uncomment the following lines, and set them to the BUILD_ROOT of your deployment,
# which is typically one directory up from the CMakeLists.txt in the deployment dir.
set(FPRIME_CURRENT_BUILD_ROOT "${CMAKE_CURRENT_LIST_DIR}/../{{cookiecutter.path_to_fprime_root}}")
message(STATUS "F´ BUILD_ROOT currently set to: ${FPRIME_CURRENT_BUILD_ROOT}")

##
# Section 3: Components and Topology
#
# This section includes deployment specific directories. This allows use of non-
# core components in the topology, which is also added here.
##
# Add component subdirectories
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../{{cookiecutter.path_to_fprime_root}}/ATmega/AssertReset/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../{{cookiecutter.path_to_fprime_root}}/ATmega/HardwareRateDriver/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/{{cookiecutter.component_dir_name}}/")

# Add Topology subdirectory
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")

