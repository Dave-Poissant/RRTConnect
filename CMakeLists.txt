#===============================================================================
# CMake settings
#===============================================================================
cmake_minimum_required(VERSION 3.0.0)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../output")

#===============================================================================
# Project settings
#===============================================================================
project(RRTConnect VERSION 1.0.0)

set(RRTCONNECT_MAJOR_VERSION "1")
set(RRTCONNECT_MINOR_VERSION "0")
set(RRTCONNECT_PATCH_VERSION "0")
set(RRTCONNECT_VERSION "${RRTCONNECT_MAJOR_VERSION}.${RRTCONNECT_MINOR_VERSION}.${RRTCONNECT_PATCH_VERSION}")
set(RRTCONNECT_PKG_DESC "RRTConnect path planning")

#===============================================================================
# Print intro
#===============================================================================
message(STATUS "")
message(STATUS "==========================================================")
message(STATUS "            ${RRTCONNECT_PKG_DESC} - ${RRTCONNECT_VERSION}")
message(STATUS "==========================================================")

#===============================================================================
# Compiler flags
#===============================================================================
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP4")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/LTCG /INCREMENTAL:NO")
  if(NOT RRTCONNECT_MSVC_DEFAULT_OPTIONS)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${RRTCONNECT_RUNTIME_LIBRARY}d /Zi /Gy /W1 /EHsc")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${RRTCONNECT_RUNTIME_LIBRARY} /Zi /GL /Gy /W1 /EHsc")
  endif(NOT RRTCONNECT_MSVC_DEFAULT_OPTIONS)
elseif(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
else()
  message(SEND_ERROR "Compiler[${CMAKE_CXX_COMPILER_ID}] not supported.")
endif()

#===============================================================================
# Build type settings
#===============================================================================
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug | Release | RelWithDebInfo | MinSizeRel" FORCE)
endif()
string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPERCASE)

set(BUILD_TYPE_DEBUG FALSE)
set(BUILD_TYPE_RELEASE FALSE)
set(BUILD_TYPE_RELWITHDEBINFO FALSE)
set(BUILD_TYPE_MINSIZEREL FALSE)

if("${CMAKE_BUILD_TYPE_UPPERCASE}" STREQUAL "DEBUG")
  set(BUILD_TYPE_DEBUG TRUE)
elseif("${CMAKE_BUILD_TYPE_UPPERCASE}" STREQUAL "RELEASE")
  set(BUILD_TYPE_RELEASE TRUE)
elseif("${CMAKE_BUILD_TYPE_UPPERCASE}" STREQUAL "RELWITHDEBINFO")
  set(BUILD_TYPE_RELWITHDEBINFO TRUE)
elseif("${CMAKE_BUILD_TYPE_UPPERCASE}" STREQUAL "MINSIZEREL")
  set(BUILD_TYPE_MINSIZEREL TRUE)
else()
  build_error("CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} unknown. Valid options are: Debug | Release | RelWithDebInfo | MinSizeRel")
endif()

#===============================================================================
# Find dependencies
#===============================================================================
set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH )

#------------------------
# Mandatory dependencies
#------------------------
message(STATUS "")
message(STATUS "[ Mandatory dependencies ]")


# SFML packages
find_package(SFML COMPONENTS graphics audio CONFIG REQUIRED)

# Boost packages
find_package(Boost REQUIRED COMPONENTS system filesystem thread)

#===============================================================================
# Include directories
#===============================================================================
set(RRTCONNECT_PACKAGES_INCLUDE_DIRS
)
include_directories(${RRTCONNECT_PACKAGES_INCLUDE_DIRS})

# Include RRTCONNECT header files
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

#===============================================================================
# Set build dependent variables
#===============================================================================
set(RRTCONNECT_PACKAGES_LIBRARIES
)

set(RRTCONNECT_DEPENDENCIES
  sfml-graphics
  sfml-audio
  Boost::boost
  Boost::system 
  Boost::filesystem
  Boost::thread
)

#===============================================================================
# Target link libraries
#===============================================================================
add_subdirectory(src/RRTConnect)
add_subdirectory(tests/RRTConnect)
