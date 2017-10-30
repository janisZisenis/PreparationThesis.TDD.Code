#ifndef COCOAVIEWS_COCOASHELLDECOMPOSINGVISITOR_H
#define COCOAVIEWS_COCOASHELLDECOMPOSINGVISITOR_H

#include "Hierarchies/CNVisitor/CNVisitor.h"

#include "CocoaViews/NSViewBased/CocoaSolutionExplorer/CocoaSolutionExplorerVisitor.h"
#include "CocoaViews/NSViewBased/CocoaPropertiesExplorer/CocoaPropertiesExplorerVisitor.h"
#include "CocoaViews/NSViewBased/CocoaCentral/CocoaCentralVisitor.h"

class CocoaShell;

class CocoaShellDecomposingVisitor;
typedef std::shared_ptr<CocoaShellDecomposingVisitor> CocoaShellDecomposingVisitorPtr;

class CocoaShellDecomposingVisitor
        : public CNVisitor,
          public CocoaSolutionExplorerVisitor,
          public CocoaPropertiesExplorerVisitor,
          public CocoaCentralVisitor {

public:
    static CocoaShellDecomposingVisitorPtr getNewInstance(std::shared_ptr<CocoaShell> shell);
    virtual ~CocoaShellDecomposingVisitor();
private:
    CocoaShellDecomposingVisitor(std::shared_ptr<CocoaShell> shell);

public:
    void visit(std::shared_ptr<CocoaSolutionExplorer> solutionExplorer) override;
    void visit(std::shared_ptr<CocoaPropertiesExplorer> propertiesExplorer) override;
    void visit(std::shared_ptr<CocoaCentral> central) override;

private:
    std::shared_ptr<CocoaShell> shell;
};

#endif //COCOAVIEWS_COCOASHELLDECOMPOSINGVISITOR_H