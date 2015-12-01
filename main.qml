import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true

    MouseArea {
        anchors.fill: parent
        onClicked: {
            client.test();
        }
    }

    Connections{
        target: client
        onBoolFromJava: console.debug("onBoolFromJava:",b)
        onIntFromJava: console.debug("onIntFromJava:",i)
        onStringFromJava: console.debug("onStringFromJava:",s)
        onStringArrayFromJava: console.debug("onStringArrayFromJava", sl)
    }

    Text {
        text: qsTr("Test")
        anchors.centerIn: parent
    }
}

