#ifndef QTVIEWS_QTSHELLNULLVISITOR_H
#define QTVIEWS_QTSHELLNULLVISITOR_H

#include "QtViews/QtShell/QtShellVisitor.h"
#include "CrossNative/CNVisitor/CNVisitor.h"

class QtShellNullVisitor;
typedef std::shared_ptr<QtShellNullVisitor> QtShellNullVisitorPtr;

class QtShellNullVisitor : public CNVisitor, public QtShellVisitor {
public:
    static QtShellNullVisitorPtr getNewInstance() {
        return QtShellNullVisitorPtr(new QtShellNullVisitor());
    }
    virtual ~QtShellNullVisitor() {}
private:
    QtShellNullVisitor() {}

public:
    virtual void visit(std::shared_ptr<QtShell> qtShell) {}
};

#endif //QTVIEWS_QTSHELLNULLVISITOR_H