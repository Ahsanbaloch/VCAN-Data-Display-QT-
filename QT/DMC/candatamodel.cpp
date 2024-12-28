#include "candatamodel.h"

// CANDataModel::CANDataModel() {}

CANDataModel::CANDataModel(QObject *parent) : QAbstractListModel(parent) {}

void CANDataModel::addData(const QString &interface, const QString &frameId, const QString &payload)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append({interface, frameId, payload});
    endInsertRows();
}

int CANDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

QVariant CANDataModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count())
        return QVariant();
    
    const auto &item = m_data[index.row()];
    switch (role)
    {
    case InterfaceRole:
        return item.interface;
    case FrameIdRole:
        return item.frameId;
    case PayloadRole:
        return item.payload;
    }
    return QVariant();
}

QHash<int, QByteArray> CANDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[InterfaceRole] = "interface";
    roles[FrameIdRole] = "frameId";
    roles[PayloadRole] = "payload";
    return roles;
}