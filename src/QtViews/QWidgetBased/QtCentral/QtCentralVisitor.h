#ifndef QTVIEWS_QTCENTRALVISITOR_H
#define QTVIEWS_QTCENTRALVISITOR_H

#include <memory>

class QtCentral;

class QtCentralVisitor;
typedef std::shared_ptr<QtCentralVisitor> QtCentralVisitorPtr;

class QtCentralVisitor {
public:
    virtual void visit(std::shared_ptr<QtCentral> central) = 0;
};

#endif //QTVIEWS_QTCENTRALVISITOR_H