#ifndef CODEBASEIMP_FIXEDACCESSIBILITY_H
#define CODEBASEIMP_FIXEDACCESSIBILITY_H

#include <Base/CBTransActionAppearance/CBActionAccessibility.h>

class CBFixedAccessibility;
typedef std::shared_ptr<CBFixedAccessibility> CBFixedAccessibilityPtr;

class CBFixedAccessibility : public CBActionAccessibility {
public:
    static CBFixedAccessibilityPtr getNewInstance(bool accessibility = true);
    virtual ~CBFixedAccessibility();
private:
    CBFixedAccessibility(bool accessibility);

public:
    virtual bool isAccessible() override;

private:
    bool accessibility;
};

#endif //CODEBASEIMP_FIXEDACCESSIBILITY_H