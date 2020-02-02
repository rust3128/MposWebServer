#ifndef MODELUSERS_H
#define MODELUSERS_H
#include <QSqlTableModel>

class ModelUsers : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit ModelUsers(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // MODELUSERS_H
