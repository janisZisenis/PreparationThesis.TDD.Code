#ifndef CROSSNATIVE_FAKECOMPONENT_H
#define CROSSNATIVE_FAKECOMPONENT_H

#include "CNComponent.h"

class CNFakeComponent;
typedef std::shared_ptr<CNFakeComponent> CNFakeComponentPtr;

class CNFakeComponent : public CNComponent {
public:
    static CNFakeComponentPtr getNewInstance() {
        return CNFakeComponentPtr(new CNFakeComponent());
    }
    virtual ~CNFakeComponent() {};
protected:
    CNFakeComponent() {};

public:
    virtual void add(CNComponentPtr view) override {
        children.push_back(view);
    }
    virtual void remove(CNComponentPtr view) override {
        children.erase(std::find(children.begin(), children.end(), view));
    }
    virtual bool isParentOf(CNComponentPtr view) override {
        return std::find(children.begin(), children.end(), view) != children.end();
    }

    virtual void accept(std::shared_ptr<CNVisitor> visitor) override {}
private:
    std::vector<CNComponentPtr> children;
};


#endif //CROSSNATIVE_FAKECOMPONENT_H