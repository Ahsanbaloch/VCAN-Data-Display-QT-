#ifndef CANS_INFO_H
#define CANS_INFO_H

#include <QObject>
#include <QCanBus>
#include <QDebug>
#include <candatamodel.h>

class CANS_Info : public QObject
{
    Q_OBJECT
    // Q_PROPERTY(QString lastInterfaceName READ lastInterfaceName NOTIFY lastInterfaceNameChanged)
    // Q_PROPERTY(QString lastFrameId READ lastFrameId NOTIFY lastFrameIdChanged)
    // Q_PROPERTY(QString lastFrameData READ lastFrameData NOTIFY lastFrameDataChanged)
    //from CAN DATA Model
    Q_PROPERTY(CANDataModel* dataModel READ dataModel CONSTANT)

    public:
        // CANS_Info();
        explicit CANS_Info(QObject *parent = nullptr);
        ~CANS_Info();

        //send the value to check if there is CAN_Interface available or intialized
        Q_INVOKABLE bool initializeCANInterface(); 
        // through QCANBUs it checks if there is socket  with name of "socketcan" and then store those CANs info
        QStringList getAvailableInterface() const;

        // if connect with interface then it connect signal to slot readFrame to read the frame
        bool connectToInterface(const QString &interfaceName);

        //stores the frame in the Map with interfaceName
        void sendFrame(const QString &interfaceName, const QCanBusFrame &frame);


        // QString lastInterfaceName() const;
        // QString lastFrameId() const;
        // QString lastFrameData() const;

        //from CAN Data Model
        CANDataModel* dataModel() const;

        //fetching the CAN for Some/IP
        std::vector<uint8_t> fetchDataSomeIp(uint32_t canId) const;
    
    /* 
    Signals
    Signals are emitted by objects when they change state or when an event occurs.
    They are declared in the signals section of a class.
    Signals do not have a return type and can have parameters.
    When a signal is emitted, it can be connected to one or more slots.
    */
    signals:
        void frameReceived(const QString &interfaceName, const QCanBusFrame &frame);
        // void lastInterfaceNameChanged();
        // void lastFrameIdChanged();
        // void lastFrameDataChanged();
        

    /* 
    Slots
    Slots are functions that are called in response to a particular signal.
    They are declared in the slots section of a class.
    Slots can be regular member functions, and they can also be virtual.
    Slots can be public, protected, or private.
    */
    private slots:
        void readFrame();
    
    private:
        QMap<QString, QCanBusDevice*> m_device;
        QString m_lastInterfaceName;
        QString m_lastFrameId;
        QString m_lastFrameData;
        //from CAN Data Model
        CANDataModel* m_dataModel;

        //Hash to store the latest CAN data
        QHash<uint32_t, QString> m_canData;
};

#endif // CANS_INFO_H





/* 

signals:
    void mySignal(int value);

public slots:
    void mySlot(int value) {
        qDebug() << "Slot called with value:" << value;
    }
};

int main() {
    MyObject obj;
    QObject::connect(&obj, &MyObject::mySignal, &obj, &MyObject::mySlot);

    emit obj.mySignal(42); // This will call mySlot with the value 42

    return 0;
}
 */