#include <AppKit/AppKit.h>

#include "CocoaViews/CocoaShell/CocoaShell.h"

int main(int argc, char** argv) {
    NSApplication* application = [NSApplication sharedApplication];
    [application activateIgnoringOtherApps:true];

    CocoaShellPtr shell = CocoaShell::getNewInstance();


    [application run];
    return 0;
}