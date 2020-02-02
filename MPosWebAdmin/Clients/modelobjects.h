#ifndef MODELOBJECTS_H
#define MODELOBJECTS_H

#include <QSqlTableModel>

class ModelObjects : public QSqlTableModel
{
    Q_OBJECT
public:
   explicit ModelObjects(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // MODELOBJECTS_H
