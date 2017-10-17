#ifndef QTVIEWS_QTMENUVISITOR_H
#define QTVIEWS_QTMENUVISITOR_H

#include <memory>

class QtMenu;

class QtMenuVisitor;
typedef std::shared_ptr<QtMenuVisitor> QtMenuVisitorPtr;

class QtMenuVisitor {
public:
    virtual void visit(std::shared_ptr<QtMenu> menu) = 0;
};

#endif //QTVIEWS_QTMENUVISITOR_H