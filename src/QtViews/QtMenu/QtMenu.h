#ifndef QTVIEWS_QTMENU_H
#define QTVIEWS_QTMENU_H

#include <memory>
#include <string>
#include <CrossNative/CNVisitable/CNVisitable.h>

class CNAcceptor;

class QAction;
class QMenu;

class QtMenu;
typedef std::shared_ptr<QtMenu> QtMenuPtr;

class QtMenu : public CNVisitable, public std::enable_shared_from_this<QtMenu> {
public:
    static QtMenuPtr getNewInstance(std::string title);
    virtual ~QtMenu();
private:
    QtMenu(std::string title);

public:
    virtual QAction* getQAction();

    virtual void addQAction(QAction* action);
    virtual void removeQAction(QAction* action);

    virtual void accept(CNVisitorPtr visitor) override;
private:
    virtual void initializeEmptyAction();
    virtual void initializeMenu();
    virtual void initializeAction();

    virtual void addToMenu(QAction *action);
    virtual void removeFromMenu(QAction *action);

    virtual bool menuIsEmpty();
    virtual bool menuContainsEmptyAction();
    virtual void addEmptyActionToMenu();
    virtual void removeEmptyActionFromMenu();

    virtual QtMenuPtr me();
private:
    std::shared_ptr<CNAcceptor> acceptor;

    QAction* action;
    QMenu* menu;

    QAction* emptyAction;
};

#endif //QTVIEWS_QTMENU_H