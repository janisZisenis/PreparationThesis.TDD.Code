#ifndef CROSSNATIVE_FAKEVIEW_H
#define CROSSNATIVE_FAKEVIEW_H

#include "CNView.h"

class CNFakeView;
typedef std::shared_ptr<CNFakeView> CNFakeViewPtr;

class CNFakeView : public CNView {
public:
    static CNFakeViewPtr getNewInstance() {
        return CNFakeViewPtr(new CNFakeView());
    }
    virtual ~CNFakeView() {};
protected:
    CNFakeView() {};

public:
    virtual void add(CNViewPtr view) override {
        children.push_back(view);
    }
    virtual void remove(CNViewPtr view) override {
        children.erase(std::find(children.begin(), children.end(), view));
    }
    virtual bool isParentOf(CNViewPtr view) override {
        return std::find(children.begin(), children.end(), view) != children.end();
    }
private:
    std::vector<CNViewPtr> children;
};


#endif //CROSSNATIVE_FAKEVIEW_H