#include <AppKit/AppKit.h>

#include <CrossNative/CNDynamicHierarchy/CNDynamicHierarchy.h>
#include <CrossNative/CNMatcher/CNTypeMatcher.h>
#include <CrossNative/CNMatcher/CNNullMatcher.h>

#include "CocoaViews/CocoaShell/Visitors/CocoaShellNullVisitor.h"
#include "CocoaViews/CocoaViewComponentFactory/CocoaViewComponentFactory.h"

int main(int argc, char** argv) {
    NSApplication* application = [NSApplication sharedApplication];
    [application activateIgnoringOtherApps:true];

    CocoaViewComponentFactoryPtr componentFactory = CocoaViewComponentFactory::getNewInstance();

    CNDynamicHierarchyPtr viewHierarchy = CNDynamicHierarchy::getNewInstance();
    viewHierarchy->load(componentFactory->makeShellComponent(), CNNullMatcher::getNewInstance());
    viewHierarchy->load(componentFactory->makePropertiesExplorerComponent(), CNTypeMatcher::getNewInstance(CocoaShellNullVisitor::getNewInstance()));

    [application run];
    return 0;
}