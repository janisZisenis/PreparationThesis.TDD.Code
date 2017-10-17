#ifndef CROSSNATIVE_TAGGEDVISITOR_H
#define CROSSNATIVE_TAGGEDVISITOR_H

#include <memory>

class CNTagged;

class CNTaggedVisitor;
typedef std::shared_ptr<CNTaggedVisitor> CNTaggedVisitorPtr;

class CNTaggedVisitor {
public:
    virtual ~CNTaggedVisitor() {}
protected:
    CNTaggedVisitor() {}

public:
    virtual void visit(std::shared_ptr<CNTagged> tagged) = 0;
};

#endif //CROSSNATIVE_TAGGEDVISITOR_H
