#ifndef QTVIEWS_QTACTION_H
#define QTVIEWS_QTACTION_H

#include <CrossNative/CNVisitable/CNVisitable.h>
#include "QtActionView.h"
#include <QObject>

class CNAcceptor;

class QAction;

class QtAction;
typedef std::shared_ptr<QtAction> QtActionPtr;

class QtAction : public QObject, public QtActionView, public virtual CNVisitable, public std::enable_shared_from_this<QtAction> {
    Q_OBJECT
public:
    static QtActionPtr getNewInstance();
    virtual ~QtAction();
private:
    QtAction();

public:
    virtual QAction* getQAction();

    virtual void setTitle(std::string newTitle) override;
    virtual void setAccessibility(bool newAccessibility) override;
    virtual void setState(CBActionStates newState) override;

    virtual void setChecked(bool checked);

    virtual void accept(CNVisitorPtr visitor) override;

private:
    virtual void connectToAction();

    QtActionPtr me();
private:
    std::shared_ptr<CNAcceptor> acceptor;

    QAction* action;

private slots:
    virtual void onChanged();
    virtual void onHovered();
    virtual void onToggled(bool checked);
    virtual void onTriggered(bool checked = false);
};

#endif //QTVIEWS_QTACTION_H