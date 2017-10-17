#ifndef QTVIEWS_QTMENUBARDECOMPOSINGVISITOR_H
#define QTVIEWS_QTMENUBARDECOMPOSINGVISITOR_H

#include "CrossNative/CNVisitor/CNVisitor.h"

#include "QtViews/QtMenu/QtMenuVisitor.h"

class QtMenuBar;

class QtMenuBarDecomposingVisitor;
typedef std::shared_ptr<QtMenuBarDecomposingVisitor> QtMenuBarDecomposingVisitorPtr;

class QtMenuBarDecomposingVisitor
        : public CNVisitor,
          public QtMenuVisitor {
public:
    static QtMenuBarDecomposingVisitorPtr getNewInstance(std::shared_ptr<QtMenuBar> menuBar);
    virtual ~QtMenuBarDecomposingVisitor();
private:
    QtMenuBarDecomposingVisitor(std::shared_ptr<QtMenuBar> menuBar);

public:
    void visit(std::shared_ptr<QtMenu> menu) override;

private:
    std::shared_ptr<QtMenuBar> menuBar;
};

#endif //QTVIEWS_QTMENUBARDECOMPOSINGVISITOR_H