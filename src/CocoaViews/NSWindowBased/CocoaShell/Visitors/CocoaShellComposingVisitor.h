#ifndef COCOAVIEWS_COCOASHELLCOMPOSINGVISITOR_H
#define COCOAVIEWS_COCOASHELLCOMPOSINGVISITOR_H

#include "CrossHierarchies/CNVisitor/CNVisitor.h"

#include "CocoaViews/NSViewBased/CocoaSolutionExplorer/CocoaSolutionExplorerVisitor.h"
#include "CocoaViews/NSViewBased/CocoaPropertiesExplorer/CocoaPropertiesExplorerVisitor.h"
#include "CocoaViews/NSViewBased/CocoaCentral/CocoaCentralVisitor.h"

class CocoaShell;

class CocoaShellComposingVisitor;
typedef std::shared_ptr<CocoaShellComposingVisitor> CocoaShellComposingVisitorPtr;

class CocoaShellComposingVisitor
        : public CNVisitor,
          public CocoaPropertiesExplorerVisitor,
          public CocoaSolutionExplorerVisitor,
          public CocoaCentralVisitor {
public:
    static CocoaShellComposingVisitorPtr getNewInstance(std::shared_ptr<CocoaShell> shell);
    virtual ~CocoaShellComposingVisitor();
private:
    CocoaShellComposingVisitor(std::shared_ptr<CocoaShell> shell);

public:
    void visit(std::shared_ptr<CocoaSolutionExplorer> solutionExplorer) override;
    void visit(std::shared_ptr<CocoaPropertiesExplorer> propertiesExplorer) override;
    void visit(std::shared_ptr<CocoaCentral> central) override;

private:
    std::shared_ptr<CocoaShell> shell;
};

#endif //COCOAVIEWS_COCOASHELLCOMPOSINGVISITOR_H