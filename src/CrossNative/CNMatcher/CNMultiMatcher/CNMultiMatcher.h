#ifndef CROSSNATIVE_MULTIMATCHER_H
#define CROSSNATIVE_MULTIMATCHER_H

#include "CrossNative/CNMatcher/CNMatcher.h"

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
};

#endif //CROSSNATIVE_MULTIMATCHER_H
