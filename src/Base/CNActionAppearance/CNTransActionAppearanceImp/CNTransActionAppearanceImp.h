#ifndef CROSSNATIVE_TRANSACTIONAPPEARANCEIMP_H
#define CROSSNATIVE_TRANSACTIONAPPEARANCEIMP_H

#include <Base/CNTransActionAppearance/CNTransActionAppearance.h>

class CNActionAccessibility;
class CNActionState;
class CNActionTitle;

class CNTransActionAppearanceImp;
typedef std::shared_ptr<CNTransActionAppearanceImp> CNTransActionAppearanceImpPtr;

class CNTransActionAppearanceImp : public CNTransActionAppearance {
public:
    static CNTransActionAppearanceImpPtr getNewInstance(std::shared_ptr<CNActionAccessibility> accessibility,
                                                        std::shared_ptr<CNActionState> state,
                                                        std::shared_ptr<CNActionTitle> title);
    virtual ~CNTransActionAppearanceImp();
private:
    CNTransActionAppearanceImp(std::shared_ptr<CNActionAccessibility> accessibility,
                               std::shared_ptr<CNActionState> state,
                               std::shared_ptr<CNActionTitle> title);

public:
    virtual bool isAccessible() override;
    CNActionStates getState() override;
    std::string getTitle() override;

private:
    std::shared_ptr<CNActionAccessibility> accessibility;
    std::shared_ptr<CNActionState> state;
    std::shared_ptr<CNActionTitle> title;
};

#endif //CROSSNATIVE_TRANSACTIONAPPEARANCEIMP_H