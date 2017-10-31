#ifndef CROSSNATIVE_SELECTIONDEPENDENTACCESSIBILITY_H
#define CROSSNATIVE_SELECTIONDEPENDENTACCESSIBILITY_H

#include <Base/CNTransActionAppearance/CNTransActionAccessibility.h>

class CNSelectionModel;

class CNSelectionDependentAccessibility;
typedef std::shared_ptr<CNSelectionDependentAccessibility> CNSelectionDependentAccessibilityPtr;

class CNSelectionDependentAccessibility : public CNTransActionAccessibility {
public:
    static CNSelectionDependentAccessibilityPtr getNewInstance(std::shared_ptr<CNSelectionModel> selectionModel);
    virtual ~CNSelectionDependentAccessibility();
private:
    CNSelectionDependentAccessibility(std::shared_ptr<CNSelectionModel> selectionModel);

public:
    virtual bool isAccessible() override;

private:
    std::shared_ptr<CNSelectionModel> selectionModel;
};

#endif //CROSSNATIVE_SELECTIONDEPENDENTACCESSIBILITY_H