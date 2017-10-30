#ifndef CROSSVIEWS_SELECTIONDEPENDENTACCESSIBILITY_H
#define CROSSVIEWS_SELECTIONDEPENDENTACCESSIBILITY_H

#include <Base/CNTransActionAppearance/CNActionAccessibility.h>

class SelectionModel;

class SelectionDependentAccessibility;
typedef std::shared_ptr<SelectionDependentAccessibility> SelectionDependentAccessibilityPtr;

class SelectionDependentAccessibility : public CNActionAccessibility {
public:
    static SelectionDependentAccessibilityPtr getNewInstance(std::shared_ptr<SelectionModel> selectionModel);
    virtual ~SelectionDependentAccessibility();
private:
    SelectionDependentAccessibility(std::shared_ptr<SelectionModel> selectionModel);

public:
    virtual bool isAccessible() override;

private:
    std::shared_ptr<SelectionModel> selectionModel;
};

#endif //CROSSVIEWS_SELECTIONDEPENDENTACCESSIBILITY_H