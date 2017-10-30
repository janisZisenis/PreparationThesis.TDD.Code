#ifndef CROSSNATIVE_MULTIMATCHER_H
#define CROSSNATIVE_MULTIMATCHER_H

#include "CrossHierarchies/CNMatcher/CNMatcher.h"
#include <vector>

class CNIdentifyingVisitor;

class CNMultiMatcher;
typedef std::shared_ptr<CNMultiMatcher> CNMultiMatcherPtr;

class CNMultiMatcher : public CNMatcher {
public:
    static CNMultiMatcherPtr getNewInstance();
    virtual ~CNMultiMatcher();
protected:
    CNMultiMatcher();

public:
    virtual bool matches(std::shared_ptr<CNVisitable> visitable) override;
    virtual void add(CNMatcherPtr matcher);

private:
    std::vector<CNMatcherPtr> matchers;
};

#endif //CROSSNATIVE_MULTIMATCHER_H
