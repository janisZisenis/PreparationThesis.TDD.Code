#ifndef QTVIEWS_QTVIEWMATCHERFACTORY_H
#define QTVIEWS_QTVIEWMATCHERFACTORY_H

#include <memory>

class CNMatcher;
class CNVisitor;

class QtViewMatcherFactory;
typedef std::shared_ptr<QtViewMatcherFactory> QtViewMatcherFactoryPtr;

class QtViewMatcherFactory {
public:
    static QtViewMatcherFactoryPtr getNewInstance();
    virtual ~QtViewMatcherFactory();
private:
    QtViewMatcherFactory();

public:
    virtual std::shared_ptr<CNMatcher> makeTopLevelMatcher();
    virtual std::shared_ptr<CNMatcher> makeShellTypeMatcher();
private:
    virtual std::shared_ptr<CNMatcher> makeCNNullMatcher();
    virtual std::shared_ptr<CNMatcher> makeCNTypeMatcher(std::shared_ptr<CNVisitor> matchingVisitor);
};

#endif //QTVIEWS_QTVIEWMATCHERFACTORY_H