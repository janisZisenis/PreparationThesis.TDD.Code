#ifndef COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H
#define COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H

#include <memory>

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
    virtual std::shared_ptr<CNComponent> makePropertiesExplorerComponent();

private:
    virtual std::shared_ptr<CNComponent> makeComposable(std::shared_ptr<CNVisitable> visitable, std::shared_ptr<CNComposer> composer);
    virtual std::shared_ptr<CNComposer> makeVisitingComposer(std::shared_ptr<CNVisitor> composing, std::shared_ptr<CNVisitor> decomposing);
    virtual std::shared_ptr<CNComposer> makeNullComposer();
};

#endif //COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H