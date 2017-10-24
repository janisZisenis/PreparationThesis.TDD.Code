#ifndef QTVIEWS_QTCENTRAL_H
#define QTVIEWS_QTCENTRAL_H

#include <CrossNative/CNVisitable/CNVisitable.h>
#include "QtViews/QWidgetBased/QWidgetBased.h"

class QtCentral;

class QtCentral;
typedef std::shared_ptr<QtCentral> QtCentralPtr;

class QtCentral : public QWidgetBased, public virtual CNVisitable {
public:
    virtual ~QtCentral() {}
protected:
    QtCentral() {}
};

#endif //QTVIEWS_QTCENTRAL_H