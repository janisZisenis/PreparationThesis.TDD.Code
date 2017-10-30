#ifndef CODEBASEIMP_FIXEDAPPEARANCE_H
#define CODEBASEIMP_FIXEDAPPEARANCE_H

#include <Base/CBTransActionAppearance/CBTransActionAppearance.h>

class CBActionAccessibility;
class CBActionState;
class CBActionTitle;

class CBFixedAppearance;
typedef std::shared_ptr<CBFixedAppearance> CBFixedAppearancePtr;

class CBFixedAppearance : public CBTransActionAppearance {
public:
    static CBFixedAppearancePtr getNewInstance(bool accessibility,
                                               CBActionStates state,
                                               std::string title);
    virtual ~CBFixedAppearance();
private:
    CBFixedAppearance(bool accessibility,
                      CBActionStates state,
                      std::string title);

public:
    virtual bool isAccessible() override;
    CBActionStates getState() override;
    std::string getTitle() override;

private:
    bool accessibility;
    CBActionStates state;
    std::string title;
};

#endif //CODEBASEIMP_FIXEDAPPEARANCE_H