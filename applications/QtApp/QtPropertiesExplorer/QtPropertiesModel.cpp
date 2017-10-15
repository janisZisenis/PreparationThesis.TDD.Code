#include "QtPropertiesModel.h"
#include "QtPropertiesItem.h"

QtPropertiesModel::QtPropertiesModel() : QAbstractItemModel(), root(QtPropertiesItem::getNewInstance("", "")) {}
QtPropertiesModel::~QtPropertiesModel() {}


QVariant QtPropertiesModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0) return "Property";
        if (section == 1) return "Value";
    }
    return QVariant();
}

void QtPropertiesModel::addItem(QtPropertiesItemPtr item) {
    beginInsertRows(QModelIndex(),root->getChildCount(), root->getChildCount());
    root->appendChild(item);
    endInsertRows();
}

void QtPropertiesModel::deleteIndex(QModelIndex index) {
    if(index.isValid()) {
        beginRemoveRows(QModelIndex(),index.row(), index.row());
        root->removeChild(index.row());
        endRemoveRows();
    }
}

QModelIndex QtPropertiesModel::parent(const QModelIndex &child) const {
    QtPropertiesItem* parentItem = getParentItem(getItem(child));
    if (!parentItem || parentItem == root.get()) return QModelIndex();
    return createIndex(parentItem->getRow(), 0, parentItem);
}

int QtPropertiesModel::rowCount(const QModelIndex &parent) const {
    return getItem(parent)->getChildCount();
}

int QtPropertiesModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant QtPropertiesModel::data(const QModelIndex &index, int role) const {
    return getDataAt(getItem(index), role, index.column());
}

QModelIndex QtPropertiesModel::index(int row, int column, const QModelIndex &parent) const {
    QtPropertiesItem *childItem = getChildItem(getItem(parent), row);
    if (!childItem) return QModelIndex();
    return createIndex(row, column, childItem);
}

QtPropertiesItem *QtPropertiesModel::getItem(const QModelIndex &index) const {
    if (!index.isValid()) return root.get();
    return static_cast<QtPropertiesItem*>(index.internalPointer());
}

QtPropertiesItem* QtPropertiesModel::getChildItem(QtPropertiesItem* parent, int row) const {
    if (row < parent->getChildCount())
        return parent->getChildAt(row).get();
    return nullptr;
}

QtPropertiesItem* QtPropertiesModel::getParentItem(QtPropertiesItem* child) const {
    if (!child->getParent()) return nullptr;
    return child->getParent().get();
}

QModelIndex QtPropertiesModel::getIndex(QtPropertiesItemPtr item) {
    if (item == root) return QModelIndex();
    return createIndex(item->getRow(), 0, item.get());
}

QVariant QtPropertiesModel::getDataAt(QtPropertiesItem *item, int role, int col) const {
    if (role == Qt::DisplayRole) {
        if (col == 0) return QString::fromStdString(item->getProperty());
        if (col == 1) return QString::fromStdString(item->getValue());
    }

    return QVariant();
}