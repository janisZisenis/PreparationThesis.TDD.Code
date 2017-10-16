#ifndef QTVIEWS_QTSHELLCOMPOSINGVISITOR_H
#define QTVIEWS_QTSHELLCOMPOSINGVISITOR_H

#include "CrossNative/CNVisitor/CNVisitor.h"

#include "QtViews/QtSolutionExplorer/QtSolutionExplorerVisitor.h"
#include "QtViews/QtPropertiesExplorer/QtPropertiesExplorerVisitor.h"

class QtShell;

class QtShellComposingVisitor;
typedef std::shared_ptr<QtShellComposingVisitor> QtShellComposingVisitorPtr;

class QtShellComposingVisitor
        : public CNVisitor,
          public QtSolutionExplorerVisitor,
          public QtPropertiesExplorerVisitor {
public:
    static QtShellComposingVisitorPtr getNewInstance(std::shared_ptr<QtShell> shell);
    virtual ~QtShellComposingVisitor();
private:
    QtShellComposingVisitor(std::shared_ptr<QtShell> shell);

public:
    void visit(std::shared_ptr<QtSolutionExplorer> solutionExplorer) override;
    void visit(std::shared_ptr<QtPropertiesExplorer> propertiesExplorer) override;

private:
    std::shared_ptr<QtShell> shell;
};

#endif //QTVIEWS_QTSHELLCOMPOSINGVISITOR_H