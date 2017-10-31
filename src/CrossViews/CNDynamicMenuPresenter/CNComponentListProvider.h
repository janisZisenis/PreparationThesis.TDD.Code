#ifndef CROSSNATIVE_COMPONENTLISTPROVIDER_H
#define CROSSNATIVE_COMPONENTLISTPROVIDER_H

#include <memory>
#include <vector>

class CNVisitable;

class CNComponentListProvider;
typedef std::shared_ptr<CNComponentListProvider> CNComponentListProviderPtr;

class CNComponentListProvider {
public:
    virtual ~CNComponentListProvider() {}
protected:
    CNComponentListProvider() {}

public:
    virtual const std::vector< std::shared_ptr<CNVisitable> > getMenuEntryList() = 0;
};

#endif //CROSSNATIVE_COMPONENTLISTPROVIDER_H