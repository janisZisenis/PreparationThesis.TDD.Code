#ifndef COCOAVIEWS_COCOASHELLNULLVISITOR_H
#define COCOAVIEWS_COCOASHELLNULLVISITOR_H

#include "CocoaViews/CocoaShell/CocoaShellVisitor.h"
#include "CrossNative/CNVisitor/CNVisitor.h"

class CocoaShellNullVisitor;
typedef std::shared_ptr<CocoaShellNullVisitor> CocoaShellNullVisitorPtr;

class CocoaShellNullVisitor : public CNVisitor, public CocoaShellVisitor {
public:
    static CocoaShellNullVisitorPtr getNewInstance() {
        return CocoaShellNullVisitorPtr(new CocoaShellNullVisitor());
    }
    virtual ~CocoaShellNullVisitor() {}
private:
    CocoaShellNullVisitor() {}

public:
    virtual void visit(std::shared_ptr<CocoaShell> view) {}
};

#endif //COCOAVIEWS_COCOASHELLNULLVISITOR_H