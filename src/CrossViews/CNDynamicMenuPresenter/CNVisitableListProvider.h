#ifndef CROSSNATIVE_VISITABLELISTPROVIDER_H
#define CROSSNATIVE_VISITABLELISTPROVIDER_H

#include <memory>
#include <vector>

class CNVisitable;

class CNVisitableListProvider;
typedef std::shared_ptr<CNVisitableListProvider> CNVisitableListProviderPtr;

class CNVisitableListProvider {
public:
    virtual ~CNVisitableListProvider() {}
protected:
    CNVisitableListProvider() {}

public:
    virtual const std::vector< std::shared_ptr<CNVisitable> > getVisitables() = 0;
};

#endif //CROSSNATIVE_VISITABLELISTPROVIDER_H