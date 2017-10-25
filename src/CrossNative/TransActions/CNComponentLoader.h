#ifndef CROSSNATIVE_COMPONENTLOADER_H
#define CROSSNATIVE_COMPONENTLOADER_H

#include <memory>

class CNComponentLoader;
typedef std::shared_ptr<CNComponentLoader> CNComponentLoaderPtr;

class CNComponentLoader {
public:
    virtual ~CNComponentLoader() {}
protected:
    CNComponentLoader() {}
};

#endif //CROSSNATIVE_COMPONENTLOADER_H