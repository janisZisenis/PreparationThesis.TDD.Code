#ifndef QTVIEWS_QTACTIONVIEW_H
#define QTVIEWS_QTACTIONVIEW_H

#include <memory>
#include <CodeBase/CBTransActionAppearance/CBActionState.h>

class QtActionView;
typedef std::shared_ptr<QtActionView> QtActionViewPtr;

class QtActionView {
public:
    virtual ~QtActionView() {}
protected:
    QtActionView() {}

public:
    virtual void setAccessibility(bool newAccessibility) = 0;
    virtual void setState(CBActionStates newState) = 0;
};

#endif //QTVIEWS_QTACTIONVIEW_H