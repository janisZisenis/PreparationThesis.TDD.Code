#ifndef COCOALVICE_COCOAPROPERTIESEXPLORERVIEWVISITOR_H
#define COCOALVICE_COCOAPROPERTIESEXPLORERVIEWVISITOR_H

#include <memory>

class CocoaPropertiesExplorer;

class CocoaPropertiesExplorerVisitor;
typedef std::shared_ptr<CocoaPropertiesExplorerVisitor> CocoaPropertiesExplorerViewVisitorPtr;

class CocoaPropertiesExplorerVisitor {
public:
     virtual void visit(std::shared_ptr<CocoaPropertiesExplorer> view) = 0;
};

#endif //COCOALVICE_COCOAPROPERTIESEXPLORERVIEWVISITOR_H