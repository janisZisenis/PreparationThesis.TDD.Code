#include "GridGeneratorComposingVisitor.h"

#include "IRMB/GridGenerator/GridGenerator.h"
#include "IRMB/GridGenerator/STLFile.h"

GridGeneratorComposingVisitorPtr GridGeneratorComposingVisitor::getNewInstance(GridGeneratorPtr gridGenerator) {
    return GridGeneratorComposingVisitorPtr(new GridGeneratorComposingVisitor(gridGenerator));
}

GridGeneratorComposingVisitor::~GridGeneratorComposingVisitor() {}

GridGeneratorComposingVisitor::GridGeneratorComposingVisitor(GridGeneratorPtr gridGenerator) : gridGenerator(gridGenerator) {}

void GridGeneratorComposingVisitor::visit(STLFilePtr stlFile) {
    gridGenerator->addSTLFile(stlFile);
}
