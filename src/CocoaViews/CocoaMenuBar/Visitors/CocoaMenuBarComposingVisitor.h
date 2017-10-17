#ifndef COCOAVIEWS_COCOAMENUBARCOMPOSINGVISITOR_H
#define COCOAVIEWS_COCOAMENUBARCOMPOSINGVISITOR_H

#include "CrossNative/CNVisitor/CNVisitor.h"

class CocoaMenuBar;

class CocoaMenuBarComposingVisitor;
typedef std::shared_ptr<CocoaMenuBarComposingVisitor> CocoaMenuBarComposingVisitorPtr;

class CocoaMenuBarComposingVisitor
        : public CNVisitor {
public:
    static CocoaMenuBarComposingVisitorPtr getNewInstance(std::shared_ptr<CocoaMenuBar> menBar);
    virtual ~CocoaMenuBarComposingVisitor();
private:
    CocoaMenuBarComposingVisitor(std::shared_ptr<CocoaMenuBar> menuBar);

private:
    std::shared_ptr<CocoaMenuBar> menuBar;
};

#endif //COCOAVIEWS_COCOAMENUBARCOMPOSINGVISITOR_H