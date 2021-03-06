#ifndef CROSSNATIVE_FAKESELECTIONMODEL_H
#define CROSSNATIVE_FAKESELECTIONMODEL_H

#include "CNSelectionModel.h"
#include <Base/CNObserver/CNObserver.h>

class CNFakeSelectionModel;
typedef std::shared_ptr<CNFakeSelectionModel> CNFakeSelectionModelPtr;

class CNFakeSelectionModel : public CNSelectionModel {
public:
    static CNFakeSelectionModelPtr getNewInstance() {
        return CNFakeSelectionModelPtr(new CNFakeSelectionModel());
    }
    virtual ~CNFakeSelectionModel() {};
protected:
    CNFakeSelectionModel() {};

public:
    virtual void setSelectedIndex(const CNHierarchyIndex& index) override {
        selected = index;
        notify();
    }
    virtual CNHierarchyIndex getSelectedIndex() override {
        return selected;
    }
    virtual bool hasSelection() override {
        return selected.isValid();
    }

    void attach(std::shared_ptr<CNObserver> observer) override {
        observers.push_back(observer);
    }
    void detach(std::shared_ptr<CNObserver> observer) override {
        removeObserver(findPosition(observer));
    }

private:
    virtual void notify() {
        for(int i = 0; i < observers.size(); i++)
            (observers[i].lock() != nullptr) ? update(observers[i].lock()) : removeObserver(i--);
    }
    virtual void update(std::shared_ptr<CNObserver> observer) {
        observer->update();
    }
    virtual void removeObserver(int position) {
        observers.erase(observers.begin() + position);
    }
    int findPosition(std::shared_ptr<CNObserver> observer) {
        for(int i = 0; i < observers.size(); i++) {
            if(observers[i].lock() && observers[i].lock() == observer)
                return i;
        }

        return -1;
    }

private:
    CNHierarchyIndex selected;
    std::vector< std::weak_ptr<CNObserver> > observers;
};

#endif //CROSSNATIVE_FAKESELECTIONMODEL_H
