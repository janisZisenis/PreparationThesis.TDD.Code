#include "CNComponentFactory.h"
#include "Hierarchies/CNComponent/CNComposable/CNComposable.h"

CNComponentFactoryPtr CNComponentFactory::getNewInstance() {
    return CNComponentFactoryPtr(new CNComponentFactory());
}
CNComponentFactory::~CNComponentFactory() {}
CNComponentFactory::CNComponentFactory() {}

CNComponentPtr CNComponentFactory::makeCNComposable(CNVisitablePtr visitable, std::shared_ptr<CNComposer> composer) {
    return CNComposable::getNewInstance(visitable, composer);
}

