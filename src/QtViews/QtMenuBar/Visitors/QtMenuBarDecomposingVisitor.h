#ifndef QTVIEWS_QTMENUBARDECOMPOSINGVISITOR_H
#define QTVIEWS_QTMENUBARDECOMPOSINGVISITOR_H

#include "CrossNative/CNVisitor/CNVisitor.h"

class QtMenuBar;

class QtMenuBarDecomposingVisitor;
typedef std::shared_ptr<QtMenuBarDecomposingVisitor> QtMenuBarDecomposingVisitorPtr;

class QtMenuBarDecomposingVisitor
        : public CNVisitor{
public:
    static QtMenuBarDecomposingVisitorPtr getNewInstance(std::shared_ptr<QtMenuBar> menuBar);
    virtual ~QtMenuBarDecomposingVisitor();
private:
    QtMenuBarDecomposingVisitor(std::shared_ptr<QtMenuBar> menuBar);
    
private:
    std::shared_ptr<QtMenuBar> menuBar;
};

#endif //QTVIEWS_QTMENUBARDECOMPOSINGVISITOR_H