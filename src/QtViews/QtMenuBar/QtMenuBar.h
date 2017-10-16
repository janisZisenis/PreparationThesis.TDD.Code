#ifndef QTVIEWS_QTMENUBAR_H
#define QTVIEWS_QTMENUBAR_H

#include <CrossNative/CNVisitable/CNVisitable.h>

class CNAcceptor;
class QMenuBar;
class QAction;

class QtMenuBar;
typedef std::shared_ptr<QtMenuBar> QtMenuBarPtr;

class QtMenuBar : public CNVisitable, public std::enable_shared_from_this<QtMenuBar> {
public:
    static QtMenuBarPtr getNewInstance();
    virtual ~QtMenuBar();
private:
    QtMenuBar();

public:
    virtual QMenuBar* getQMenuBar();

    virtual void addQAction(QAction* qAction);
    virtual void removeQAction(QAction* qAction);

    void accept(CNVisitorPtr visitor) override;

private:
    QtMenuBarPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;
    QMenuBar* menuBar;
};



#endif //QTVIEWS_QTMENUBAR_H