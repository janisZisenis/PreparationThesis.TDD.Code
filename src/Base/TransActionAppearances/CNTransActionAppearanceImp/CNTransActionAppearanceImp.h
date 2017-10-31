#ifndef CROSSNATIVE_TRANSACTIONAPPEARANCEIMP_H
#define CROSSNATIVE_TRANSACTIONAPPEARANCEIMP_H

#include "Base/CNTransActionAppearance/CNTransActionAppearance.h"

class CNTransActionAccessibility;
class CNTransActionState;
class CNTransActionTitle;

class CNTransActionAppearanceImp;
typedef std::shared_ptr<CNTransActionAppearanceImp> CNTransActionAppearanceImpPtr;

class CNTransActionAppearanceImp : public CNTransActionAppearance {
public:
    static CNTransActionAppearanceImpPtr getNewInstance(std::shared_ptr<CNTransActionAccessibility> accessibility,
                                                        std::shared_ptr<CNTransActionState> state,
                                                        std::shared_ptr<CNTransActionTitle> title);
    virtual ~CNTransActionAppearanceImp();
private:
    CNTransActionAppearanceImp(std::shared_ptr<CNTransActionAccessibility> accessibility,
                               std::shared_ptr<CNTransActionState> state,
                               std::shared_ptr<CNTransActionTitle> title);

public:
    virtual bool isAccessible() override;
    CNTransActionStateValues getState() override;
    std::string getTitle() override;

private:
    std::shared_ptr<CNTransActionAccessibility> accessibility;
    std::shared_ptr<CNTransActionState> state;
    std::shared_ptr<CNTransActionTitle> title;
};

#endif //CROSSNATIVE_TRANSACTIONAPPEARANCEIMP_H