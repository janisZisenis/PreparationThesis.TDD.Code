#FILE ENDINGS
resetFileEndingsToCollect()
addCAndCPPFileTypes()

#GLOB SOURCE FILES IN MY_SRCS
unset(MY_SRCS)
includeRecursiveAllFilesFrom(${targetName} ${CMAKE_CURRENT_LIST_DIR})


#activate AllTestOption ON for extended source_group
activateAllTestOption()

includeRecursiveTestFilesFrom(CrossViews ${CMAKE_SOURCE_DIR}/src/Hierarchies)
includeRecursiveTestFilesFrom(CrossViews ${CMAKE_SOURCE_DIR}/src/CrossViews)

#deactivate AllTestOption for normal source_group
deactivateAllTestOption()