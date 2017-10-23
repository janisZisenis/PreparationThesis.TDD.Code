#ifndef QTVIEWS_QTACTION_H
#define QTVIEWS_QTACTION_H

#include <QObject>
#include <CrossViews/MenuEntryPresenter/MenuEntryView.h>
#include "QtViews/QActionBased/QActionBased.h"

class CNAcceptor;

class QAction;

class QtAction;
typedef std::shared_ptr<QtAction> QtActionPtr;

class QtAction : public QObject, public QActionBased, public MenuEntryView, public std::enable_shared_from_this<QtAction> {
    Q_OBJECT
public:
    static QtActionPtr getNewInstance();
    virtual ~QtAction();
private:
    QtAction();

public:
    virtual QAction* getQAction() override;

    virtual void setTitle(std::string newTitle) override;
    virtual void check() override;
    virtual void uncheck() override;
    virtual void enable() override;
    virtual void disable() override;

    virtual void accept(CNVisitorPtr visitor) override;
    virtual void setListener(std::shared_ptr<MenuEntryListener> listener) override;
private:
    virtual void setChecked(bool checked);
    virtual void setEnbaled(bool enabled);

    virtual void connectToAction();

    QtActionPtr me();
private:
    std::shared_ptr<CNAcceptor> acceptor;
    std::shared_ptr<MenuEntryListener> listener;

    QAction* action;

private slots:
    virtual void onTriggered(bool checked = false);
};

#endif //QTVIEWS_QTACTION_H