#ifndef CROSSNATIVE_ACTIONTITLE_H
#define CROSSNATIVE_ACTIONTITLE_H

#include <memory>
#include <string>

class CNActionTitle;
typedef std::shared_ptr<CNActionTitle> CNActionTitlePtr;

class CNActionTitle {
public:
    virtual ~CNActionTitle() {};
protected:
    CNActionTitle() {};

public:
    virtual std::string getTitle() = 0;
};

#endif //CROSSNATIVE_ACTIONTITLE_H