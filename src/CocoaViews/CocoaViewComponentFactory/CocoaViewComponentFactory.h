#ifndef COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H
#define COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H

#include <memory>
#include <string>

class CNComponent;
class CNVisitable;
class CNComposer;
class CNVisitor;

class CocoaViewComponentFactory;
typedef std::shared_ptr<CocoaViewComponentFactory> CocoaViewComponentFactoryPtr;

class CocoaViewComponentFactory {
public:
    static CocoaViewComponentFactoryPtr getNewInstance();
    virtual ~CocoaViewComponentFactory();
private:
    CocoaViewComponentFactory();

public:
    virtual std::shared_ptr<CNComponent> makeShellComponent();
    virtual std::shared_ptr<CNComponent> makeSolutionExplorerComponent();
    virtual std::shared_ptr<CNComponent> makePropertiesExplorerComponent();
    virtual std::shared_ptr<CNComponent> makeMenuBarComponent();
    virtual std::shared_ptr<CNComponent> makeHelloWorldMenuComponent(std::string tag);
    virtual std::shared_ptr<CNComponent> makeExampleMenuItemComponent();


private:
    virtual std::shared_ptr<CNComponent> makeComposable(std::shared_ptr<CNVisitable> visitable, std::shared_ptr<CNComposer> composer);
    virtual std::shared_ptr<CNComposer> makeVisitingComposer(std::shared_ptr<CNVisitor> composing, std::shared_ptr<CNVisitor> decomposing);
    virtual std::shared_ptr<CNComposer> makeNullComposer();
};

#endif //COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H