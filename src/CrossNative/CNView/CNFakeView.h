#ifndef CROSSNATIVE_FAKEVIEW_H
#define CROSSNATIVE_FAKEVIEW_H

#include "CNView.h"

class CNFakeView;
typedef std::shared_ptr<CNFakeView> CNFakeViewPtr;

class CNFakeView : public CNView {
private:
    class Iterator;
    typedef std::shared_ptr<Iterator> IteratorPtr;
    class Iterator : public CNIterator {
    public:
        static IteratorPtr getNewInstance(std::vector<CNViewPtr> views) {
            return IteratorPtr(new Iterator(views));
        }
        virtual ~Iterator() {}
    private:
        Iterator(std::vector<CNViewPtr> views) : views(views) {}

    public:
        void first() override {
            initialized = true;
            it = views.begin();
        }
        void next() override {
            throwExceptionIfWasNotInitialized();

            it++;
        }
        bool isDone() override {
            throwExceptionIfWasNotInitialized();

            return it >= views.end();
        }
        CNViewPtr current() override {
            throwExceptionIfWasNotInitialized();

            return isDone() ? throw CNNotIteratorOutOfBoundsException() : *it;
        }
    private:
        virtual void throwExceptionIfWasNotInitialized() {
            if(!initialized) throw CNNotInitializedIteratorException();
        }

    private:
        bool initialized = false;
        std::vector<CNViewPtr> views;
        std::vector<CNViewPtr>::iterator it;
    };

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

    virtual CNIteratorPtr makeIterator() override {
        return Iterator::getNewInstance(children);
    }

    virtual CNViewPtr getChild(int position) override {
        return children[position];
    };
    virtual int getChildCount() override {
        return children.size();
    };

private:
    std::vector<CNViewPtr> children;
};


#endif //CROSSNATIVE_FAKEVIEW_H