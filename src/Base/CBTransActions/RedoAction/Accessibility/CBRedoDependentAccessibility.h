#ifndef CODEBASEIMP_REDODEPENDENTACCESSIBILITY_H
#define CODEBASEIMP_REDODEPENDENTACCESSIBILITY_H

#include "Base/CBTransActionAppearance/CBActionAccessibility.h"

class CBCommandHistory;

class CBRedoDependentAccessibility;
typedef std::shared_ptr<CBRedoDependentAccessibility> CBRedoDependentAccessibilityPtr;

class CBRedoDependentAccessibility : public CBActionAccessibility {
public:
    static CBRedoDependentAccessibilityPtr getNewInstance(std::shared_ptr<CBCommandHistory> commandHistory);
    virtual ~CBRedoDependentAccessibility();
private:
    CBRedoDependentAccessibility(std::shared_ptr<CBCommandHistory> commandHistory);

public:
    virtual bool isAccessible() override;

private:
    std::shared_ptr<CBCommandHistory> commandHistory;
};

#endif //CODEBASEIMP_REDODEPENDENTACCESSIBILITY_H