include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/GMock/Link.cmake)
linkGMock(${targetName})

target_include_directories(${targetName} PUBLIC "/Users/Janis/Development/CodeBase/src")
target_link_libraries(${targetName} /Users/Janis/Development/CodeBase/cmake-build-debug/applications/CodeBaseImp/libCodeBaseImp.dylib)