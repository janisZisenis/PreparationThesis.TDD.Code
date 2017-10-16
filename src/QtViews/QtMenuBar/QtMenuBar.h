#ifndef QTVIEWS_QTMENUBAR_H
#define QTVIEWS_QTMENUBAR_H

#include <memory>

class QMenuBar;
class QAction;

class QtMenuBar;
typedef std::shared_ptr<QtMenuBar> QtMenuBarPtr;

class QtMenuBar {
public:
    static QtMenuBarPtr getNewInstance();
    virtual ~QtMenuBar();
private:
    QtMenuBar();

public:
    virtual QMenuBar* getQMenuBar();

    virtual void addQAction(QAction* qAction);
    virtual void removeQAction(QAction* qAction);

private:
    QMenuBar* menuBar;
};



#endif //QTVIEWS_QTMENUBAR_H