#ifndef CODEBASE_ACTIONACCESSIBILITY_H
#define CODEBASE_ACTIONACCESSIBILITY_H

#include <memory>

class CBActionAccessibility;
typedef std::shared_ptr<CBActionAccessibility> CBActionAccessibilityPtr;

class CBActionAccessibility {
public:
    virtual ~CBActionAccessibility() {};
protected:
    CBActionAccessibility() {};

public:
    virtual bool isAccessible() = 0;
};

#endif //CODEBASE_ACTIONACCESSIBILITY_H