#ifndef COCOAVIEWS_COCOAMENUDECOMPOSINGVISITOR_H
#define COCOAVIEWS_COCOAMENUDECOMPOSINGVISITOR_H

#include <CrossNative/CNVisitor/CNVisitor.h>

#include "CocoaViews/NSMenuItemBased/CocoaMenu/CocoaMenuVisitor.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenuItem/CocoaMenuItemVisitor.h"

class CocoaMenu;

class CocoaMenuDecomposingVisitor;
typedef std::shared_ptr<CocoaMenuDecomposingVisitor> CocoaMenuDecomposingVisitorPtr;

class CocoaMenuDecomposingVisitor
        : public CNVisitor,
          public CocoaMenuVisitor,
          public CocoaMenuItemVisitor {
public:
    static CocoaMenuDecomposingVisitorPtr getNewInstance(std::shared_ptr<CocoaMenu> menu);
    virtual ~CocoaMenuDecomposingVisitor();
private:
    CocoaMenuDecomposingVisitor(std::shared_ptr<CocoaMenu> menu);

public:
    virtual void visit(std::shared_ptr<CocoaMenuItem> menuItem) override;
    virtual void visit(std::shared_ptr<CocoaMenu> menu) override;
private:
    std::shared_ptr<CocoaMenu> menu;
};

#endif //COCOAVIEWS_COCOAMENUDECOMPOSINGVISITOR_H