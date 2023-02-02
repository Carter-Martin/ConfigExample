import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.LocalStorage 2.0
// Import the settings module
import settings 1.0

Window {
    // Accessing the properties in Settings
    width: Settings.width
    height: Settings.height
    visible: true
    title: qsTr("Settings Test")
}
