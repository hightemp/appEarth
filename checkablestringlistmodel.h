#ifndef CHECKABLESTRINGLISTMODEL_H
#define CHECKABLESTRINGLISTMODEL_H

#include <QObject>
#include <QWidget>
#include <QStringListModel>
#include "surface.h"

class CheckableStringListModel : public QStringListModel
{
public:
    CheckableStringListModel(QVector<Coordinate> *oCoordinates, QObject* parent = 0);
    CheckableStringListModel(QVector<Coordinate> *oCoordinates, const QStringList & strings, QObject* parent = 0);
    Qt::ItemFlags flags (const QModelIndex& index) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
private:
    QVector<Coordinate> *oCoordinates;
};

#endif // CHECKABLESTRINGLISTMODEL_H
