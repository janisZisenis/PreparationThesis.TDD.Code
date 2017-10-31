#ifndef CROSSNATIVE_SELECTIONMODEL_TESTDOUBLES_H
#define CROSSNATIVE_SELECTIONMODEL_TESTDOUBLES_H

#include "CNSelectionModel.h"

class CNSelectionModelDummy;
typedef std::shared_ptr<CNSelectionModelDummy> CNSelectionModelDummyPtr;
class CNSelectionModelDummy : public CNSelectionModel {
public:
    static CNSelectionModelDummyPtr getNewInstance() {
        return CNSelectionModelDummyPtr(new CNSelectionModelDummy());
    }

    virtual ~CNSelectionModelDummy() {};
protected:
    CNSelectionModelDummy() {};

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

#endif //CROSSNATIVE_SELECTIONMODEL_TESTDOUBLES_H
