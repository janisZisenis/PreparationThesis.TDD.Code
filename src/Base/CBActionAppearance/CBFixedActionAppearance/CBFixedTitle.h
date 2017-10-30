#ifndef CODEBASEIMP_FIXEDTITLE_H
#define CODEBASEIMP_FIXEDTITLE_H

#include "Base/CBTransActionAppearance/CBActionTitle.h"

class CBFixedTitle;
typedef std::shared_ptr<CBFixedTitle> CBFixedTitlePtr;

class CBFixedTitle : public CBActionTitle {
public:
    static CBFixedTitlePtr getNewInstance(std::string title);
    virtual ~CBFixedTitle();
private:
    CBFixedTitle(std::string title);

public:
    virtual std::string getTitle() override;

private:
    std::string title;
};

#endif //CODEBASEIMP_FIXEDTITLE_H