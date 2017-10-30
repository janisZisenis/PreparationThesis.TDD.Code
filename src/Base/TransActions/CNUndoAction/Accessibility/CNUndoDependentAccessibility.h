#ifndef CROSSNATIVE_UNDOPOSSIBLEDEPENDENTACCESSIBILITY_H
#define CROSSNATIVE_UNDOPOSSIBLEDEPENDENTACCESSIBILITY_H

#include "Base/CNTransActionAppearance/CNActionAccessibility.h"

class CNCommandHistory;

class CNUndoDependentAccessibility;
typedef std::shared_ptr<CNUndoDependentAccessibility> CNUndoDependentAccessibilityPtr;

class CNUndoDependentAccessibility : public CNActionAccessibility {
public:
    static CNUndoDependentAccessibilityPtr getNewInstance(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual ~CNUndoDependentAccessibility();
private:
    CNUndoDependentAccessibility(std::shared_ptr<CNCommandHistory> commandHistory);

public:
    virtual bool isAccessible() override;

private:
    std::shared_ptr<CNCommandHistory> commandHistory;
};

#endif //CROSSNATIVE_UNDOPOSSIBLEDEPENDENTACCESSIBILITY_H