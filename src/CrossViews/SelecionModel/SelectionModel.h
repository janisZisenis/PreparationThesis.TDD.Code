#ifndef CROSSVIEWS_SELECTIONMODEL_H
#define CROSSVIEWS_SELECTIONMODEL_H

#include <memory>
#include "CrossNative/CNHierarchy/CNHierarchyIndex.h"

class SelectionModel;
typedef std::shared_ptr<SelectionModel> SelectionModelPtr;

class SelectionModel {
public:
    virtual ~SelectionModel() {};
protected:
    SelectionModel() {};

public:
    virtual void setSelectedIndex(const CNHierarchyIndex& index) = 0;
    virtual const CNHierarchyIndex getSelectedIndex() = 0;
    virtual bool hasSelection() = 0;
};

#endif //CROSSVIEWS_SELECTIONMODEL_H
