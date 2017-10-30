#ifndef QTVIEWS_QTSHELLCOMPOSINGVISITOR_H
#define QTVIEWS_QTSHELLCOMPOSINGVISITOR_H

#include "Hierarchies/CNVisitor/CNVisitor.h"

#include "QtViews/QMenuBarBased/QtMenuBar/QtMenuBarVisitor.h"
#include "QtViews/QWidgetBased/QtCentral/QtCentralVisitor.h"
#include "QtViews/QWidgetBased/QtSolutionExplorer/QtSolutionExplorerVisitor.h"
#include "QtViews/QWidgetBased/QtPropertiesExplorer/QtPropertiesExplorerVisitor.h"

class QtShell;

class QtShellComposingVisitor;
typedef std::shared_ptr<QtShellComposingVisitor> QtShellComposingVisitorPtr;

class QtShellComposingVisitor
        : public CNVisitor,
          public QtMenuBarVisitor,
          public QtSolutionExplorerVisitor,
          public QtPropertiesExplorerVisitor,
          public QtCentralVisitor {
public:
    static QtShellComposingVisitorPtr getNewInstance(std::shared_ptr<QtShell> shell);
    virtual ~QtShellComposingVisitor();
private:
    QtShellComposingVisitor(std::shared_ptr<QtShell> shell);

public:
    void visit(std::shared_ptr<QtMenuBar> menuBar) override;
    void visit(std::shared_ptr<QtSolutionExplorer> solutionExplorer) override;
    void visit(std::shared_ptr<QtPropertiesExplorer> propertiesExplorer) override;
    void visit(std::shared_ptr<QtCentral> central) override;

private:
    std::shared_ptr<QtShell> shell;
};

#endif //QTVIEWS_QTSHELLCOMPOSINGVISITOR_H