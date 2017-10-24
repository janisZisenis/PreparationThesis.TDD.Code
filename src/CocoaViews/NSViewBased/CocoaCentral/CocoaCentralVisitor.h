#ifndef COCOAVIEWS_COCOACENTRALVISITOR_H
#define COCOAVIEWS_COCOACENTRALVISITOR_H

#include <memory>

class CocoaCentral;

class CocoaCentralVisitor;
typedef std::shared_ptr<CocoaCentralVisitor> CocoaCentralVisitorPtr;

class CocoaCentralVisitor {
public:
    virtual void visit(std::shared_ptr<CocoaCentral> central) = 0;
};

#endif //COCOAVIEWS_COCOACENTRALVISITOR_H