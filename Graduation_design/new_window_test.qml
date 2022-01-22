import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import Tool_InterAction 1.0
import QtQuick.LocalStorage 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import "database.js" as DB

Window {
    id: new_window
    x: main_window.x
    y: main_window.y
    width: main_window.width
    height: main_window.height

    title: "hello world"




    Button {
        text: "Click to open"
        onClicked: {
            swipe_view.currentIndex = 3;
        }

    }


}
