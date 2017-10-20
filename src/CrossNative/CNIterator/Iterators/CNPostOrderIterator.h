#ifndef CROSSNATIVE_POSTORDERITERATOR_H
#define CROSSNATIVE_POSTORDERITERATOR_H

#include "CrossNative/CNIterator/CNIterator.h"
#include "CrossNative/CNComponent/CNComponent.h"
#include <stack>

class CNPostOrderIterator;
typedef std::shared_ptr<CNPostOrderIterator> CNPostOrderIteratorPtr;

class CNPostOrderIterator : public CNIterator {
public:
    static CNPostOrderIteratorPtr getNewInstance(CNComponentPtr root) {
        return CNPostOrderIteratorPtr(new CNPostOrderIterator(root));
    }
    virtual ~CNPostOrderIterator() {}
private:
CNPostOrderIterator(CNComponentPtr root) {
    pushNotDoneIteratorsToStackBeginningAt(root);
}

public:
    virtual void next() override {
        if(isDone()) return;
        iterators.top()->next();
        if(iterators.top()->isDone()) iterators.pop();
        else pushNotDoneIteratorsToStackBeginningAt(iterators.top()->current());
    }

    virtual bool isDone() override {
//        return iterators.size() == 0;
        return true;
    }
    virtual CNComponentPtr current() override {
//        if(isDone()) throw CNIteratorOutOfBoundsException();
//        return iterators.top()->current();
        return nullptr;
    }

private:
    virtual void pushNotDoneIteratorsToStackBeginningAt(CNComponentPtr component) {
//        iterators.push(component->begin());
//
//        while(!iterators.top()->isDone())
//            iterators.push(iterators.top()->current()->begin());
//
//        iterators.pop();
    }

    std::stack<CNIteratorPtr> iterators;
};

#endif //CROSSNATIVE_POSTORDERITERATOR_H