#include <AppKit/AppKit.h>

#include "CocoaViews/CocoaViewComponentFactory/CocoaViewComponentFactory.h"
#include "CocoaViews/CocoaViewMatcherFactory/CocoaViewMatcherFactory.h"

#include <CrossNative/CNDynamicHierarchy/CNDynamicHierarchy.h>

int main(int argc, char** argv) {
    NSApplication* application = [NSApplication sharedApplication];
    [application activateIgnoringOtherApps:true];

    CocoaViewComponentFactoryPtr componentFactory = CocoaViewComponentFactory::getNewInstance();
    CocoaViewMatcherFactoryPtr matcherFactory = CocoaViewMatcherFactory::getNewInstance();

    CNDynamicHierarchyPtr viewHierarchy = CNDynamicHierarchy::getNewInstance();
    viewHierarchy->load(componentFactory->makeShellComponent(), matcherFactory->makeTopLevelMatcher());
    viewHierarchy->load(componentFactory->makeSolutionExplorerComponent(), matcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(componentFactory->makePropertiesExplorerComponent(), matcherFactory->makeShellTypeMatcher());

    [application run];
    return 0;
}