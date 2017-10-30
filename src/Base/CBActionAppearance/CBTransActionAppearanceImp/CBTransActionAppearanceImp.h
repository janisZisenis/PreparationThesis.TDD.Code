#ifndef CODEBASEIMP_TRANSACTIONAPPEARANCEIMP_H
#define CODEBASEIMP_TRANSACTIONAPPEARANCEIMP_H

#include <Base/CBTransActionAppearance/CBTransActionAppearance.h>

class CBActionAccessibility;
class CBActionState;
class CBActionTitle;

class CBTransActionAppearanceImp;
typedef std::shared_ptr<CBTransActionAppearanceImp> CBTransActionAppearanceImpPtr;

class CBTransActionAppearanceImp : public CBTransActionAppearance {
public:
    static CBTransActionAppearanceImpPtr getNewInstance(std::shared_ptr<CBActionAccessibility> accessibility,
                                                        std::shared_ptr<CBActionState> state,
                                                        std::shared_ptr<CBActionTitle> title);
    virtual ~CBTransActionAppearanceImp();
private:
    CBTransActionAppearanceImp(std::shared_ptr<CBActionAccessibility> accessibility,
                               std::shared_ptr<CBActionState> state,
                               std::shared_ptr<CBActionTitle> title);

public:
    virtual bool isAccessible() override;
    CBActionStates getState() override;
    std::string getTitle() override;

private:
    std::shared_ptr<CBActionAccessibility> accessibility;
    std::shared_ptr<CBActionState> state;
    std::shared_ptr<CBActionTitle> title;
};

#endif //CODEBASEIMP_TRANSACTIONAPPEARANCEIMP_H