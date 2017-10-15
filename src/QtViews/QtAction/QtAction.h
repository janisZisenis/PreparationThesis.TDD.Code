#ifndef QTVIEWS_QTACTION_H
#define QTVIEWS_QTACTION_H

#include <QObject>

class QAction;

class QtAction;
typedef std::shared_ptr<QtAction> QtActionPtr;

class QtAction : public QObject {
    Q_OBJECT
public:
    static QtActionPtr getNewInstance();
    virtual ~QtAction();
private:
    QtAction();

public:
    virtual QAction* getQAction();

    virtual void setTitle(std::string newTitle);
    virtual void setAccessibility(bool newAccessibility);
    virtual void setChecked(bool checked);
private:
    virtual void connectToAction();

private:
    QAction* action;

private slots:
    virtual void onChanged();
    virtual void onHovered();
    virtual void onToggled(bool checked);
    virtual void onTriggered(bool checked = false);
};

#endif //QTVIEWS_QTACTION_H