import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World") + globalTranslator.language

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: qsTr("Hello World") + globalTranslator.language
        }

        Repeater {
            model: globalTranslator.languages
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: modelData
                onClicked: {
                    globalTranslator.setLanguage(modelData)
                }
            }
        }
    }
}
