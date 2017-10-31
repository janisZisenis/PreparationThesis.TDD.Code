#ifndef CROSSNATIVE_TRANSACTIONAPPEARANCE_H
#define CROSSNATIVE_TRANSACTIONAPPEARANCE_H

#include <memory>
#include <string>

#include "CNTransActionStateValues.h"

class CNTransActionAppearance;
typedef std::shared_ptr<CNTransActionAppearance> CNTransActionAppearancePtr;

class CNTransActionAppearance {
public:
    virtual ~CNTransActionAppearance() {};
protected:
    CNTransActionAppearance() {};

public:
    virtual bool isAccessible() = 0;
    virtual CNTransActionStateValues getState() = 0;
    virtual std::string getTitle() = 0;
};

#endif //CROSSNATIVE_TRANSACTIONAPPEARANCE_H