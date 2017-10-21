#ifndef QTVIEWS_QTPROPERTIESEXPLORER_H
#define QTVIEWS_QTPROPERTIESEXPLORER_H

#include <memory>
#include <CrossViews/PropertiesExplorerPresenter/PropertiesExplorerView.h>
#include "QtViews/QtWidget/QtWidget.h"

class CNAcceptor;

class QWidget;
class QTreeView;
class QtPropertiesModel;

class QtPropertiesExplorer;
typedef std::shared_ptr<QtPropertiesExplorer> QtPropertiesExplorerPtr;

class QtPropertiesExplorer : public QtWidget, public PropertiesExplorerView, public std::enable_shared_from_this<QtPropertiesExplorer> {
public:
    static QtPropertiesExplorerPtr getNewInstance();
    virtual ~QtPropertiesExplorer();
private:
    QtPropertiesExplorer();

public:
    virtual QWidget* getQWidget() override;
    virtual std::string getTitle() override;

    void accept(CNVisitorPtr visitor) override;

    virtual void displayPropertiesFor(CNVisitablePtr visitable) override;
    virtual void displayEmptyProperties() override;

private:
    virtual QtPropertiesModel *makePropertiesModel(CNVisitablePtr visitable);

    QtPropertiesExplorerPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    QTreeView* tableView;
};

#endif //QTVIEWS_QTPROPERTIESEXPLORER_H