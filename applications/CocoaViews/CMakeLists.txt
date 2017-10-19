set(targetName CocoaViews)       #REQUIRED#

set(linkDirectories "")
set(libsToLink CrossViews CrossNative)
set(includeDirectories ${CMAKE_SOURCE_DIR}/src)
#glob files and save in MY_SRCS
include(CMakePackage.cmake)

buildLib(${targetName} "${MY_SRCS}" "${linkDirectories}" "${libsToLink}" "${includeDirectories}")
generateExportHeader(${targetName} ${CMAKE_SOURCE_DIR}/src/${targetName})

target_compile_options(${targetName} PRIVATE -std=c++11)
target_compile_options(${targetName} PUBLIC -fobjc-arc)

#Specify the linking to 3rdParty libs
include(3rdPartyLinking.cmake)
