#include "cans_info.h"

// CANS_Info::CANS_Info() {}

CANS_Info::CANS_Info(QObject *parent) /* //from CAN Data Model */: m_dataModel(new CANDataModel(this))
{}

CANS_Info::~CANS_Info()
{
    for (auto device: std::as_const(m_device))
    {
        device->disconnectDevice();
        delete device;
    }
}

bool CANS_Info::initializeCANInterface()
{
    QStringList interface = getAvailableInterface();
    bool atLeastOneConnected = false;
    for (const QString &interface : interface)
    {
        if (connectToInterface(interface))
            atLeastOneConnected = true;
    }
    return atLeastOneConnected;
}

QStringList CANS_Info::getAvailableInterface() const
{
    QStringList result;
    if (QCanBus::instance()->plugins().contains(QStringLiteral("socketcan")))
    {
        QString errorString;
        QList<QCanBusDeviceInfo> devices = QCanBus::instance()->availableDevices(QString("socketcan"), &errorString);
        if (!errorString.isEmpty())
            qWarning() << "Error getting available interfaces:" << errorString;
        else
        {
            for (const QCanBusDeviceInfo &deviceInfo: devices)
                result.append(deviceInfo.name());
        }
    }
    return result;
}

bool CANS_Info::connectToInterface(const QString &interfaceName)
{
    if (m_device.contains(interfaceName))
    {
        qDebug() << "Already Connected to" << interfaceName;
        return true;
    }

    QCanBusDevice *device = QCanBus::instance()->createDevice(
        QStringLiteral("socketcan"), interfaceName
        );

    if (device)
    {
        connect(device, &QCanBusDevice::framesReceived, this, &CANS_Info::readFrame);
        if (device->connectDevice())
        {
            m_device[interfaceName] = device;
            qDebug() << "Connected to " << interfaceName;
            return true;
        }
        else
            qWarning() << "Failed to Connect to" << interfaceName << ":" << device->errorString();
    }
    else
    {
        qWarning() << "Failed to create device for" << interfaceName;
    }
    
    return false;
}

void CANS_Info::sendFrame(const QString &interfaceName, const QCanBusFrame &frame)
{
    if (m_device.contains(interfaceName))
        m_device[interfaceName]->writeFrame(frame);
    else
        qWarning() << "Attempt to send frame on non-connected interface" << interfaceName;
}

void CANS_Info::readFrame()
{
    QCanBusDevice *device = qobject_cast<QCanBusDevice*>(sender());
    if (!device)
        return ;
    QString interfaceName = m_device.key(device);
    while (device->framesAvailable())
    {
        const QCanBusFrame frame = device->readFrame();
        emit frameReceived(interfaceName, frame);

        // m_lastInterfaceName = interfaceName;
        // m_lastFrameId = QString::number(frame.frameId(), 16);
        // m_lastFrameData = frame.payload().toHex();

        // emit lastInterfaceNameChanged();
        // emit lastFrameIdChanged();
        // emit lastFrameDataChanged();

        //Store the latest CAN data in a QHash
        m_canData[frame.frameId()] = frame.payload().toHex();
        
        //from CAN Data Model
        m_dataModel->addData(interfaceName, QString::number(frame.frameId(), 16), frame.payload().toHex());
        qDebug() << "Received from on" << interfaceName
            << "- id" << QString::number(frame.frameId(), 16)
            << "Data" << frame.payload().toHex();
    }
}


std::vector<uint8_t> CANS_Info::fetchDataSomeIp(uint32_t canId) const
{
    auto it = m_canData.find(canId);
    if (it != m_canData.end())
    {
        QByteArray byteArray = QByteArray::fromHex(it.value().toUtf8());
        return std::vector<uint8_t>(byteArray.begin(), byteArray.end());
    }
    return {};
}

CANDataModel *CANS_Info::dataModel() const
{
    return m_dataModel;
}

// QString CANS_Info::lastInterfaceName() const
// {
//     return m_lastInterfaceName;
// }

// QString CANS_Info::lastFrameId() const
// {
//     return m_lastFrameId;
// }

// QString CANS_Info::lastFrameData() const
// {
//     return m_lastFrameData;
// }
