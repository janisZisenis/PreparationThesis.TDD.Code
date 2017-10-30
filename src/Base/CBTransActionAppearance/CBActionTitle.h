#ifndef CODEBASE_ACTIONTITLE_H
#define CODEBASE_ACTIONTITLE_H

#include <memory>
#include <string>

class CBActionTitle;
typedef std::shared_ptr<CBActionTitle> CBActionTitlePtr;

class CBActionTitle {
public:
    virtual ~CBActionTitle() {};
protected:
    CBActionTitle() {};

public:
    virtual std::string getTitle() = 0;
};

#endif //CODEBASE_ACTIONTITLE_H