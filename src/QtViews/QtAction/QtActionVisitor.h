#ifndef QTVIEWS_QTACTIONVISITOR_H
#define QTVIEWS_QTACTIONVISITOR_H

#include <memory>

class QtAction;

class QtActionVisitor;
typedef std::shared_ptr<QtActionVisitor> QtActionVisitorPtr;

class QtActionVisitor {
public:
    virtual void visit(std::shared_ptr<QtAction> action) = 0;
};

#endif //QTVIEWS_QTACTIONVISITOR_H