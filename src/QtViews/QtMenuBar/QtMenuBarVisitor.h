#ifndef QTVIEWS_QTMENUBARVISITOR_H
#define QTVIEWS_QTMENUBARVISITOR_H

#include <memory>

class QtMenuBar;

class QtMenuBarVisitor;
typedef std::shared_ptr<QtMenuBarVisitor> QtMenuBarVisitorPtr;

class QtMenuBarVisitor {
public:
    virtual void visit(std::shared_ptr<QtMenuBar> menuBar) = 0;
};

#endif //QTVIEWS_QTMENUBARVISITOR_H