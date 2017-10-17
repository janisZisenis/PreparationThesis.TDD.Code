#ifndef COCOAVIEWS_COCOAMENUVISITOR_H
#define COCOAVIEWS_COCOAMENUVISITOR_H

#include <memory>

class CocoaMenu;

class CocoaMenuVisitor;
typedef std::shared_ptr<CocoaMenuVisitor> CocoaMenuVisitorPtr;

class CocoaMenuVisitor {
public:
    virtual void visit(std::shared_ptr<CocoaMenu> view) = 0;
};

#endif //COCOAVIEWS_COCOAMENUVISITOR_H