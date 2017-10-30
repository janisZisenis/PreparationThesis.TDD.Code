#ifndef CROSSVIEWS_SELECTIONMODEL_H
#define CROSSVIEWS_SELECTIONMODEL_H

#include <memory>
#include "Hierarchies/CNHierarchy/CNHierarchyIndex.h"

class CNObserver;

class SelectionModel;
typedef std::shared_ptr<SelectionModel> SelectionModelPtr;

class SelectionModel {
public:
    virtual ~SelectionModel() {};
protected:
    SelectionModel() {};

public:
    virtual void setSelectedIndex(const CNHierarchyIndex& index) = 0;
    virtual CNHierarchyIndex getSelectedIndex() = 0;
    virtual bool hasSelection() = 0;

    virtual void attach(std::shared_ptr<CNObserver> observer) = 0;
    virtual void detach(std::shared_ptr<CNObserver> observer) = 0;
};

#endif //CROSSVIEWS_SELECTIONMODEL_H
