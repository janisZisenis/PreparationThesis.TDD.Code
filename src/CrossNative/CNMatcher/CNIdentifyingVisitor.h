#ifndef CROSSNATIVE_IDENTIFYINGVISITOR_H
#define CROSSNATIVE_IDENTIFYINGVISITOR_H

#include "CrossNative/CNVisitor/CNVisitor.h"

class CNIdentifyingVisitor;
typedef std::shared_ptr<CNIdentifyingVisitor> CNIdentifyingVisitorPtr;

class CNIdentifyingVisitor : public CNVisitor {
public:
    virtual ~CNIdentifyingVisitor() {}

protected:
    CNIdentifyingVisitor() {}

public:
    virtual bool hasIdentified() = 0;
};

#endif //CROSSNATIVE_IDENTIFYINGVISITOR_H