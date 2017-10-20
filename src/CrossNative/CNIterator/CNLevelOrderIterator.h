#ifndef CROSSNATIVE_LEVELORDERITERATOR_H
#define CROSSNATIVE_LEVELORDERITERATOR_H

#include "CNIterator.h"
#include "CrossNative/CNComponent/CNComponent.h"
#include <queue>


class CNLevelOrderIterator;
typedef std::shared_ptr<CNLevelOrderIterator> CNLevelOrderIteratorPtr;

class CNLevelOrderIterator : public CNIterator {
public:
    static CNLevelOrderIteratorPtr getNewInstance(std::shared_ptr<CNComponent> root) {
        return CNLevelOrderIteratorPtr(new CNLevelOrderIterator(root));
    }
    virtual ~CNLevelOrderIterator() {}
private:
    CNLevelOrderIterator(std::shared_ptr<CNComponent> root) {
//        queue.push(root->begin());
    }

public:
    virtual void next() override {
//        if(isDone()) return;
//
//        if(!queue.front()->current()->begin()->isDone())
//            queue.push(queue.front()->current()->begin());
//
//        queue.front()->next();
//
//        if(queue.front()->isDone()) queue.pop();
    }
    virtual bool isDone() override {
//        return queue.empty();
        return true;
    }

    virtual std::shared_ptr<CNComponent> current() override {
//        if(isDone()) throw CNIteratorOutOfBoundsException();
//        return queue.front()->current();
        return nullptr;
    }

private:
    std::queue<CNIteratorPtr>  queue;
};

#endif //CROSSNATIVE_LEVELORDERITERATOR_H