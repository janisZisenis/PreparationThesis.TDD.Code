#ifndef CROSSNATIVE_ACTIONACCESSIBILITY_H
#define CROSSNATIVE_ACTIONACCESSIBILITY_H

#include <memory>

class CNActionAccessibility;
typedef std::shared_ptr<CNActionAccessibility> CNActionAccessibilityPtr;

class CNActionAccessibility {
public:
    virtual ~CNActionAccessibility() {};
protected:
    CNActionAccessibility() {};

public:
    virtual bool isAccessible() = 0;
};

#endif //CROSSNATIVE_ACTIONACCESSIBILITY_H