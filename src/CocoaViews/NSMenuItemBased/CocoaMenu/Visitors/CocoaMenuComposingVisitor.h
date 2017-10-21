#ifndef COCOAVIEWS_COCOAMENUCOMPOSINGVISITOR_H
#define COCOAVIEWS_COCOAMENUCOMPOSINGVISITOR_H

#include <CrossNative/CNVisitor/CNVisitor.h>
#include "CocoaViews/NSMenuItemBased/CocoaMenuItem/CocoaMenuItemVisitor.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenu/CocoaMenuVisitor.h"

class CocoaMenu;

class CocoaMenuComposingVisitor;
typedef std::shared_ptr<CocoaMenuComposingVisitor> CocoaMenuComposingVisitorPtr;

class CocoaMenuComposingVisitor
        : public CNVisitor,
          public CocoaMenuVisitor,
          public CocoaMenuItemVisitor {
public:
    static CocoaMenuComposingVisitorPtr getNewInstance(std::shared_ptr<CocoaMenu> menu);
    virtual ~CocoaMenuComposingVisitor();
private:
    CocoaMenuComposingVisitor(std::shared_ptr<CocoaMenu> menu);

public:
    virtual void visit(std::shared_ptr<CocoaMenuItem> menuItem) override;
    virtual void visit(std::shared_ptr<CocoaMenu> menu) override;
private:
    std::shared_ptr<CocoaMenu> menu;
};

#endif //COCOAVIEWS_COCOAMENUCOMPOSINGVISITOR_H