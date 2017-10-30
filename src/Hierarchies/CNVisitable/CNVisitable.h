#ifndef CROSSNATIVE_VISITABLE_H
#define CROSSNATIVE_VISITABLE_H

#include "Hierarchies/CNVisitor/CNVisitor.h"
#include "CNVisitableVisitorMismatchException.h"

class CNVisitable;
typedef std::shared_ptr<CNVisitable> CNVisitablePtr;

class CNVisitable {
public:
    virtual ~CNVisitable() {}

protected:
    CNVisitable() {}

public:
    virtual void accept(CNVisitorPtr visitor) = 0;
};

#endif //CROSSNATIVE_VISITABLE_H