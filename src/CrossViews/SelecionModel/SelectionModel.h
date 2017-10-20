#ifndef CROSSVIEWS_SELECTIONMODEL_H
#define CROSSVIEWS_SELECTIONMODEL_H

#include <memory>
#include "CrossViews/HierarchyIndex/HierarchyIndex.h"

class SelectionModel;
typedef std::shared_ptr<SelectionModel> SelectionModelPtr;

class SelectionModel {
public:
    virtual ~SelectionModel() {};
protected:
    SelectionModel() {};

public:
    virtual void setSelectedIndex(const HierarchyIndex& index) = 0;
};

#endif //CROSSVIEWS_SELECTIONMODEL_H
