#include "QtSolutionModel.h"
#include "QtSolutionItem.h"

QtSolutionModel::QtSolutionModel() : QAbstractItemModel(), root(QtSolutionItem::getNewInstance("", "")) {}
QtSolutionModel::~QtSolutionModel() {}


QVariant QtSolutionModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0) return "Name";
        if (section == 1) return "Type";
    }
    return QVariant();
}

void QtSolutionModel::insertItem(QtSolutionItemPtr item, QModelIndex index, int childPos) {
    beginInsertRows(index, childPos, childPos);
    getItem(index)->insertChild(item, childPos);
    endInsertRows();
}

void QtSolutionModel::deleteIndex(QModelIndex index, int childPos) {
    beginRemoveRows(index, childPos, childPos);
    getItem(index)->removeChild(childPos);
    endRemoveRows();
}

QModelIndex QtSolutionModel::parent(const QModelIndex &child) const {
    QtSolutionItem* parentItem = getParentItem(getItem(child));
    if (!parentItem || parentItem == root.get()) return QModelIndex();
    return createIndex(parentItem->getRow(), 0, parentItem);
}

int QtSolutionModel::rowCount(const QModelIndex &parent) const {
    return getItem(parent)->getChildCount();
}

int QtSolutionModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant QtSolutionModel::data(const QModelIndex &index, int role) const {
    return getDataAt(getItem(index), role, index.column());
}

QModelIndex QtSolutionModel::index(int row, int column, const QModelIndex &parent) const {
    QtSolutionItem *childItem = getChildItem(getItem(parent), row);
    if (!childItem) return QModelIndex();
    return createIndex(row, column, childItem);
}

QtSolutionItem *QtSolutionModel::getItem(const QModelIndex &index) const {
    if (!index.isValid()) return root.get();
    return static_cast<QtSolutionItem*>(index.internalPointer());
}

QtSolutionItem* QtSolutionModel::getChildItem(QtSolutionItem* parent, int row) const {
    if (row < parent->getChildCount())
        return parent->getChildAt(row).get();
    return nullptr;
}

QtSolutionItem* QtSolutionModel::getParentItem(QtSolutionItem* child) const {
    if (!child->getParent()) return nullptr;
    return child->getParent().get();
}

QModelIndex QtSolutionModel::getIndex(QtSolutionItemPtr item) {
    if (item == root) return QModelIndex();
    return createIndex(item->getRow(), 0, item.get());
}

QVariant QtSolutionModel::getDataAt(QtSolutionItem *item, int role, int col) const {
    if (role == Qt::DisplayRole) {
        if (col == 0) return QString::fromStdString(item->getName());
        if (col == 1) return QString::fromStdString(item->getType());
    }

    return QVariant();
}

QModelIndex QtSolutionModel::transformIndex(HierarchyIndex index) {
    QModelIndex qIndex = QModelIndex();

    for(int i = 0; i < index.depth(); i++)
        qIndex = this->index(index[i], 0, qIndex);

    return qIndex;
}
