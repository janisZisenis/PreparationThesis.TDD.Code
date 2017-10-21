#ifndef COCOAVIEWS_COCOASHELLVISITOR_H
#define COCOAVIEWS_COCOASHELLVISITOR_H

#include "CocoaShellVisitor.h"

class CocoaShell;

class CocoaShellVisitor;
typedef std::shared_ptr<CocoaShellVisitor> CocoaShellVisitorPtr;

class CocoaShellVisitor {
public:
    virtual void visit(std::shared_ptr<CocoaShell> cocoaShell) = 0;
};

#endif //COCOAVIEWS_COCOASHELLVISITOR_H