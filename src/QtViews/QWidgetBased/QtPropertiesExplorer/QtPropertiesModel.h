#ifndef QTVIEWS_QTPROPERTIESMODEL_H
#define QTVIEWS_QTPROPERTIESMODEL_H

#include <QAbstractItemModel>
#include <memory>

class QtPropertiesItem;

class QtPropertiesModel : public QAbstractItemModel {
public:
    QtPropertiesModel();
    virtual ~QtPropertiesModel();

    virtual void addItem(std::shared_ptr<QtPropertiesItem> item);
    virtual void deleteIndex(QModelIndex index);

    virtual QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    virtual int rowCount(const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual int columnCount(const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
protected:
    virtual QVariant getDataAt(QtPropertiesItem* item, int role, int col) const;

    virtual QtPropertiesItem* getItem(const QModelIndex &index) const;
    QtPropertiesItem* getChildItem(QtPropertiesItem* parent, int row) const;
    QtPropertiesItem* getParentItem(QtPropertiesItem* child) const;
    QModelIndex getIndex(std::shared_ptr<QtPropertiesItem> item);

protected:
    std::shared_ptr<QtPropertiesItem> root;
};

#endif //QTVIEWS_QTPROPERTIESMODEL_H