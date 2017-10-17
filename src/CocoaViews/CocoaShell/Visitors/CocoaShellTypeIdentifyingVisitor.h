#ifndef COCOAVIEWS_COCOASHELLTYPEIDENTIFYINGVISITOR_H
#define COCOAVIEWS_COCOASHELLTYPEIDENTIFYINGVISITOR_H

#include "CocoaViews/CocoaShell/CocoaShellVisitor.h"
#include "CrossNative/CNMatcher/CNIdentifyingVisitor.h"

class CocoaShellTypeIdentifyingVisitor;
typedef std::shared_ptr<CocoaShellTypeIdentifyingVisitor> CocoaShellTypeIdentifyingVisitorPtr;

class CocoaShellTypeIdentifyingVisitor : public CNIdentifyingVisitor, public CocoaShellVisitor {
public:
    static CocoaShellTypeIdentifyingVisitorPtr getNewInstance() {
        return CocoaShellTypeIdentifyingVisitorPtr(new CocoaShellTypeIdentifyingVisitor());
    }
    virtual ~CocoaShellTypeIdentifyingVisitor() {}
private:
    CocoaShellTypeIdentifyingVisitor() {}

public:
    virtual void visit(std::shared_ptr<CocoaShell> CocoaShell) override {}
    bool hasIdentified() override {
        return true;
    }
};

#endif //COCOAVIEWS_COCOASHELLTYPEIDENTIFYINGVISITOR_H