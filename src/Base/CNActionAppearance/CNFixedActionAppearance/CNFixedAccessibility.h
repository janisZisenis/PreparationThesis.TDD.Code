#ifndef CROSSNATIVE_FIXEDACCESSIBILITY_H
#define CROSSNATIVE_FIXEDACCESSIBILITY_H

#include <Base/CNTransActionAppearance/CNActionAccessibility.h>

class CNFixedAccessibility;
typedef std::shared_ptr<CNFixedAccessibility> CNFixedAccessibilityPtr;

class CNFixedAccessibility : public CNActionAccessibility {
public:
    static CNFixedAccessibilityPtr getNewInstance(bool accessibility = true);
    virtual ~CNFixedAccessibility();
private:
    CNFixedAccessibility(bool accessibility);

public:
    virtual bool isAccessible() override;

private:
    bool accessibility;
};

#endif //CROSSNATIVE_FIXEDACCESSIBILITY_H