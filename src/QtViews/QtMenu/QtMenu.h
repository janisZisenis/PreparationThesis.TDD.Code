#ifndef QTVIEW_QTMENUIMP_H
#define QTVIEW_QTMENUIMP_H

#include <memory>
#include <string>

class QAction;
class QMenu;

class QtMenu;
typedef std::shared_ptr<QtMenu> QtMenuPtr;

class QtMenu {
public:
    static QtMenuPtr getNewInstance(std::string title);
    virtual ~QtMenu();
private:
    QtMenu(std::string title);

public:
    virtual QAction* getQAction();

private:
    virtual void initializeEmptyAction();
    virtual void initializeMenu();
    virtual void initializeAction();

private:
    QAction* action;
    QMenu* menu;

    QAction* emptyAction;
};



#endif //QTVIEW_QTMENUIMP_H