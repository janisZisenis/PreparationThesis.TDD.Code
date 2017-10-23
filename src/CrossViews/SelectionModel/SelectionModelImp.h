#ifndef CROSSVIEWS_SELECTIONMODELIMP_H
#define CROSSVIEWS_SELECTIONMODELIMP_H

#include "SelectionModel.h"
#include <CrossNative/CNHierarchy/CNHierarchyIndex.h>

class CBSubject;

class SelectionModelImp;
typedef std::shared_ptr<SelectionModelImp> SelectionModelImpPtr;

class SelectionModelImp : public SelectionModel {
public:
    static SelectionModelImpPtr getNewInstance();
    virtual ~SelectionModelImp();
protected:
    SelectionModelImp();

public:
    virtual bool hasSelection() override;
    virtual void setSelectedIndex(const CNHierarchyIndex& index) override;
    virtual CNHierarchyIndex getSelectedIndex() override;

    virtual void attach(std::shared_ptr<CBObserver> observer) override;
    virtual void detach(std::shared_ptr<CBObserver> observer) override;
    virtual void notifyObservers();

private:
    std::shared_ptr<CBSubject> subject;
    CNHierarchyIndex selectedIndex;
};

#endif //CROSSVIEWS_SELECTIONMODELIMP_H
