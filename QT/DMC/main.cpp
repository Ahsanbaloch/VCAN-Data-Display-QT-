#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "cans_info.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CANS_Info can_info;
    if (can_info.initializeCANInterface())
        qDebug() << "Connected Interface: " << can_info.getAvailableInterface();

    qmlRegisterType<CANS_Info>("cans_info", 1, 0, "CANSInfo");

    QObject::connect(&can_info, &CANS_Info::frameReceived, [](const QString &interface, const QCanBusFrame &frame){});
    // QObject::connect(
    //     &engine,
    //     &QQmlApplicationEngine::objectCreationFailed,
    //     &app,
    //     []() { QCoreApplication::exit(-1); },
    //     Qt::QueuedConnection);
    // engine.loadFromModule("DMC", "Main");
    engine.load(QUrl(QStringLiteral("qrc:/DMC/Main.qml")));

    return app.exec();
}
