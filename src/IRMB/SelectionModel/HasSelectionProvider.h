#ifndef CCORE_HASSELECTIONPROVIDER_H
#define CCORE_HASSELECTIONPROVIDER_H

#include <memory>

class HasSelectionProvider;
typedef std::shared_ptr<HasSelectionProvider> ValidSelectionProviderPtr;

class HasSelectionProvider {
public:
    virtual ~HasSelectionProvider() {};
protected:
    HasSelectionProvider() {};

public:
    virtual bool hasSelection() = 0;
};

#endif //CCORE_HASSELECTIONPROVIDER_H