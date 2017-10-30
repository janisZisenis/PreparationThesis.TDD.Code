#ifndef CODEBASE_TRANSACTIONAPPEARANCE_H
#define CODEBASE_TRANSACTIONAPPEARANCE_H

#include <memory>
#include <string>

#include "CBActionStates.h"

class CBTransActionAppearance;
typedef std::shared_ptr<CBTransActionAppearance> CBTransActionAppearancePtr;

class CBTransActionAppearance {
public:
    virtual ~CBTransActionAppearance() {};
protected:
    CBTransActionAppearance() {};

public:
    virtual bool isAccessible() = 0;
    virtual CBActionStates getState() = 0;
    virtual std::string getTitle() = 0;
};

#endif //CODEBASE_TRANSACTIONAPPEARANCE_H