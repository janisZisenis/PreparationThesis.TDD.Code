#ifndef QTVIEWS_QTMENUCOMPOSINGVISITOR_H
#define QTVIEWS_QTMENUCOMPOSINGVISITOR_H

#include <CrossHierarchies/CNVisitor/CNVisitor.h>
#include "QtViews/QActionBased/QtAction/QtActionVisitor.h"
#include "QtViews/QActionBased/QtMenu/QtMenuVisitor.h"

class QtMenu;

class QtMenuComposingVisitor;
typedef std::shared_ptr<QtMenuComposingVisitor> QtMenuComposingVisitorPtr;

class QtMenuComposingVisitor
        : public CNVisitor,
          public QtMenuVisitor,
          public QtActionVisitor {
public:
    static QtMenuComposingVisitorPtr getNewInstance(std::shared_ptr<QtMenu> menu);
    virtual ~QtMenuComposingVisitor();
private:
    QtMenuComposingVisitor(std::shared_ptr<QtMenu> menu);

public:
    virtual void visit(std::shared_ptr<QtAction> action) override;
    virtual void visit(std::shared_ptr<QtMenu> menu) override;
private:
    std::shared_ptr<QtMenu> menu;
};

#endif //QTVIEWS_QTMENUCOMPOSINGVISITOR_H