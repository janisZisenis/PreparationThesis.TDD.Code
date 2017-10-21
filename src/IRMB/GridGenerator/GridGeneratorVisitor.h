#ifndef LVICE_GRIDGENERATORVISITOR_H
#define LVICE_GRIDGENERATORVISITOR_H

#include <memory>

class GridGenerator;

class GridGeneratorVisitor;
typedef std::shared_ptr<GridGeneratorVisitor> GridGeneratorVisitorPtr;

class GridGeneratorVisitor {
public:
    virtual void visit(std::shared_ptr<GridGenerator> GridGenerator) = 0;
};

#endif //LVICE_GRIDGENERATORVISITOR_H