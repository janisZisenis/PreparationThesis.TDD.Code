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
    virtual void setSelectedIndex(const HierarchyIndex& index) override {}
};

class SelectionModelSpy;
typedef std::shared_ptr<SelectionModelSpy> SelectionModelSpyPtr;

class SelectionModelSpy : public SelectionModelDummy {
public:
    static SelectionModelSpyPtr getNewInstance() {
        return SelectionModelSpyPtr(new SelectionModelSpy());
    }
    virtual ~SelectionModelSpy() {};
protected:
    SelectionModelSpy() {};

public:
    virtual void setSelectedIndex(const HierarchyIndex& index) override {
        selected = index;
    }

    virtual const HierarchyIndex& getSelectedIndex() {
        return selected;
    }

private:
    HierarchyIndex selected;
};

#endif //CROSSVIEWS_SELECTIONMODEL_TESTDOUBLES_H
