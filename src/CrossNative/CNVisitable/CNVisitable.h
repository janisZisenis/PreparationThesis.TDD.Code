#ifndef CROSSNATIVE_VISITABLE_H
#define CROSSNATIVE_VISITABLE_H

#include <memory>
#include <string>
#include "CrossNative/CNVisitor/CNVisitor.h"

class CNVisitorMismatchException : public std::exception {
    const char *what() const throw() override {
        return std::string("Could not accept the visitor because of a false visitor type!").c_str();
    }
};

class CNVisitable;
typedef std::shared_ptr<CNVisitable> CNVisitablePtr;

class CNVisitable {
public:
    virtual ~CNVisitable() {}

protected:
    CNVisitable() {}

public:
    virtual void accept(CNVisitorPtr visitor) = 0;
};

#endif //CROSSNATIVE_VISITABLE_H