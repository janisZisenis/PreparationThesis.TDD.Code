include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/Qt/Link.cmake)
linkQt(${targetName})

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CodeBase/src")
target_link_libraries(${targetName} /Users/Janis/Development/CodeBase/build/applications/JZCoreImp/libJZCoreImp.dylib)