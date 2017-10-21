#ifndef QTVIEWS_QTWIDGET_H
#define QTVIEWS_QTWIDGET_H

#include <string>
#include <memory>

class QWidget;

class QtWidget;
typedef std::shared_ptr<QtWidget> QtWidgetImpPtr;
class QtWidget {
public:
    virtual ~QtWidget() {};
protected:
    QtWidget() {};

public:
    virtual QWidget* getQWidget() = 0;
    virtual std::string getTitle() = 0;
};

#endif //QTVIEWS_QTWIDGET_H