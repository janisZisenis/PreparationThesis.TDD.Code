#ifndef QTVIEWS_QWIDGETBASED_H
#define QTVIEWS_QWIDGETBASED_H

#include <string>
#include <memory>

class QWidget;

class QWidgetBased;
typedef std::shared_ptr<QWidgetBased> QWidgetBasedPtr;
class QWidgetBased {
public:
    virtual ~QWidgetBased() {};
protected:
    QWidgetBased() {};

public:
    virtual QWidget* getQWidget() = 0;
    virtual std::string getTitle() = 0;
};

#endif //QTVIEWS_QWIDGETBASED_H