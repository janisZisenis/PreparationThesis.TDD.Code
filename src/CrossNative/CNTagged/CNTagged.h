#ifndef CROSSNATIVE_TAGGED_H
#define CROSSNATIVE_TAGGED_H

#include <CrossNative/CNVisitable/CNVisitable.h>
#include <string>

class CNTagged;
typedef std::shared_ptr<CNTagged> CNTaggedPtr;

class CNTagged : public CNVisitable {
public:
    virtual ~CNTagged() {}
protected:
    CNTagged() {}

public:
    virtual std::string getTag() = 0;
};

#endif //CROSSNATIVE_TAGGED_H
