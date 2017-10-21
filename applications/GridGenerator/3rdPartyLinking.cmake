include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/Metis/Link.cmake)
linkMetis(${targetName})

include(${CMAKE_SOURCE_DIR}/${cmakeMacroPath}/MPI/Link.cmake)
linkMPI(${targetName})
