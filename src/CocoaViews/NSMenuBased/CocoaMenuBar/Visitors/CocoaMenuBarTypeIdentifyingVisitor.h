#ifndef COCOAVIEWS_COCOAMENUBARTYPEIDENTIFYINGVISITOR_H
#define COCOAVIEWS_COCOAMENUBARTYPEIDENTIFYINGVISITOR_H

#include "CocoaViews/NSMenuBased/CocoaMenuBar/CocoaMenuBarVisitor.h"
#include "Hierarchies/CNMatcher/CNVisitingMatcher/CNIdentifyingVisitor.h"

class CocoaMenuBarTypeIdentifyingVisitor;
typedef std::shared_ptr<CocoaMenuBarTypeIdentifyingVisitor> CocoaMenuBarTypeIdentifyingVisitorPtr;

class CocoaMenuBarTypeIdentifyingVisitor : public CNIdentifyingVisitor, public CocoaMenuBarVisitor {
public:
    static CocoaMenuBarTypeIdentifyingVisitorPtr getNewInstance() {
        return CocoaMenuBarTypeIdentifyingVisitorPtr(new CocoaMenuBarTypeIdentifyingVisitor());
    }
    virtual ~CocoaMenuBarTypeIdentifyingVisitor() {}
private:
    CocoaMenuBarTypeIdentifyingVisitor() {}

public:
    virtual void visit(std::shared_ptr<CocoaMenuBar> CocoaMenuBar) override {}
    bool hasIdentified() override {
        return true;
    }
};

#endif //COCOAVIEWS_COCOAMENUBARTYPEIDENTIFYINGVISITOR_H