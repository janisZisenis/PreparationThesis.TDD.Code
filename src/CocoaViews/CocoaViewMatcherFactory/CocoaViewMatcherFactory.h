#ifndef COCOAVIEWS_COCOAVIEWMATCHERFACTORY_H
#define COCOAVIEWS_COCOAVIEWMATCHERFACTORY_H

#include <memory>

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
private:
    virtual std::shared_ptr<CNMatcher> makeCNNullMatcher();
    virtual std::shared_ptr<CNMatcher> makeCNVisitingMatcher(std::shared_ptr<CNIdentifyingVisitor> identifying);
};

#endif //COCOAVIEWS_COCOAVIEWMATCHERFACTORY_H