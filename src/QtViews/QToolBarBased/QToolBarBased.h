#ifndef QTVIEWS_QTOOLBARBASED_H
#define QTVIEWS_QTOOLBARBASED_H

#include <memory>

class QToolBar;

class QToolBarBased;
typedef std::shared_ptr<QToolBarBased> QToolBarBasedPtr;
class QToolBarBased {
public:
    virtual ~QToolBarBased() {};
protected:
    QToolBarBased() {};

public:
    virtual QToolBar* getQToolBar() = 0;
};

#endif //QTVIEWS_QTOOLBARBASED_H