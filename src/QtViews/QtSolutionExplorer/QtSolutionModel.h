#ifndef QTVIEWS_QTSOLUTIONMODEL_H
#define QTVIEWS_QTSOLUTIONMODEL_H

#include <memory>

#include <QAbstractItemModel>
#include <CrossViews/HierarchyIndex/HierarchyIndex.h>

class QtSolutionItem;

class QtSolutionModel : public QAbstractItemModel {
public:
    QtSolutionModel();
    virtual ~QtSolutionModel();

    virtual void insertItem(std::shared_ptr<QtSolutionItem> item, const QModelIndex &index, int childPos);
    virtual void deleteIndex(const QModelIndex &index, int childPos);

    virtual QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    virtual int rowCount(const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual int columnCount(const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    virtual QModelIndex transformToQModelIndex(const HierarchyIndex &index);
    virtual HierarchyIndex transformToHierarchyIndex(const QModelIndex &index);

private:
    virtual QVariant getDataAt(QtSolutionItem* item, int role, int col) const;

    virtual QtSolutionItem* getItem(const QModelIndex &index) const;
    QtSolutionItem* getChildItem(QtSolutionItem* parent, int row) const;
    QtSolutionItem* getParentItem(QtSolutionItem* child) const;
    QModelIndex getIndex(std::shared_ptr<QtSolutionItem> item);

private:
    std::shared_ptr<QtSolutionItem> root;
};

#endif //QTVIEWS_QTSOLUTIONMODEL_H