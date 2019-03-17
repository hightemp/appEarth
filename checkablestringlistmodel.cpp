#include "checkablestringlistmodel.h"

CheckableStringListModel::CheckableStringListModel(QVector<Coordinate> *oCoordinates, QObject *parent) :
    QStringListModel(parent),
    oCoordinates(oCoordinates)
{

}

CheckableStringListModel::CheckableStringListModel(QVector<Coordinate> *oCoordinates, const QStringList &strings, QObject *parent) :
    QStringListModel(strings, parent),
    oCoordinates(oCoordinates)
{

}

Qt::ItemFlags CheckableStringListModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QStringListModel::flags(index);
    if (index.isValid()) {
        return defaultFlags | Qt::ItemIsUserCheckable;
    }
    return defaultFlags;
}

QVariant CheckableStringListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::CheckStateRole) {
        if (this->oCoordinates->size() > index.row()) {
            return (*this->oCoordinates)[index.row()].bShow ? Qt::Checked : Qt::Unchecked;
        }
    }

    return QStringListModel::data(index, role);
}

bool CheckableStringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << __FUNCTION__;

    if (!index.isValid() || role != Qt::CheckStateRole)
        return false;

    if (this->oCoordinates->size() > index.row()) {
        (*this->oCoordinates)[index.row()].bShow = value == Qt::Checked;
    }

    emit dataChanged(index, index);
}
