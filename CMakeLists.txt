# Specify CMake 2.8 as minimum required version
cmake_minimum_required(VERSION 2.8)

# Specify default build type if none provided (Release is default)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Chose the type of build (Debug or Release)" FORCE)
endif()

if (CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
	mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

project(2048)

# Add include folder so source files can include header files directly.
include_directories(${PROJECT_SOURCE_DIR}/include)

# C++ 14 support
if (CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

# Configurations
set(RM2_SFML_SHARED_LIBS TRUE CACHE BOOL "Link SFML dynamically?")

# Add custom CMake sub-modules to module path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake/modules;${CMAKE_MODULE_PATH}")

# Find SFML
if(NOT RM2_SFML_SHARED_LIBS)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()
find_package(SFML 2.3.2 COMPONENTS graphics window system)

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
else()
	set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories.)")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

# Macro to link SFML
macro(rm2_link_sfml RM2_TARGET)
	target_link_libraries(${RM2_TARGET} ${SFML_LIBRARIES})
endmacro()

macro(rm2_link_sfml_dependencies RM2_TARGET)
	target_link_libraries(${RM2_TARGET} ${SFML_DEPENDENCIES})
endmacro()

# Find Jsoncpp
find_package(Jsoncpp)

if (JSONCPP_FOUND)
	include_directories(${JSONCPP_INCLUDE_DIR})
else()
	
endif()

# Macro to link jsoncpp
macro(rm2_link_jsoncpp RM2_TARGET)
	target_link_libraries(${RM2_TARGET} ${JSONCPP_LIBRARIES})
endmacro()

# Source code
add_subdirectory(source)