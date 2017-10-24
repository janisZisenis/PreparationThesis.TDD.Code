#ifndef COCOAVIEWS_COCOAVIEWMATCHERFACTORY_H
#define COCOAVIEWS_COCOAVIEWMATCHERFACTORY_H

#include <memory>
#include <string>

class CNMatcherFactory;
class CNMatcher;
class CNIdentifyingVisitor;

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
    virtual std::shared_ptr<CNMatcher> makeMenuBarTypeMatcher();
    virtual std::shared_ptr<CNMatcher> makeTagMatcher(std::string tag);
private:
    virtual std::shared_ptr<CNMatcher> makeCNNullMatcher();
    virtual std::shared_ptr<CNMatcher> makeCNVisitingMatcher(std::shared_ptr<CNIdentifyingVisitor> identifier);

private:
    std::shared_ptr<CNMatcherFactory> matcherFactory;
};

#endif //COCOAVIEWS_COCOAVIEWMATCHERFACTORY_H