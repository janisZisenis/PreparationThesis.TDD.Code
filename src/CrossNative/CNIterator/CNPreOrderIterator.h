#ifndef CROSSNATIVE_PREORDERITERATOR_H
#define CROSSNATIVE_PREORDERITERATOR_H

#include "CNIterator.h"
#include "CrossNative/CNComponent/CNComponent.h"
#include <stack>

class CNPreOrderIterator;
typedef std::shared_ptr<CNPreOrderIterator> CNPreOrderIteratorPtr;
class CNPreOrderIterator : public CNIterator {
public:
    static CNPreOrderIteratorPtr getNewInstance(std::shared_ptr<CNComponent> root) {
        return CNPreOrderIteratorPtr(new CNPreOrderIterator(root));
    }
    virtual ~CNPreOrderIterator() {};
private:
    CNPreOrderIterator(std::shared_ptr<CNComponent> root) {
//        iterators.push(root->begin());
    }

public:
    virtual void next() override {
//        if(isDone()) return;
//
//        iterators.push(iterators.top()->current()->begin());
//
//        while(iterators.size() > 1 && iterators.top()->isDone()) {
//            iterators.pop();
//            iterators.top()->next();
//        }
    }
    virtual bool isDone() override {
//        return iterators.size() == 1 && iterators.top()->isDone();
        return true;
    }
    virtual std::shared_ptr<CNComponent> current() override {
//        return iterators.top()->current();
        return nullptr;
    }

private:
    std::stack<CNIteratorPtr> iterators;
};

#endif //CCORE_PREORDERITERATOR_H