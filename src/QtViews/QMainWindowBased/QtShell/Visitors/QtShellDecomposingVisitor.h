#ifndef QTVIEWS_QTSHELLDECOMPOSINGVISITOR_H
#define QTVIEWS_QTSHELLDECOMPOSINGVISITOR_H

#include "CrossHierarchies/CNVisitor/CNVisitor.h"

#include "QtViews/QMenuBarBased/QtMenuBar/QtMenuBarVisitor.h"
#include "QtViews/QWidgetBased/QtSolutionExplorer/QtSolutionExplorerVisitor.h"
#include "QtViews/QWidgetBased/QtPropertiesExplorer/QtPropertiesExplorerVisitor.h"
#include "QtViews/QWidgetBased/QtCentral/QtCentralVisitor.h"

class QtShell;

class QtShellDecomposingVisitor;
typedef std::shared_ptr<QtShellDecomposingVisitor> QtShellDecomposingVisitorPtr;

class QtShellDecomposingVisitor
        : public CNVisitor,
          public QtMenuBarVisitor,
          public QtSolutionExplorerVisitor,
          public QtPropertiesExplorerVisitor,
          public QtCentralVisitor {

public:
    static QtShellDecomposingVisitorPtr getNewInstance(std::shared_ptr<QtShell> shell);
    virtual ~QtShellDecomposingVisitor();
private:
    QtShellDecomposingVisitor(std::shared_ptr<QtShell> shell);
private:
    std::shared_ptr<QtShell> shell;

public:
    void visit(std::shared_ptr<QtMenuBar> menuBar) override;
    void visit(std::shared_ptr<QtSolutionExplorer> solutionExplorer) override;
    void visit(std::shared_ptr<QtPropertiesExplorer> propertiesExplorer) override;
    void visit(std::shared_ptr<QtCentral> central) override;
};

#endif //QTVIEWS_QTSHELLDECOMPOSINGVISITOR_H