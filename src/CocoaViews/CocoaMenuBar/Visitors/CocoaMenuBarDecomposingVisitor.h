#ifndef COCOAVIEWS_COCOAMENUBARDECOMPOSINGVISITOR_H
#define COCOAVIEWS_COCOAMENUBARDECOMPOSINGVISITOR_H

#include "CrossNative/CNVisitor/CNVisitor.h"

#include "CocoaViews/CocoaMenu/CocoaMenuVisitor.h"

class CocoaMenuBar;

class CocoaMenuBarDecomposingVisitor;
typedef std::shared_ptr<CocoaMenuBarDecomposingVisitor> CocoaMenuBarDecomposingVisitorPtr;

class CocoaMenuBarDecomposingVisitor
        : public CNVisitor,
          public CocoaMenuVisitor {
public:
    static CocoaMenuBarDecomposingVisitorPtr getNewInstance(std::shared_ptr<CocoaMenuBar> menuBar);
    virtual ~CocoaMenuBarDecomposingVisitor();
private:
    CocoaMenuBarDecomposingVisitor(std::shared_ptr<CocoaMenuBar> menuBar);

public:
    void visit(std::shared_ptr<CocoaMenu> menu) override;

private:
    std::shared_ptr<CocoaMenuBar> menuBar;
};

#endif //COCOAVIEWS_COCOAMENUBARDECOMPOSINGVISITOR_H