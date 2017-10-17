#ifndef QTVIEWS_QTVIEWCOMPONENTFACTORY_H
#define QTVIEWS_QTVIEWCOMPONENTFACTORY_H

#include <memory>

class CNComponent;
class CNVisitable;
class CNComposer;
class CNVisitor;

class QtViewComponentFactory;
typedef std::shared_ptr<QtViewComponentFactory> QtViewComponentFactoryPtr;

class QtViewComponentFactory {
public:
    static QtViewComponentFactoryPtr getNewInstance();
    virtual ~QtViewComponentFactory();
private:
    QtViewComponentFactory();

public:
    virtual std::shared_ptr<CNComponent> makeShellComponent();
    virtual std::shared_ptr<CNComponent> makeMenuBarComponent();
    virtual std::shared_ptr<CNComponent> makeSolutionExplorerComponent();
    virtual std::shared_ptr<CNComponent> makePropertiesExplorerComponent();

private:
    virtual std::shared_ptr<CNComponent> makeComposable(std::shared_ptr<CNVisitable> visitable, std::shared_ptr<CNComposer> composer);
    virtual std::shared_ptr<CNComposer> makeVisitingComposer(std::shared_ptr<CNVisitor> composing, std::shared_ptr<CNVisitor> decomposing);
    virtual std::shared_ptr<CNComposer> makeNullComposer();
};

#endif //QTVIEWS_QTVIEWCOMPONENTFACTORY_H