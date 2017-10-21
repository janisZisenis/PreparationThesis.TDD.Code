#ifndef COCOAVIEW_COCOAMENUBARVISITOR_H
#define COCOAVIEW_COCOAMENUBARVISITOR_H

#include <memory>

class CocoaMenuBar;

class CocoaMenuBarVisitor;
typedef std::shared_ptr<CocoaMenuBarVisitor> CocoaMenuBarVisitorPtr;

class CocoaMenuBarVisitor {
public:
    virtual void visit(std::shared_ptr<CocoaMenuBar> cocoaMenuBar) = 0;
};

#endif //COCOAVIEW_COCOAMENUBARVISITOR_H