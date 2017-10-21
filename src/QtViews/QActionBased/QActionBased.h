#ifndef QTVIEWS_QACTIONBASED_H
#define QTVIEWS_QACTIONBASED_H

#include <memory>

class QAction;

class QActionBased;
typedef std::shared_ptr<QActionBased> QActionBasedPtr;
class QActionBased {
public:
    virtual ~QActionBased() {};
protected:
    QActionBased() {};

public:
    virtual QAction* getQAction() = 0;
};

#endif //QTVIEWS_QACTIONBASED_H