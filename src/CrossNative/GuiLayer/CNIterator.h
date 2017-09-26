#ifndef CROSSNATIVE_ITERATOR_H
#define CROSSNATIVE_ITERATOR_H

#include <memory>

class CNView;

class CNIterator;
typedef std::shared_ptr<CNIterator> CNIteratorPtr;

class CNIterator {
public:
    virtual ~CNIterator() {};
protected:
    CNIterator() {};

public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() = 0;
    virtual std::shared_ptr<CNView> current() = 0;
};


#endif //CROSSNATIVE_ITERATOR_H