#ifndef CROSSNATIVE_FIXEDTITLE_H
#define CROSSNATIVE_FIXEDTITLE_H

#include "Base/CNTransActionAppearance/CNTransActionTitle.h"

class CNFixedTitle;
typedef std::shared_ptr<CNFixedTitle> CNFixedTitlePtr;

class CNFixedTitle : public CNTransActionTitle {
public:
    static CNFixedTitlePtr getNewInstance(std::string title);
    virtual ~CNFixedTitle();
private:
    CNFixedTitle(std::string title);

public:
    virtual std::string getTitle() override;

private:
    std::string title;
};

#endif //CROSSNATIVE_FIXEDTITLE_H