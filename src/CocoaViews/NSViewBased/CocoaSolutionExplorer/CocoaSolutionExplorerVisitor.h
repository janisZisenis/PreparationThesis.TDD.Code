#ifndef COCOALVIEWS_COCOASOLUTIONEXPLORERVISITOR_H
#define COCOALVIEWS_COCOASOLUTIONEXPLORERVISITOR_H

#include <memory>

class CocoaSolutionExplorer;

class CocoaSolutionExplorerVisitor;
typedef std::shared_ptr<CocoaSolutionExplorerVisitor> CocoaSolutionExplorerViewVisitorPtr;

class CocoaSolutionExplorerVisitor {
public:
     virtual void visit(std::shared_ptr<CocoaSolutionExplorer> view) = 0;
};

#endif //COCOALVIEWS_COCOASOLUTIONEXPLORERVISITOR_H