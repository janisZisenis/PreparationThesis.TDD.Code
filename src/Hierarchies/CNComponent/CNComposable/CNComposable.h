#ifndef CROSSNATIVE_COMPOSABLE_H
#define CROSSNATIVE_COMPOSABLE_H

#include "Hierarchies/CNComponent/CNComponent.h"
#include <vector>

class CNComposer;

class CNComposable;
typedef std::shared_ptr<CNComposable> CNComposablePtr;
class CNComposable : public CNComponent {
public:
    static CNComposablePtr getNewInstance(CNVisitablePtr visitable, std::shared_ptr<CNComposer> composer);
    virtual  ~CNComposable();

protected:
    CNComposable(CNVisitablePtr visitable, std::shared_ptr<CNComposer> composer);

public:
    virtual bool isParentOf(CNComponentPtr component) override;
    virtual int getChildCount() override;
    virtual CNComponentPtr getChild(int childPos) override;

    virtual void add(std::shared_ptr<CNComponent> component) override;
    virtual void remove(std::shared_ptr<CNComponent> component) override;
    virtual void insert(std::shared_ptr<CNComponent> component, int childPos) override;
    virtual void remove(int childPos) override;

    virtual void accept(CNVisitorPtr visitor) override;
private:
    virtual void mount(CNComponentPtr component);
    virtual void dismount(CNComponentPtr component);
    virtual void dismountAllChildren();
    virtual bool isValidInsertingPosition(int childPos);
    virtual bool isValidChildPosition(int childPos);
    virtual void addToChildren(CNComponentPtr component);
    virtual void insertToChildren(CNComponentPtr component, int childPos);
    virtual void removeFromChildren(int childPos);
    virtual int findPosition(CNComponentPtr component);

private:
    CNVisitablePtr visitable;
    std::shared_ptr<CNComposer> composer;
    std::vector<CNComponentPtr> children;
};

#endif //CROSSNATIVE_COMPOSABLE_H