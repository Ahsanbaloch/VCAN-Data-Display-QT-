#ifndef CANDATAMODEL_H
#define CANDATAMODEL_H

#include <QAbstractListModel>
#include <QList>

class CANDataModel : public QAbstractListModel
{
    Q_OBJECT

    public:

        enum Roles
        {
            InterfaceRole = Qt::UserRole + 1,
            FrameIdRole,
            PayloadRole
        };
        // CANDataModel();

        explicit CANDataModel(QObject *parent = nullptr);

        void addData(const QString &interface, const QString &frameId, const QString &payload);
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        QHash<int, QByteArray> roleNames() const override;

    private:
        struct CANData
        {
            QString interface;
            QString frameId;
            QString payload;
        };
        QList<CANData> m_data;
};

#endif // CANDATAMODEL_H
