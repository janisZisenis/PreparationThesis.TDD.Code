#ifndef QTVIEWS_QTMENUDECOMPOSINGVISITOR_H
#define QTVIEWS_QTMENUDECOMPOSINGVISITOR_H

#include <CrossNative/CNVisitor/CNVisitor.h>

#include "QtViews/QtMenu/QtMenuVisitor.h"
#include "QtViews/QtAction/QtActionVisitor.h"

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