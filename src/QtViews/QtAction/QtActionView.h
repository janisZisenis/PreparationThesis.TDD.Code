#ifndef QTVIEWS_QTACTIONVIEW_H
#define QTVIEWS_QTACTIONVIEW_H

#include <memory>

class QtActionView;
typedef std::shared_ptr<QtActionView> QtActionViewPtr;

class QtActionView {
public:
    virtual ~QtActionView() {}
protected:
    QtActionView() {}
};

#endif //QTVIEWS_QTACTIONVIEW_H