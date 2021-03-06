#include "CNComposerFactory.h"
#include "Hierarchies/CNComposer/CNNullComposer.h"
#include "Hierarchies/CNComposer/CNVisitingComposer/CNVisitingComposer.h"

CNComposerFactoryPtr CNComposerFactory::getNewInstance() {
    return CNComposerFactoryPtr(new CNComposerFactory());
}
CNComposerFactory::~CNComposerFactory() {}
CNComposerFactory::CNComposerFactory() {}

CNComposerPtr CNComposerFactory::makeCNNullComposer() {
    return CNNullComposer::getNewInstance();
}

CNComposerPtr CNComposerFactory::makeCNVisitingComposer(std::shared_ptr<CNVisitor> composing, std::shared_ptr<CNVisitor> decomposing) {
    return CNVisitingComposer::getNewInstance(composing, decomposing);
}