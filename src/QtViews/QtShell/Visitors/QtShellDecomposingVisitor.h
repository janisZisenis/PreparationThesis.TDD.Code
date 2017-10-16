#ifndef QTVIEWS_QTSHELLDECOMPOSINGVISITOR_H
#define QTVIEWS_QTSHELLDECOMPOSINGVISITOR_H

#include "CrossNative/CNVisitor/CNVisitor.h"

class QtShell;

class QtShellDecomposingVisitor;
typedef std::shared_ptr<QtShellDecomposingVisitor> QtShellDecomposingVisitorPtr;

class QtShellDecomposingVisitor
        : public CNVisitor {
public:
    static QtShellDecomposingVisitorPtr getNewInstance(std::shared_ptr<QtShell> shell);
    virtual ~QtShellDecomposingVisitor();
private:
    QtShellDecomposingVisitor(std::shared_ptr<QtShell> shell);
private:
    std::shared_ptr<QtShell> shell;
};

#endif //QTVIEWS_QTSHELLDECOMPOSINGVISITOR_H