#ifndef QTVIEWS_QTSHELL_H
#define QTVIEWS_QTSHELL_H

#include <memory>
#include <Hierarchies/CNVisitable/CNVisitable.h>

class CNAcceptor;

class QWidgetBased;
class QMenuBarBased;
class QToolBarBased;

class QMainWindow;
class QMenuBar;
class QWidget;
class QTabWidget;
class QSplitter;
class QToolBar;

enum QtShellPosition { LEFT, RIGHT, BOTTOM, CENTRAL };

class QtShell;
typedef std::shared_ptr<QtShell> QtShellPtr;

class QtShell : public CNVisitable, public std::enable_shared_from_this<QtShell> {
public:
    static QtShellPtr getNewInstance();
    virtual ~QtShell();
private:
    QtShell();

public:
    virtual void addQtWidget(std::shared_ptr<QWidgetBased> qWidgetBased, QtShellPosition pos);
    virtual void removeQtWidget(std::shared_ptr<QWidgetBased> qWidgetBased, QtShellPosition pos);

    virtual void addQMenuBar(std::shared_ptr<QMenuBarBased> qMenuBarBased);
    virtual void removeQMenuBar(std::shared_ptr<QMenuBarBased> qMenuBarBased);

    virtual void addQToolBar(std::shared_ptr<QToolBarBased> qToolBarBased);
    virtual void removeQToolBar(std::shared_ptr<QToolBarBased> qToolBarBased);

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

    virtual void updateTab(std::shared_ptr<QWidgetBased> qWidgetBased, QtShellPosition pos);
    virtual void removeTabFrom(QTabWidget* tabWidget, std::shared_ptr<QWidgetBased> qWidgetBased);
    virtual void addTabTo(QTabWidget* tabWidget, std::shared_ptr<QWidgetBased> qWidgetBased);

    virtual QTabWidget* getTabWidgetForPosition(QtShellPosition pos);

    virtual void updateSideBarWidths();

    QtShellPtr me();
private:
    std::shared_ptr<CNAcceptor> acceptor;

    QMainWindow* window;
    QSplitter* horizontalSplitter;
    QSplitter* verticalSplitter;

    QTabWidget* centralArea;

    QTabWidget* leftSideBarArea;
    QTabWidget* rightSideBarArea;
    QTabWidget* bottomSideBarArea;
};

#endif //QTVIEWS_QTSHELLIMP_H