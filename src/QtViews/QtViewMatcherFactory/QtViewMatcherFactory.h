#ifndef QTVIEWS_QTVIEWMATCHERFACTORY_H
#define QTVIEWS_QTVIEWMATCHERFACTORY_H

#include <memory>
#include <string>

class CNMatcherFactory;
class CNMatcher;
class CNIdentifyingVisitor;

class QtViewMatcherFactory;
typedef std::shared_ptr<QtViewMatcherFactory> QtViewMatcherFactoryPtr;

class QtViewMatcherFactory {
public:
    static QtViewMatcherFactoryPtr getNewInstance();
    virtual ~QtViewMatcherFactory();
protected:
    QtViewMatcherFactory();

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

#endif //QTVIEWS_QTVIEWMATCHERFACTORY_H