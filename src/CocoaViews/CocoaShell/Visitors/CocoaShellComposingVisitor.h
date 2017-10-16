#ifndef COCOAVIEWS_COCOASHELLCOMPOSINGVISITOR_H
#define COCOAVIEWS_COCOASHELLCOMPOSINGVISITOR_H

#include "CrossNative/CNVisitor/CNVisitor.h"

#include "CocoaViews/CocoaPropertiesExplorer/CocoaPropertiesExplorerVisitor.h"

class CocoaShell;

class CocoaShellComposingVisitor;
typedef std::shared_ptr<CocoaShellComposingVisitor> CocoaShellComposingVisitorPtr;

class CocoaShellComposingVisitor
        : public CNVisitor,
          public CocoaPropertiesExplorerVisitor {
public:
    static CocoaShellComposingVisitorPtr getNewInstance(std::shared_ptr<CocoaShell> shell);
    virtual ~CocoaShellComposingVisitor();
private:
    CocoaShellComposingVisitor(std::shared_ptr<CocoaShell> shell);

public:
    void visit(std::shared_ptr<CocoaPropertiesExplorer> propertiesExplorer) override;

private:
    std::shared_ptr<CocoaShell> shell;
};

#endif //COCOAVIEWS_COCOASHELLCOMPOSINGVISITOR_H