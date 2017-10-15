#ifndef QTAPP_QTPROPERTIESEXPLORER_H
#define QTAPP_QTPROPERTIESEXPLORER_H

#include <memory>
#include <vector>

class QWidget;
class QTreeView;
class QtPropertiesModel;

class QtPropertiesExplorer;
typedef std::shared_ptr<QtPropertiesExplorer> QtPropertiesExplorerPtr;

class QtPropertiesExplorer {
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

private:
    virtual void displayProperties(QtPropertiesModel* model);
    virtual void displayEmptyProperties();

    QTreeView* tableView;
};

#endif //QTAPP_QTPROPERTIESEXPLORER_H