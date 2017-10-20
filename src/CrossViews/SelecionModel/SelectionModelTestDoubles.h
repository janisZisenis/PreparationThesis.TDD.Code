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

class SelectionModelStub;
typedef std::shared_ptr<SelectionModelStub> SelectionModelStubPtr;
class SelectionModelStub : public SelectionModelDummy {
public:
    static SelectionModelStubPtr getNewInstance() {
        return SelectionModelStubPtr(new SelectionModelStub());
    }
    virtual ~SelectionModelStub() {};
protected:
    SelectionModelStub() {};

public:
    virtual void setSelectedIndex(const HierarchyIndex& index) override {
        selected = index;
    }
    virtual const HierarchyIndex getSelectedIndex() override {
        return selected;
    }

    virtual void setHasSelection(bool hasValidSelection) {
        this->hasValidSelection = hasValidSelection;
    }
    virtual bool hasSelection() override {
        return hasValidSelection;
    }
private:
    HierarchyIndex selected;
    bool hasValidSelection;
};

#endif //CROSSVIEWS_SELECTIONMODEL_TESTDOUBLES_H
