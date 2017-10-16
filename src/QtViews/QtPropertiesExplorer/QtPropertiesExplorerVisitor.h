#ifndef QTVIEWS_QTPROPERTIESEXPLORERVISITOR_H
#define QTVIEWS_QTPROPERTIESEXPLORERVISITOR_H

#include <memory>

class QtPropertiesExplorer;

class QtPropertiesExplorerVisitor;
typedef std::shared_ptr<QtPropertiesExplorerVisitor> QtPropertiesExplorerVisitorPtr;

class QtPropertiesExplorerVisitor {
public:
    virtual void visit(std::shared_ptr<QtPropertiesExplorer> propertiesExplorer) = 0;
};

#endif //QTVIEWS_QTPROPERTIESEXPLORERVISITOR_H