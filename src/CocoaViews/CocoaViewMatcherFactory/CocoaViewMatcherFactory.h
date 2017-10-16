#ifndef COCOAVIEWS_COCOAVIEWMATCHERFACTORY_H
#define COCOAVIEWS_COCOAVIEWMATCHERFACTORY_H

#include <memory>

class CNMatcher;
class CNVisitor;

class CocoaViewMatcherFactory;
typedef std::shared_ptr<CocoaViewMatcherFactory> CocoaViewMatcherFactoryPtr;

class CocoaViewMatcherFactory {
public:
    static CocoaViewMatcherFactoryPtr getNewInstance();
    virtual ~CocoaViewMatcherFactory();
private:
    CocoaViewMatcherFactory();

public:
    virtual std::shared_ptr<CNMatcher> makeTopLevelMatcher();
    virtual std::shared_ptr<CNMatcher> makeShellTypeMatcher();
private:
    virtual std::shared_ptr<CNMatcher> makeCNNullMatcher();
    virtual std::shared_ptr<CNMatcher> makeCNTypeMatcher(std::shared_ptr<CNVisitor> matchingVisitor);
};

#endif //COCOAVIEWS_COCOAVIEWMATCHERFACTORY_H