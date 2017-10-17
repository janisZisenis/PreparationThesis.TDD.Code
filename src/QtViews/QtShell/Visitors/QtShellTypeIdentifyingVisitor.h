#ifndef QTVIEWS_QTSHELLTYPEIDENTIFYINGVISITOR_H
#define QTVIEWS_QTSHELLTYPEIDENTIFYINGVISITOR_H

#include "QtViews/QtShell/QtShellVisitor.h"
#include "CrossNative/CNMatcher/CNIdentifyingVisitor.h"

class QtShellTypeIdentifyingVisitor;
typedef std::shared_ptr<QtShellTypeIdentifyingVisitor> QtShellTypeIdentifyingVisitorPtr;

class QtShellTypeIdentifyingVisitor : public CNIdentifyingVisitor, public QtShellVisitor {
public:
    static QtShellTypeIdentifyingVisitorPtr getNewInstance() {
        return QtShellTypeIdentifyingVisitorPtr(new QtShellTypeIdentifyingVisitor());
    }
    virtual ~QtShellTypeIdentifyingVisitor() {}
private:
    QtShellTypeIdentifyingVisitor() {}

public:
    virtual void visit(std::shared_ptr<QtShell> qtShell) override {}
    bool hasIdentified() override {
        return true;
    }
};

#endif //QTVIEWS_QTSHELLTYPEIDENTIFYINGVISITOR_H