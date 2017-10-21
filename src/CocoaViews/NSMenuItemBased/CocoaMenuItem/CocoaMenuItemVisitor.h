#ifndef COCOAVIEWS_COCOAMENUITEMVISITOR_H
#define COCOAVIEWS_COCOAMENUITEMVISITOR_H

#include <memory>

class CocoaMenuItem;

class CocoaMenuItemVisitor;
typedef std::shared_ptr<CocoaMenuItemVisitor> CocoaMenuItemVisitorPtr;

class CocoaMenuItemVisitor {
public:
    virtual void visit(std::shared_ptr<CocoaMenuItem> menuItem) = 0;
};

#endif //COCOAVIEWS_COCOAMENUITEMVISITOR_H