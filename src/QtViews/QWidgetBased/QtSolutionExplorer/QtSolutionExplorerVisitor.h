#ifndef QTVIEWS_QTSOLUTIONEXPLORERVISITOR_H
#define QTVIEWS_QTSOLUTIONEXPLORERVISITOR_H

#include <memory>

class QtSolutionExplorer;

class QtSolutionExplorerVisitor;
typedef std::shared_ptr<QtSolutionExplorerVisitor> QtSolutionExplorerVisitorPtr;

class QtSolutionExplorerVisitor {
public:
    virtual void visit(std::shared_ptr<QtSolutionExplorer> solutionExplorer) = 0;
};

#endif //QTVIEWS_QTSOLUTIONEXPLORERVISITOR_H