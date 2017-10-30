#include "QtShell.h"
#include "QtShellVisitor.h"
#include <CrossHierarchies/CNAcceptor/CNAcceptorImp.h>

#include "QtViews/QWidgetBased/QWidgetBased.h"
#include "QtViews/QMenuBarBased/QMenuBarBased.h"
#include "QtViews/QToolBarBased/QToolBarBased.h"

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

void QtShell::addQtWidget(QWidgetBasedPtr qWidgetBased, QtShellPosition pos) {
    addTabTo(getTabWidgetForPosition(pos), qWidgetBased);
}
void QtShell::removeQtWidget(QWidgetBasedPtr qWidgetBased, QtShellPosition pos) {
    removeTabFrom(getTabWidgetForPosition(pos), qWidgetBased);
    qWidgetBased->getQWidget()->setParent(nullptr);
}

void QtShell::addQToolBar(QToolBarBasedPtr qToolBarBased) {
    window->addToolBar(qToolBarBased->getQToolBar());
}
void QtShell::removeQToolBar(QToolBarBasedPtr qToolBarBased) {
    window->removeToolBar(qToolBarBased->getQToolBar());
    qToolBarBased->getQToolBar()->setParent(nullptr);
}

void QtShell::addQMenuBar(QMenuBarBasedPtr qMenuBarBased) {
    window->setMenuBar(qMenuBarBased->getQMenuBar());
}
void QtShell::removeQMenuBar(QMenuBarBasedPtr qMenuBarBased) {
    window->setMenuBar(nullptr);
    qMenuBarBased->getQMenuBar()->setParent(nullptr);
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

void QtShell::updateTab(std::shared_ptr<QWidgetBased> qWidgetBased, QtShellPosition pos) {
    if(qWidgetBased->getQWidget()->isVisible())
        addTabTo(getTabWidgetForPosition(pos), qWidgetBased);
    else
        removeTabFrom(getTabWidgetForPosition(pos), qWidgetBased);
}
void QtShell::removeTabFrom(QTabWidget *tabWidget, QWidgetBasedPtr qWidgetBased) {
    for(int i = 0; i < tabWidget->count(); i++) {
        if(tabWidget->widget(i) == qWidgetBased->getQWidget()) {
            tabWidget->removeTab(i);
            qWidgetBased->getQWidget()->setParent(nullptr);
        }
    }
    updateSideBarWidths();
}
void QtShell::addTabTo(QTabWidget *tabWidget, QWidgetBasedPtr qWidgetBased) {
    tabWidget->addTab(qWidgetBased->getQWidget(), QString::fromStdString(qWidgetBased->getTitle()));
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

