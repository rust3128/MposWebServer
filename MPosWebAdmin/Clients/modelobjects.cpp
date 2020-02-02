#include "modelobjects.h"
#include <QBrush>
#include <QColor>

#define COLUMN_IS_ACTIVE 10


ModelObjects::ModelObjects(QObject *parent) :
    QSqlTableModel(parent)
{

}


QVariant ModelObjects::data(const QModelIndex &idx, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        if(idx.column() == COLUMN_IS_ACTIVE){
            if(QSqlTableModel::data(this->index(idx.row(),COLUMN_IS_ACTIVE)).toBool())
                return tr("Да");
            else
                return tr("Нет");
        } else
            return QSqlTableModel::data(idx);
    case Qt::BackgroundColorRole:
        if(!QSqlTableModel::data(this->index(idx.row(),COLUMN_IS_ACTIVE)).toBool()){
            return QBrush(QColor("#F5A9A9"));
        }
        break;
    case Qt::EditRole:
        return  QSqlTableModel::data(idx);
    case Qt::TextAlignmentRole:
        if(idx.column()==COLUMN_IS_ACTIVE)
            return Qt::AlignCenter;
        break;
    }
    return QVariant();
}
