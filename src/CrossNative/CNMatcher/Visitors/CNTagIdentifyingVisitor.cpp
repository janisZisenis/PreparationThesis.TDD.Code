#include "CNTagIdentifyingVisitor.h"
#include "CrossNative/CNTagged/CNTagged.h"

CNTagIdentifyingVisitorPtr CNTagIdentifyingVisitor::getNewInstance(std::string tag) {
    return CNTagIdentifyingVisitorPtr(new CNTagIdentifyingVisitor(tag));
}
CNTagIdentifyingVisitor::~CNTagIdentifyingVisitor() {}
CNTagIdentifyingVisitor::CNTagIdentifyingVisitor(std::string tag) : expectedTag(tag) {}

bool CNTagIdentifyingVisitor::hasIdentified() {
    return actualTag == expectedTag;
}

void CNTagIdentifyingVisitor::visit(CNTaggedPtr tagged) {
    actualTag = tagged->getTag();
}
