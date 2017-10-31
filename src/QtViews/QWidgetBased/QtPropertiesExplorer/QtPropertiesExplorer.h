#ifndef QTVIEWS_QTPROPERTIESEXPLORER_H
#define QTVIEWS_QTPROPERTIESEXPLORER_H

#include <memory>
#include <CrossViews/CNPropertiesExplorerPresenter/CNPropertiesExplorerView.h>
#include "QtViews/QWidgetBased/QWidgetBased.h"

class CNAcceptor;

class QtPropertiesModelFactory;

class QWidget;
class QTreeView;
class QtPropertiesModel;

class QtPropertiesExplorer;
typedef std::shared_ptr<QtPropertiesExplorer> QtPropertiesExplorerPtr;

class QtPropertiesExplorer : public QWidgetBased, public CNPropertiesExplorerView, public std::enable_shared_from_this<QtPropertiesExplorer> {
public:
    static QtPropertiesExplorerPtr getNewInstance(std::shared_ptr<QtPropertiesModelFactory> modelFactory);
    virtual ~QtPropertiesExplorer();
private:
    QtPropertiesExplorer(std::shared_ptr<QtPropertiesModelFactory> modelFactory);

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
    std::shared_ptr<QtPropertiesModelFactory> modelFactory;

    QTreeView* tableView;
};

#endif //QTVIEWS_QTPROPERTIESEXPLORER_H