#ifndef CROSSNATIVE_TYPEMATCHER_H
#define CROSSNATIVE_TYPEMATCHER_H

#include <CrossNative/CrossNative_EXPORT.h>
#include "CNMatcher.h"

class CNVisitor;

class CNTypeMatcher;
typedef std::shared_ptr<CNTypeMatcher> CNTypeMatcherPtr;

class CrossNative_EXPORT CNTypeMatcher : public CNMatcher {
public:
    static CNTypeMatcherPtr getNewInstance(std::shared_ptr<CNVisitor> typeIdentifier);
    virtual ~CNTypeMatcher();
protected:
    CNTypeMatcher(std::shared_ptr<CNVisitor> matching);

public:
    virtual bool matches(std::shared_ptr<CNVisitable> visitable) override;

private:
    std::shared_ptr<CNVisitor> typeIdentifier;
};

#endif //CROSSNATIVE_TYPEMATCHER_H
