#ifndef CROSSNATIVE_TRANSACTIONTITLE_H
#define CROSSNATIVE_TRANSACTIONTITLE_H

#include <memory>
#include <string>

class CNTransActionTitle;
typedef std::shared_ptr<CNTransActionTitle> CNTransActionTitlePtr;

class CNTransActionTitle {
public:
    virtual ~CNTransActionTitle() {};
protected:
    CNTransActionTitle() {};

public:
    virtual std::string getTitle() = 0;
};

#endif //CROSSNATIVE_TRANSACTIONTITLE_H