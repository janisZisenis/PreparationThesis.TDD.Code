set(targetName BaseTest)     #REQUIRED#

set(linkDirectories "")
set(libsToLink Base)
set(includeDirectories ${CMAKE_SOURCE_DIR}/src)

#glob files and save in MY_SRCS
include(CMakePackage.cmake)

buildExe(${targetName} "${MY_SRCS}" "${linkDirectories}" "${libsToLink}" "${includeDirectories}")

target_compile_options(${targetName} PRIVATE -std=c++11)

#Specify the linking to 3rdParty libs
include(3rdPartyLinking.cmake)