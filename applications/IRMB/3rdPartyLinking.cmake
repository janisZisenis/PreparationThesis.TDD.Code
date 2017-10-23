include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/Boost/Link.cmake)
linkBoost(${targetName} COMPONENTS filesystem)

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CodeBase/src")
target_link_libraries(${targetName} /Users/Janis/Development/CodeBase/build/applications/CodeBaseImp/libCodeBaseImp.dylib)
