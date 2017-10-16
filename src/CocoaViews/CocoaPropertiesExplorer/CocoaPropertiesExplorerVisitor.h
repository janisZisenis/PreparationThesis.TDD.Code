#ifndef COCOALVIEWS_COCOAPROPERTIESEXPLORERVISITOR_H
#define COCOALVIEWS_COCOAPROPERTIESEXPLORERVISITOR_H

#include <memory>

class CocoaPropertiesExplorer;

class CocoaPropertiesExplorerVisitor;
typedef std::shared_ptr<CocoaPropertiesExplorerVisitor> CocoaPropertiesExplorerViewVisitorPtr;

class CocoaPropertiesExplorerVisitor {
public:
     virtual void visit(std::shared_ptr<CocoaPropertiesExplorer> view) = 0;
};

#endif //COCOALVIEWS_COCOAPROPERTIESEXPLORERVISITOR_H