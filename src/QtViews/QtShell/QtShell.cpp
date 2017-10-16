#include "QtShell.h"
#include "QtShellVisitor.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>

#include <QtWidgets>

QtShellPtr QtShell::getNewInstance() {
    return QtShellPtr(new QtShell());
}
QtShell::~QtShell() {
    delete leftSideBarArea;
    delete rightSideBarArea;
    delete bottomSideBarArea;
    delete centralArea;

    delete horizontalSplitter;
    delete verticalSplitter;

    delete window;
}
QtShell::QtShell() : acceptor(CNAcceptorImp<QtShellVisitor, QtShell>::getNewInstance()){
    initWindow();
    initComponents();
    composeWindow();

    updateSideBarWidths();
}

void QtShell::addQWidget(QWidget* qWidget, QtShellPosition pos) {
    addTabTo(getTabWidgetForPosition(pos), qWidget);
}
void QtShell::removeQWidget(QWidget* qWidget, QtShellPosition pos) {
    removeTabFrom(getTabWidgetForPosition(pos), qWidget);
    qWidget->setParent(nullptr);
}

void QtShell::addQToolBar(QToolBar* qToolBar) {
    window->addToolBar(qToolBar);
}
void QtShell::removeQToolBar(QToolBar* qToolBar) {
    window->removeToolBar(qToolBar);
    qToolBar->setParent(nullptr);
}

void QtShell::addQMenuBar(QMenuBar* qMenuBar) {
    window->setMenuBar(qMenuBar);
}
void QtShell::removeQMenuBar(QMenuBar* qMenuBar) {
    window->setMenuBar(nullptr);
    qMenuBar->setParent(nullptr);
}

void QtShell::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

void QtShell::initWindow() {
    window = new QMainWindow(); //57, 601, 1200, 1000
    window->setWindowTitle("Qt Window Title");
    window->setUnifiedTitleAndToolBarOnMac(true);
    window->resize(1200, 1000);
    window->show();
}
void QtShell::initComponents() {
    initSplitter();
    initSideBarAreas();
    initCentralArea();
}
void QtShell::initSplitter() {
    horizontalSplitter = this->makeSplitView();
    horizontalSplitter->setOrientation(Qt::Vertical);
    verticalSplitter = this->makeSplitView();
}
void QtShell::initSideBarAreas() {
    leftSideBarArea = makeTabWidget();
    rightSideBarArea = makeTabWidget();
    bottomSideBarArea = makeTabWidget();
}
void QtShell::initCentralArea() {
    centralArea = makeTabWidget();
}
void QtShell::composeWindow() {
    horizontalSplitter->addWidget(centralArea);
    horizontalSplitter->addWidget(bottomSideBarArea);

    verticalSplitter->addWidget(leftSideBarArea);
    verticalSplitter->addWidget(horizontalSplitter);
    verticalSplitter->addWidget(rightSideBarArea);

    window->setCentralWidget(verticalSplitter);
}

void QtShell::updateTab(QWidget* qWidget, QtShellPosition pos) {
    if(qWidget->isVisible())
        addTabTo(getTabWidgetForPosition(pos), qWidget);
    else
        removeTabFrom(getTabWidgetForPosition(pos), qWidget);
}
void QtShell::removeTabFrom(QTabWidget *tabWidget, QWidget* qWidget) {
    for(int i = 0; i < tabWidget->count(); i++) {
        if(tabWidget->widget(i) == qWidget) {
            tabWidget->removeTab(i);
            qWidget->setParent(nullptr);
        }
    }
    updateSideBarWidths();
}
void QtShell::addTabTo(QTabWidget *tabWidget, QWidget* qWidget) {
    tabWidget->addTab(qWidget, qWidget->windowTitle());
    updateSideBarWidths();
}

QTabWidget *QtShell::getTabWidgetForPosition(QtShellPosition pos) {
    if(pos == LEFT) return leftSideBarArea;
    if(pos == RIGHT) return rightSideBarArea;
    if(pos == BOTTOM) return bottomSideBarArea;
    else return centralArea;
}

QSplitter *QtShell::makeSplitView() {
    QSplitter* splitter = new QSplitter();
    splitter->setHandleWidth(0);
    return splitter;
}
QTabWidget *QtShell::makeTabWidget() {
    return new QTabWidget();
}

void QtShell::updateSideBarWidths() {
    int left = (getTabWidgetForPosition(LEFT)->count() > 0) ? 250 : 0;
    int right = (getTabWidgetForPosition(RIGHT)->count() > 0) ? 250 : 0;
    int bottom = (getTabWidgetForPosition(BOTTOM)->count() > 0) ? 250 : 0;


    QList<int> horSizes = QList<int>();
    horSizes.push_back(window->height()-bottom); //window->height()-sideBarWidth
    horSizes.push_back(bottom);                  //sideBarWidth
    horizontalSplitter->setSizes(horSizes);

    QList<int> vertSizes = QList<int>();
    vertSizes.push_back(left);
    vertSizes.push_back(window->width()-left-right);
    vertSizes.push_back(right);
    verticalSplitter->setSizes(vertSizes);
}

QtShellPtr QtShell::me() {
    return this->shared_from_this();
}

