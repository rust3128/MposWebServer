#include "modelusers.h"
#include <QBrush>

ModelUsers::ModelUsers(QObject *parent) :
    QSqlTableModel(parent)
{

}


QVariant ModelUsers::data(const QModelIndex &idx, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        if(idx.column() == 7){
            if(QSqlTableModel::data(this->index(idx.row(),7)).toBool())
                return tr("Есть");
            else
                return tr("Нет");
        } else
            return QSqlTableModel::data(idx);
    case Qt::BackgroundColorRole:
        if(!QSqlTableModel::data(this->index(idx.row(),7)).toBool()){
            return QBrush(QColor("#F5A9A9"));
        }
        break;
    case Qt::EditRole:
        return  QSqlTableModel::data(idx);
    case Qt::TextAlignmentRole:
        if(idx.column()==7)
            return Qt::AlignCenter;
        break;
    }
    return QVariant();
}
