#ifndef QTVIEWS_QTVIEWCOMPOSABLEFACTORY_H
#define QTVIEWS_QTVIEWCOMPOSABLEFACTORY_H

#include <memory>

class CNComposable;
class CNVisitable;
class CNComposer;
class CNVisitor;

class QtViewComposableFactory;
typedef std::shared_ptr<QtViewComposableFactory> QtViewComposableFactoryPtr;

class QtViewComposableFactory {
public:
    static QtViewComposableFactoryPtr getNewInstance();
    virtual ~QtViewComposableFactory();
private:
    QtViewComposableFactory();

public:
    virtual std::shared_ptr<CNComposable> makeShellComposable();
    virtual std::shared_ptr<CNComposable> makeSolutionExplorerComposable();
    virtual std::shared_ptr<CNComposable> makePropertiesExplorerComposable();
    virtual std::shared_ptr<CNComposable> makeMenuBarComposable();

private:
    virtual std::shared_ptr<CNComposable> makeComposable(std::shared_ptr<CNVisitable> visitable, std::shared_ptr<CNComposer> composer);
    virtual std::shared_ptr<CNComposer> makeVisitingComposer(std::shared_ptr<CNVisitor> composing, std::shared_ptr<CNVisitor> decomposing);
    virtual std::shared_ptr<CNComposer> makeNullComposer();
};

#endif //QTVIEWS_QTVIEWCOMPOSABLEFACTORY_H