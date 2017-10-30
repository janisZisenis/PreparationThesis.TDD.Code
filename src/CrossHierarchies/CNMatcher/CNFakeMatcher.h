#ifndef CROSSNATIVE_FAKEMATCHER_H
#define CROSSNATIVE_FAKEMATCHER_H

#include "CNMatcher.h"

class CNFakeMatcher;
typedef std::shared_ptr<CNFakeMatcher> CNFakeMatcherPtr;

class CNFakeMatcher : public CNMatcher {
public:
    static CNFakeMatcherPtr getNewInstance(std::shared_ptr<CNVisitable> matching) {
        return CNFakeMatcherPtr(new CNFakeMatcher(matching));
    }
    virtual ~CNFakeMatcher() {};
protected:
    CNFakeMatcher(std::shared_ptr<CNVisitable> matching) : matching(matching) {};

public:
    virtual bool matches(std::shared_ptr<CNVisitable> visitable) {
        return visitable == matching;
    }
private:
    std::shared_ptr<CNVisitable> matching;
};


#endif //CROSSNATIVE_FAKEMATCHER_H