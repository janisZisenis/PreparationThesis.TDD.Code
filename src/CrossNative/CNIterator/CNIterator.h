#ifndef CROSSNATIVE_ITERATOR_H
#define CROSSNATIVE_ITERATOR_H

#include <memory>
#include "CNIteratorException.h"

class CNComponent;

class CNIterator;
typedef std::shared_ptr<CNIterator> CNIteratorPtr;

class CNIterator {
public:
    virtual void next() = 0;
    virtual bool isDone() = 0;
    virtual std::shared_ptr<CNComponent> current() = 0;
};

#endif //CROSSNATIVE_ITERATOR_H