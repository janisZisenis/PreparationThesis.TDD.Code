#ifndef CROSSNATIVE_NULLMATCHER_H
#define CROSSNATIVE_NULLMATCHER_H

#include "CNMatcher.h"

class CNNullMatcher;
typedef std::shared_ptr<CNNullMatcher> CNNullMatcherPtr;

class CNNullMatcher : public CNMatcher {
public:
    static CNNullMatcherPtr getNewInstance() {
        return CNNullMatcherPtr(new CNNullMatcher());
    }
    virtual ~CNNullMatcher() {};
protected:
    CNNullMatcher() {};

public:
    virtual bool matches(std::shared_ptr<CNVisitable> visitable) {
        return false;
    }
};

#endif //CROSSNATIVE_NULLMATCHER_H
