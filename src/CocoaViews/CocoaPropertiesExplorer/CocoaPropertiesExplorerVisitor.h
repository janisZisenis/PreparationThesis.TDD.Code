#ifndef COCOALVICE_COCOAPROPERTIESEXPLORERVIEWVISITOR_H
#define COCOALVICE_COCOAPROPERTIESEXPLORERVIEWVISITOR_H

#include <memory>

class CocoaPropertiesExplorerView;

class CocoaPropertiesExplorerVisitor;
typedef std::shared_ptr<CocoaPropertiesExplorerVisitor> CocoaPropertiesExplorerViewVisitorPtr;

class CocoaPropertiesExplorerVisitor {
public:
     virtual void visit(std::shared_ptr<CocoaPropertiesExplorerView> view) = 0;
};

#endif //COCOALVICE_COCOAPROPERTIESEXPLORERVIEWVISITOR_H