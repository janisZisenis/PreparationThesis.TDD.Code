#ifndef QTVIEWS_QTSHELLVISITOR_H
#define QTVIEWS_QTSHELLVISITOR_H

#include <memory>

class QtShell;

class QtShellVisitor;
typedef std::shared_ptr<QtShellVisitor> QtShellVisitorPtr;

class QtShellVisitor {
public:
    virtual void visit(std::shared_ptr<QtShell> view) = 0;
};

#endif //QTVIEWS_QTSHELLVISITOR_H