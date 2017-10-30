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
    virtual void setSelectedIndex(const CNHierarchyIndex &index) override {}
    virtual CNHierarchyIndex getSelectedIndex() override {
        return CNHierarchyIndex();
    }
    virtual bool hasSelection() override {
        return false;
    }

    void attach(std::shared_ptr<CNObserver> observer) override {}
    void detach(std::shared_ptr<CNObserver> observer) override {}

};

#endif //CROSSVIEWS_SELECTIONMODEL_TESTDOUBLES_H
