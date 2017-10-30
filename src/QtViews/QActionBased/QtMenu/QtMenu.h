#ifndef QTVIEWS_QTMENU_H
#define QTVIEWS_QTMENU_H

#include <memory>
#include <string>
#include <Hierarchies/CNTagged/CNTagged.h>
#include <CrossViews/DynamicMenuPresenter/MenuView.h>
#include "QtViews/QActionBased/QActionBased.h"

class CNAcceptor;

class QMenuBarBased;

class QAction;
class QMenu;

class QtMenu;
typedef std::shared_ptr<QtMenu> QtMenuPtr;

class QtMenu : public QActionBased, public CNTagged, public MenuView, public std::enable_shared_from_this<QtMenu> {
public:
    static QtMenuPtr getNewInstance(std::string title);
    virtual ~QtMenu();
private:
    QtMenu(std::string title);

public:
    virtual QAction* getQAction() override;

    virtual void addQAction(QActionBasedPtr qActionBased);
    virtual void removeQAction(QActionBasedPtr qActionBased);

    virtual void accept(CNVisitorPtr visitor) override;
    virtual void setTag(std::string tag);
    virtual std::string getTag() override;
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
    std::shared_ptr<CNAcceptor> typeAcceptor;
    std::shared_ptr<CNAcceptor> tagAcceptor;
    std::string tag;

    QAction* action;
    QMenu* menu;

    QAction* emptyAction;
};

#endif //QTVIEWS_QTMENU_H