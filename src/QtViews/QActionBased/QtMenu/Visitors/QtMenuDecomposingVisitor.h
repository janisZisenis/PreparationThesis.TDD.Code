#ifndef QTVIEWS_QTMENUDECOMPOSINGVISITOR_H
#define QTVIEWS_QTMENUDECOMPOSINGVISITOR_H

#include <CrossHierarchies/CNVisitor/CNVisitor.h>

#include "QtViews/QActionBased/QtMenu/QtMenuVisitor.h"
#include "QtViews/QActionBased/QtAction/QtActionVisitor.h"

class QtMenu;

class QtMenuDecomposingVisitor;
typedef std::shared_ptr<QtMenuDecomposingVisitor> QtMenuDecomposingVisitorPtr;

class QtMenuDecomposingVisitor
        : public CNVisitor,
          public QtMenuVisitor,
          public QtActionVisitor {
public:
    static QtMenuDecomposingVisitorPtr getNewInstance(std::shared_ptr<QtMenu> menu);
    virtual ~QtMenuDecomposingVisitor();
private:
    QtMenuDecomposingVisitor(std::shared_ptr<QtMenu> menu);

public:
    virtual void visit(std::shared_ptr<QtAction> action) override;
    virtual void visit(std::shared_ptr<QtMenu> menu) override;
private:
    std::shared_ptr<QtMenu> menu;
};

#endif //QTVIEWS_QTMENUDECOMPOSINGVISITOR_H