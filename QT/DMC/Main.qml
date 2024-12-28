import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import cans_info 1.0

Window {
    width: 1000
    height: 600
    visible: true
    title: qsTr("CAN Data Monitor")
    color: "#2c3e50"

    CANSInfo {
        id: canInfo
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        Rectangle {
            Layout.fillWidth: true
            height: 60
            color: "#34495e"

            Text {
                anchors.centerIn: parent
                text: "CAN Data Monitor"
                font.pixelSize: 24
                color: "white"
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.margins: 10

            TextField {
                id: filterField
                Layout.fillWidth: true
                placeholderText: "Filter by Interface or Frame ID"
                color: "white"
                background: Rectangle {
                    color: "#34495e"
                    radius: 5
                }
            }

            Button {
                text: "Clear Filter"
                onClicked: filterField.text = ""
            }

            Switch {
                id: autoScrollSwitch
                text: "Auto-scroll"
                checked: true
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#34495e"
            radius: 5

            ListView {
                id: canListView
                anchors.fill: parent
                anchors.margins: 5
                clip: true
                model: canInfo.dataModel
                spacing: 1

                ScrollBar.vertical: ScrollBar {}

                header: Rectangle {
                    width: parent.width
                    height: 30
                    color: "#2c3e50"

                    Row {
                        anchors.fill: parent
                        Text { text: "Timestamp"; width: 150; color: "white"; font.bold: true }
                        Text { text: "Interface"; width: 100; color: "white"; font.bold: true }
                        Text { text: "Frame ID"; width: 100; color: "white"; font.bold: true }
                        Text { text: "Payload"; color: "white"; font.bold: true }
                    }
                }

                delegate: Rectangle {
                    width: canListView.width
                    height: 30
                    color: index % 2 ? "#3498db" : "#2980b9"

                    Row {
                        anchors.fill: parent
                        spacing: 5

                        Text {
                            text: Qt.formatDateTime(new Date(), "hh:mm:ss.zzz")
                            width: 150
                            color: "white"
                        }
                        Text {
                            text: model.interface
                            width: 100
                            color: "white"
                        }
                        Text {
                            text: model.frameId
                            width: 100
                            color: model.frameId === "000" ? "yellow" : "white"
                        }
                        Text {
                            text: model.payload
                            color: "white"
                            font.family: "Courier"
                        }
                    }

                    visible: {
                        if (filterField.text === "") return true;
                        return model.interface.toLowerCase().includes(filterField.text.toLowerCase()) ||
                               model.frameId.toLowerCase().includes(filterField.text.toLowerCase());
                    }
                }

                onCountChanged: {
                    if (autoScrollSwitch.checked) {
                        canListView.positionViewAtEnd();
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        if(canInfo.initializeCANInterface()) {
            console.log("CAN Interface initialized successfully")
        } else {
            console.log("Failed to initialize CAN Interface")
        }
    }
}
