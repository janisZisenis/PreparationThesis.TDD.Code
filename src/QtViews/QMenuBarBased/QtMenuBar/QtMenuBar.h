#ifndef QTVIEWS_QTMENUBAR_H
#define QTVIEWS_QTMENUBAR_H

#include <CrossNative/CNVisitable/CNVisitable.h>
#include "QtViews/QMenuBarBased/QMenuBarBased.h"

class QActionBased;

class CNAcceptor;
class QMenuBar;
class QAction;

class QtMenuBar;
typedef std::shared_ptr<QtMenuBar> QtMenuBarPtr;

class QtMenuBar : public QMenuBarBased, public virtual CNVisitable, public std::enable_shared_from_this<QtMenuBar> {
public:
    static QtMenuBarPtr getNewInstance();
    virtual ~QtMenuBar();
private:
    QtMenuBar();

public:
    virtual QMenuBar* getQMenuBar() override ;

    virtual void addQAction(std::shared_ptr<QActionBased> qActionBased);
    virtual void removeQAction(std::shared_ptr<QActionBased> qActionBased);

    void accept(CNVisitorPtr visitor) override;

private:
    QtMenuBarPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;
    QMenuBar* menuBar;
};



#endif //QTVIEWS_QTMENUBAR_H