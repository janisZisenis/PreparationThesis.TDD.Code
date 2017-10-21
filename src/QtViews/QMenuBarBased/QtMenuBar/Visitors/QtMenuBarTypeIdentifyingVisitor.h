#ifndef QTVIEWS_QTMENUBARTYPEIDENTIFYINGVISITOR_H
#define QTVIEWS_QTMENUBARTYPEIDENTIFYINGVISITOR_H

#include "QtViews/QMenuBarBased/QtMenuBar/QtMenuBarVisitor.h"
#include "CrossNative/CNMatcher/CNVisitingMatcher/CNIdentifyingVisitor.h"

class QtMenuBarTypeIdentifyingVisitor;
typedef std::shared_ptr<QtMenuBarTypeIdentifyingVisitor> QtMenuBarTypeIdentifyingVisitorPtr;

class QtMenuBarTypeIdentifyingVisitor : public CNIdentifyingVisitor, public QtMenuBarVisitor {
public:
    static QtMenuBarTypeIdentifyingVisitorPtr getNewInstance() {
        return QtMenuBarTypeIdentifyingVisitorPtr(new QtMenuBarTypeIdentifyingVisitor());
    }
    virtual ~QtMenuBarTypeIdentifyingVisitor() {}
private:
    QtMenuBarTypeIdentifyingVisitor() {}

public:
    virtual void visit(std::shared_ptr<QtMenuBar> qtMenuBar) override {}
    bool hasIdentified() override {
        return true;
    }
};

#endif //QTVIEWS_QTMENUBARTYPEIDENTIFYINGVISITOR_H