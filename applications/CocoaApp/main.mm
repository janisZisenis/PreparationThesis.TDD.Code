#include <AppKit/AppKit.h>

#include "CocoaViews/CocoaViewComponentFactory/CocoaViewComponentFactory.h"
#include "CocoaViews/CocoaViewMatcherFactory/CocoaViewMatcherFactory.h"

#include <CrossNative/CNDynamicHierarchy/CNDynamicHierarchy.h>

#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNNullComposer.h>
#include <CocoaViews/CocoaMenu/CocoaMenu.h>

int main(int argc, char** argv) {
    NSApplication* application = [NSApplication sharedApplication];
    [application activateIgnoringOtherApps:true];

    CocoaViewComponentFactoryPtr componentFactory = CocoaViewComponentFactory::getNewInstance();
    CocoaViewMatcherFactoryPtr matcherFactory = CocoaViewMatcherFactory::getNewInstance();

    CNDynamicHierarchyPtr viewHierarchy = CNDynamicHierarchy::getNewInstance();
//    viewHierarchy->load(componentFactory->makeShellComponent(), matcherFactory->makeTopLevelMatcher());
//    viewHierarchy->load(componentFactory->makeSolutionExplorerComponent(), matcherFactory->makeShellTypeMatcher());
//    viewHierarchy->load(componentFactory->makePropertiesExplorerComponent(), matcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(componentFactory->makeMenuBarComponent(), matcherFactory->makeTopLevelMatcher());

    CocoaMenuPtr menu = CocoaMenu::getNewInstance("HelloWorld!");
    CNComposerPtr menuComposer = CNNullComposer::getNewInstance();
    CNComposablePtr menuComposable = CNComposable::getNewInstance(menu, menuComposer);

    viewHierarchy->load(menuComposable, matcherFactory->makeMenuBarTypeMatcher());

    [application run];
    return 0;
}