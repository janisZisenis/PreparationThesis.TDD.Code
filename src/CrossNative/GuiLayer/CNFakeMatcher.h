#ifndef CROSSNATIVE_FAKEMATCHER_H
#define CROSSNATIVE_FAKEMATCHER_H

#include "CNMatcher.h"

class CNFakeMatcher;
typedef std::shared_ptr<CNFakeMatcher> CNFakeMatcherPtr;

class CNFakeMatcher : public CNMatcher {
public:
    static CNFakeMatcherPtr getNewInstance(std::shared_ptr<CNView> matchingView) {
        return CNFakeMatcherPtr(new CNFakeMatcher(matchingView));
    }
    virtual ~CNFakeMatcher() {};
protected:
    CNFakeMatcher(std::shared_ptr<CNView> matchingView) : matchingView(matchingView) {};

public:
    virtual bool matches(std::shared_ptr<CNView> view) {
        return view == matchingView;
    }
private:
    std::shared_ptr<CNView> matchingView;
};


#endif //CROSSNATIVE_FAKEMATCHER_H