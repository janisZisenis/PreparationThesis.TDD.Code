#ifndef QTVIEWS_QTPROPERTIESEXPLORER_H
#define QTVIEWS_QTPROPERTIESEXPLORER_H

#include <memory>
#include <CrossNative/CNVisitable/CNVisitable.h>

class CNAcceptor;

class QWidget;
class QTreeView;
class QtPropertiesModel;

class QtPropertiesExplorer;
typedef std::shared_ptr<QtPropertiesExplorer> QtPropertiesExplorerPtr;

class QtPropertiesExplorer : public CNVisitable, public std::enable_shared_from_this<QtPropertiesExplorer> {
public:
    static QtPropertiesExplorerPtr getNewInstance();
    virtual ~QtPropertiesExplorer();
private:
    QtPropertiesExplorer();

public:
    virtual QWidget* getQWidget();

    virtual std::string getTitle();
    virtual bool isVisible();
    virtual void toggleVisibility();

    void accept(CNVisitorPtr visitor) override;

    virtual void displayProperties(QtPropertiesModel* model);
    virtual void displayEmptyProperties();

private:
    QtPropertiesExplorerPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    QTreeView* tableView;
};

#endif //QTVIEWS_QTPROPERTIESEXPLORER_H