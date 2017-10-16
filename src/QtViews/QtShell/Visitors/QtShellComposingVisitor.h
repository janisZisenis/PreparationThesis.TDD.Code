#ifndef QTVIEWS_QTSHELLCOMPOSINGVISITOR_H
#define QTVIEWS_QTSHELLCOMPOSINGVISITOR_H

#include "CrossNative/CNVisitor/CNVisitor.h"

#include "QtViews/QtSolutionExplorer/QtSolutionExplorerVisitor.h"

class QtShell;

class QtShellComposingVisitor;
typedef std::shared_ptr<QtShellComposingVisitor> QtShellComposingVisitorPtr;

class QtShellComposingVisitor
        : public CNVisitor,
          public QtSolutionExplorerVisitor {
public:
    static QtShellComposingVisitorPtr getNewInstance(std::shared_ptr<QtShell> shell);
    virtual ~QtShellComposingVisitor();
private:
    QtShellComposingVisitor(std::shared_ptr<QtShell> shell);

public:
    void visit(std::shared_ptr<QtSolutionExplorer> solutionExplorer) override;

private:
    std::shared_ptr<QtShell> shell;
};

#endif //QTVIEWS_QTSHELLCOMPOSINGVISITOR_H