#ifndef CROSSVIEWS_SELECTIONMODEL_TESTDOUBLES_H
#define CROSSVIEWS_SELECTIONMODEL_TESTDOUBLES_H

#include "SelectionModel.h"

class SelectionModelDummy;
typedef std::shared_ptr<SelectionModelDummy> SelectionModelDummyPtr;
class SelectionModelDummy : public SelectionModel {
public:
    static SelectionModelDummyPtr getNewInstance() {
        return SelectionModelDummyPtr(new SelectionModelDummy());
    }

    virtual ~SelectionModelDummy() {};
protected:
    SelectionModelDummy() {};

public:
    virtual void setSelectedIndex(const HierarchyIndex &index) override {}
    virtual const HierarchyIndex getSelectedIndex() override {
        return HierarchyIndex();
    }
    virtual bool hasSelection() override {
        return false;
    }
};

#endif //CROSSVIEWS_SELECTIONMODEL_TESTDOUBLES_H
