set(targetName QtViews)       #REQUIRED#

set(linkDirectories "")
set(libsToLink CrossHierarchies CrossViews)
set(includeDirectories ${CMAKE_SOURCE_DIR}/src)
#glob files and save in MY_SRCS
include(CMakePackage.cmake)

set(CMAKE_AUTOMOC ON)

buildLib(${targetName} "${MY_SRCS}" "${linkDirectories}" "${libsToLink}" "${includeDirectories}")
generateExportHeader(${targetName} ${CMAKE_SOURCE_DIR}/src/${targetName})

target_compile_options(${targetName} PRIVATE -std=c++11)

#Specify the linking to 3rdParty libs
include(3rdPartyLinking.cmake)
