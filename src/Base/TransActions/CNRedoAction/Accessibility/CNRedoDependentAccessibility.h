#ifndef CROSSNATIVE_REDODEPENDENTACCESSIBILITY_H
#define CROSSNATIVE_REDODEPENDENTACCESSIBILITY_H

#include "Base/CNTransActionAppearance/CNTransActionAccessibility.h"

class CNCommandHistory;

class CNRedoDependentAccessibility;
typedef std::shared_ptr<CNRedoDependentAccessibility> CNRedoDependentAccessibilityPtr;

class CNRedoDependentAccessibility : public CNTransActionAccessibility {
public:
    static CNRedoDependentAccessibilityPtr getNewInstance(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual ~CNRedoDependentAccessibility();
private:
    CNRedoDependentAccessibility(std::shared_ptr<CNCommandHistory> commandHistory);

public:
    virtual bool isAccessible() override;

private:
    std::shared_ptr<CNCommandHistory> commandHistory;
};

#endif //CROSSNATIVE_REDODEPENDENTACCESSIBILITY_H