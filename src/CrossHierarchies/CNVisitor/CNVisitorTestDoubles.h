#ifndef CROSSNATIVE_VISITOR_TESTDOUBLES_H
#define CROSSNATIVE_VISITOR_TESTDOUBLES_H

#include "CNVisitor.h"

class CNVisitorDummy;
typedef std::shared_ptr<CNVisitorDummy> CNVisitorDummyPtr;
class CNVisitorDummy : public CNVisitor {
public:
    static CNVisitorDummyPtr getNewInstance() {
        return CNVisitorDummyPtr(new CNVisitorDummy());
    };

    virtual ~CNVisitorDummy() {};
private:
    CNVisitorDummy() {};
};

#endif //CROSSNATIVE_VISITOR_TESTDOUBLES_H