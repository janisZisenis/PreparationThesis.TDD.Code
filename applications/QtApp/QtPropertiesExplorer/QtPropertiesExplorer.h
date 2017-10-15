#ifndef QTAPP_QTPROPERTIESEXPLORER_H
#define QTAPP_QTPROPERTIESEXPLORER_H

#include <memory>
#include <vector>

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
    virtual void* getGraphicRepresentation();

    virtual std::string getTitle();
    virtual bool isVisible();

private:
    virtual void displayProperties(QtPropertiesModel* model);
    virtual void displayEmptyProperties();
    virtual void toggleGUIVisibility();

    QTreeView* tableView;
};

#endif //QTAPP_QTPROPERTIESEXPLORER_H