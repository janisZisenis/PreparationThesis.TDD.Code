#ifndef CROSSNATIVE_MATCHERFACTORY_H
#define CROSSNATIVE_MATCHERFACTORY_H

#include <memory>
#include <vector>
#include <string>

class CNMatcher;
class CNIdentifyingVisitor;
class CNMultiMatcher;

class CNMatcherFactory;
typedef std::shared_ptr<CNMatcherFactory> CNMatcherFactoryPtr;

class CNMatcherFactory {
public:
    static CNMatcherFactoryPtr getNewInstance();
    virtual ~CNMatcherFactory();
private:
    CNMatcherFactory();

public:
    virtual std::shared_ptr<CNMatcher> makeCNNullMatcher();
    virtual std::shared_ptr<CNMatcher> makeCNVisitingMatcher(std::shared_ptr<CNIdentifyingVisitor> identifier);
    virtual std::shared_ptr<CNMatcher> makeCNTagMatcher(std::string tag);
    virtual std::shared_ptr<CNMatcher> makeCNMultiMatcher(std::vector< std::shared_ptr<CNMatcher> > matchers);
};


#endif //CROSSNATIVE_MATCHERFACTORY_H