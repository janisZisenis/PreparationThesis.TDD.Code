#ifndef QTVIEWS_QTSHELLNULLVISITOR_H
#define QTVIEWS_QTSHELLNULLVISITOR_H

#include "QtViews/QtShell/QtShellVisitor.h"
#include "CrossNative/CNVisitor/CNVisitor.h"

class CocoaShellNullVisitor;
typedef std::shared_ptr<CocoaShellNullVisitor> QtShellNullVisitorPtr;

class CocoaShellNullVisitor : public CNVisitor, public QtShellVisitor {
public:
    static QtShellNullVisitorPtr getNewInstance() {
        return QtShellNullVisitorPtr(new CocoaShellNullVisitor());
    }
    virtual ~CocoaShellNullVisitor() {}
private:
    CocoaShellNullVisitor() {}

public:
    virtual void visit(std::shared_ptr<QtShell> view) {}
};

#endif //QTVIEWS_QTSHELLNULLVISITOR_H