cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0042)
   CMAKE_POLICY(SET CMP0042 NEW)
endif()
if(POLICY CMP0020)
   CMAKE_POLICY(SET CMP0020 NEW)
endif()
if(POLICY CMP0028)
   CMAKE_POLICY(SET CMP0028 NEW)
endif()
if(POLICY CMP0037)
   CMAKE_POLICY(SET CMP0037 NEW)
endif()
if(POLICY CMP0047)
   CMAKE_POLICY(SET CMP0047 NEW)
endif()
if(POLICY CMP0053)
   CMAKE_POLICY(SET CMP0053 NEW)
endif()


if(APPLE)
   set(CMAKE_CXX_FLAGS -std=c++11)
endif()

#############################################################
###                     ENVIRONMENT                       ###
#############################################################
set(cmakeMacroPath "CMakeMacros")
include(${cmakeMacroPath}/Environment/environment.cmake)
#############################################################
###                   GENERAL MACROS                      ###
#############################################################

include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/general/BuildTarget.cmake)
include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/general/BuildTargetUtilities.cmake)
include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/general/EndingsToCollect.cmake)
include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/general/FileUtilities.cmake)
include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/MacOSXBundle/MacOSXBundle.cmake)

#############################################################
###                   GENERAL SETTINGS                    ###
#############################################################

project(CrossNative)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")
sharedLibs()


#############################################################
###                   SUBDIRECTORIES                      ###
#############################################################

add_subdirectory(applications/Base)
add_subdirectory(applications/BaseTest)

add_subdirectory(applications/Hierarchies)
add_subdirectory(applications/HierarchiesTest)

add_subdirectory(applications/CrossViewsTest)
add_subdirectory(applications/CrossViews)

add_subdirectory(applications/QtViews)
if(APPLE)
   add_subdirectory(applications/CocoaViews)
endif()

add_subdirectory(applications/AllTest)
