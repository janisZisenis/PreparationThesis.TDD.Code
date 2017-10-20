#ifndef CROSSVIEWS_FAKESELECTIONMODEL_H
#define CROSSVIEWS_FAKESELECTIONMODEL_H

#include "SelectionModel.h"

class FakeSelectionModel;
typedef std::shared_ptr<FakeSelectionModel> FakeSelectionModelPtr;

class FakeSelectionModel : public SelectionModel {
public:
    static FakeSelectionModelPtr getNewInstance() {
        return FakeSelectionModelPtr(new FakeSelectionModel());
    }
    virtual ~FakeSelectionModel() {};
protected:
    FakeSelectionModel() {};

public:
    virtual void setSelectedIndex(const HierarchyIndex& index) override {
        selected = index;
    }

    const HierarchyIndex getSelectedIndex() override {
        return selected;
    }

    bool hasSelection() override {
        return selected.isValid();
    }

private:
    HierarchyIndex selected;
};

#endif //CROSSVIEWS_FAKESELECTIONMODEL_H
