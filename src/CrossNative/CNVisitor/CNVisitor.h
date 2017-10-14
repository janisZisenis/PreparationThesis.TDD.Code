#ifndef CROSSNATIVE_VISITOR_H
#define CROSSNATIVE_VISITOR_H

#include <memory>

class CNVisitor;
typedef std::shared_ptr<CNVisitor> CNVisitorPtr;

class CNVisitor {
public:
    virtual ~CNVisitor() {}

protected:
    CNVisitor() {}
};

#endif //CROSSNATIVE_VISITOR_H