#ifndef QTVIEWS_QTMENUBARCOMPOSINGVISITOR_H
#define QTVIEWS_QTMENUBARCOMPOSINGVISITOR_H

#include "CrossNative/CNVisitor/CNVisitor.h"

class QtMenuBar;

class QtMenuBarComposingVisitor;
typedef std::shared_ptr<QtMenuBarComposingVisitor> QtMenuBarComposingVisitorPtr;

class QtMenuBarComposingVisitor
        : public CNVisitor{
public:
    static QtMenuBarComposingVisitorPtr getNewInstance(std::shared_ptr<QtMenuBar> menBar);
    virtual ~QtMenuBarComposingVisitor();
private:
    QtMenuBarComposingVisitor(std::shared_ptr<QtMenuBar> menuBar);

private:
    std::shared_ptr<QtMenuBar> menuBar;
};

#endif //QTVIEWS_QTMENUBARCOMPOSINGVISITOR_H