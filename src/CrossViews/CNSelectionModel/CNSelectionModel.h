#ifndef CROSSNATIVE_SELECTIONMODEL_H
#define CROSSNATIVE_SELECTIONMODEL_H

#include <memory>
#include "Hierarchies/CNHierarchy/CNHierarchyIndex.h"

class CNObserver;

class CNSelectionModel;
typedef std::shared_ptr<CNSelectionModel> CNSelectionModelPtr;

class CNSelectionModel {
public:
    virtual ~CNSelectionModel() {};
protected:
    CNSelectionModel() {};

public:
    virtual void setSelectedIndex(const CNHierarchyIndex& index) = 0;
    virtual CNHierarchyIndex getSelectedIndex() = 0;
    virtual bool hasSelection() = 0;

    virtual void attach(std::shared_ptr<CNObserver> observer) = 0;
    virtual void detach(std::shared_ptr<CNObserver> observer) = 0;
};

#endif //CROSSNATIVE_SELECTIONMODEL_H
