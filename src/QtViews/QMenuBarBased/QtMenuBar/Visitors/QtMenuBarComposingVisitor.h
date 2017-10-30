#ifndef QTVIEWS_QTMENUBARCOMPOSINGVISITOR_H
#define QTVIEWS_QTMENUBARCOMPOSINGVISITOR_H

#include "Hierarchies/CNVisitor/CNVisitor.h"

#include "QtViews/QActionBased/QtMenu/QtMenuVisitor.h"

class QtMenuBar;

class QtMenuBarComposingVisitor;
typedef std::shared_ptr<QtMenuBarComposingVisitor> QtMenuBarComposingVisitorPtr;

class QtMenuBarComposingVisitor
        : public CNVisitor,
          public QtMenuVisitor {
public:
    static QtMenuBarComposingVisitorPtr getNewInstance(std::shared_ptr<QtMenuBar> menBar);
    virtual ~QtMenuBarComposingVisitor();
private:
    QtMenuBarComposingVisitor(std::shared_ptr<QtMenuBar> menuBar);

public:
    void visit(std::shared_ptr<QtMenu> menu) override;

private:
    std::shared_ptr<QtMenuBar> menuBar;
};

#endif //QTVIEWS_QTMENUBARCOMPOSINGVISITOR_H