#ifndef CROSSNATIVE_TRANSACTIONACCESSIBILITY_H
#define CROSSNATIVE_TRANSACTIONACCESSIBILITY_H

#include <memory>

class CNTransActionAccessibility;
typedef std::shared_ptr<CNTransActionAccessibility> CNTransActionAccessibilityPtr;

class CNTransActionAccessibility {
public:
    virtual ~CNTransActionAccessibility() {};
protected:
    CNTransActionAccessibility() {};

public:
    virtual bool isAccessible() = 0;
};

#endif //CROSSNATIVE_TRANSACTIONACCESSIBILITY_H