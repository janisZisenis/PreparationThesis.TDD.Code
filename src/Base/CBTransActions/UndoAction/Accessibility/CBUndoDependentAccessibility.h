#ifndef CODEBASEIMP_UNDOPOSSIBLEDEPENDENTACCESSIBILITY_H
#define CODEBASEIMP_UNDOPOSSIBLEDEPENDENTACCESSIBILITY_H

#include "Base/CBTransActionAppearance/CBActionAccessibility.h"

class CBCommandHistory;

class CBUndoDependentAccessibility;
typedef std::shared_ptr<CBUndoDependentAccessibility> CBUndoDependentAccessibilityPtr;

class CBUndoDependentAccessibility : public CBActionAccessibility {
public:
    static CBUndoDependentAccessibilityPtr getNewInstance(std::shared_ptr<CBCommandHistory> commandHistory);
    virtual ~CBUndoDependentAccessibility();
private:
    CBUndoDependentAccessibility(std::shared_ptr<CBCommandHistory> commandHistory);

public:
    virtual bool isAccessible() override;

private:
    std::shared_ptr<CBCommandHistory> commandHistory;
};

#endif //CODEBASEIMP_UNDOPOSSIBLEDEPENDENTACCESSIBILITY_H