include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/Cocoa/Link.cmake)
linkCocoa(${targetName})

include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/Boost/Link.cmake)
linkBoost(${targetName})