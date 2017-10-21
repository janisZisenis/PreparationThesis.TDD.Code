#ifndef IRMB_SELECTIONMODELIMP_H
#define IRMB_SELECTIONMODELIMP_H

#include <CrossViews/SelecionModel/SelectionModel.h>
#include <CrossNative/CNHierarchy/CNHierarchyIndex.h>
#include "HasSelectionProvider.h"

class CBObserver;
class CBSubject;

class SelectionModelImp;
typedef std::shared_ptr<SelectionModelImp> SelectionModelImpPtr;

class SelectionModelImp : public SelectionModel, public HasSelectionProvider {
public:
    static SelectionModelImpPtr getNewInstance();
    virtual ~SelectionModelImp();
protected:
    SelectionModelImp();

public:
    virtual bool hasSelection() override;
    virtual void setSelectedIndex(const CNHierarchyIndex& index) override;
    virtual CNHierarchyIndex getSelectedIndex() override;

    virtual void attach(std::shared_ptr<CBObserver> observer);
    virtual void detach(std::shared_ptr<CBObserver> observer);
    virtual void notifyObservers();

private:
    std::shared_ptr<CBSubject> subject;
    CNHierarchyIndex selectedIndex;
};

#endif //IRMB_SELECTIONMODELIMP_H
