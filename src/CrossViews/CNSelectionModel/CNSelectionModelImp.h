#ifndef CROSSNATIVE_SELECTIONMODELIMP_H
#define CROSSNATIVE_SELECTIONMODELIMP_H

#include "CNSelectionModel.h"
#include <Hierarchies/CNHierarchy/CNHierarchyIndex.h>

class CNSubject;

class CNSelectionModelImp;
typedef std::shared_ptr<CNSelectionModelImp> CNSelectionModelImpPtr;

class CNSelectionModelImp : public CNSelectionModel {
public:
    static CNSelectionModelImpPtr getNewInstance();
    virtual ~CNSelectionModelImp();
protected:
    CNSelectionModelImp();

public:
    virtual bool hasSelection() override;
    virtual void setSelectedIndex(const CNHierarchyIndex& index) override;
    virtual CNHierarchyIndex getSelectedIndex() override;

    virtual void attach(std::shared_ptr<CNObserver> observer) override;
    virtual void detach(std::shared_ptr<CNObserver> observer) override;
    virtual void notifyObservers();

private:
    std::shared_ptr<CNSubject> subject;
    CNHierarchyIndex selectedIndex;
};

#endif //CROSSNATIVE_SELECTIONMODELIMP_H
