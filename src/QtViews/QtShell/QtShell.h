#ifndef QTVIEWS_QTSHELL_H
#define QTVIEWS_QTSHELL_H

#include <memory>
#include <CrossNative/CNVisitable/CNVisitable.h>

enum QtShellPosition { LEFT, RIGHT, BOTTOM, CENTRAL };

class QMainWindow;
class QMenuBar;
class QWidget;
class QTabWidget;
class QSplitter;
class QToolBar;

class QtShell;
typedef std::shared_ptr<QtShell> QtShellPtr;

class QtShell : public CNVisitable, public std::enable_shared_from_this<QtShell> {
public:
    static QtShellPtr getNewInstance();
    virtual ~QtShell();
private:
    QtShell();

public:
    virtual void addQWidget(QWidget* widget, QtShellPosition pos);
    virtual void removeQWidget(QWidget* qWidget, QtShellPosition pos);

    virtual void addQMenuBar(QMenuBar* qMenuBar);
    virtual void removeQMenuBar(QMenuBar* qMenuBar);

    virtual void addQToolBar(QToolBar* qToolBar);
    virtual void removeQToolBar(QToolBar* qToolBar);

    void accept(CNVisitorPtr visitor) override;
private:
    virtual void initWindow();
    virtual void initComponents();
    virtual void initSplitter();
    virtual QSplitter* makeSplitView();
    virtual void initSideBarAreas();
    virtual void initCentralArea();
    virtual QTabWidget* makeTabWidget();
    virtual void composeWindow();

    virtual void updateTab(QWidget* qWidget, QtShellPosition pos);
    virtual void removeTabFrom(QTabWidget* tabWidget, QWidget* qWidget);
    virtual void addTabTo(QTabWidget* tabWidget, QWidget* qWidget);

    virtual QTabWidget* getTabWidgetForPosition(QtShellPosition pos);

    virtual void updateSideBarWidths();

    QtShellPtr me();
private:
    QMainWindow* window;
    QSplitter* horizontalSplitter;
    QSplitter* verticalSplitter;

    QTabWidget* centralArea;

    QTabWidget* leftSideBarArea;
    QTabWidget* rightSideBarArea;
    QTabWidget* bottomSideBarArea;
};

#endif //QTVIEWS_QTSHELLIMP_H