#ifndef COCOAVIEWS_COCOASHELLNULLVISITOR_H
#define COCOAVIEWS_COCOASHELLNULLVISITOR_H

#include "CocoaViews/CocoaShell/CocoaShellVisitor.h"

class CocoaShellNullVisitor;
typedef std::shared_ptr<CocoaShellNullVisitor> CocoaShellNullVisitorPtr;

class CocoaShellNullVisitor : public CocoaShellVisitor {
public:
    virtual void visit(std::shared_ptr<CocoaShell> cocoaShell) override {}
};

#endif //COCOAVIEWS_COCOASHELLNULLVISITOR_H