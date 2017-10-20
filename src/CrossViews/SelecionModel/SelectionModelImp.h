#ifndef CROSSVIEWS_SELECTIONMODELIMP_H
#define CROSSVIEWS_SELECTIONMODELIMP_H

#include "SelectionModel.h"

class SelectionModelImp;
typedef std::shared_ptr<SelectionModelImp> SelectionModelImpPtr;

class SelectionModelImp : public SelectionModel {
public:
    static SelectionModelImpPtr getNewInstance() {
        return SelectionModelImpPtr(new SelectionModelImp());
    }
    virtual ~SelectionModelImp() {};
protected:
    SelectionModelImp() {};

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

#endif //CROSSVIEWS_SELECTIONMODELIMP_H
