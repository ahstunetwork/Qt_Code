import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import Tool_InterAction 1.0
import QtQuick.LocalStorage 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import "database.js" as DB

ApplicationWindow {
    id: main_window
    visible: true
    width: 350
    height: 710
    title: qsTr("English_study")

    Tool_InterAction {
        id: tool_interaction
    }

    SwipeView {
        id: swipe_view
//        width: parent.width
//        height: parent.height*9/10
        anchors.fill: parent
        currentIndex: tabBar.currentIndex


        Page_1_word {

        }

        Page_2_word_list {

        }

        Page_3_statistics {

        }

        Page_4_account {

        }
    }

//    Rectangle {
//        id: swipe_ctrl_btn_rec

//        width: parent.width
//        height: parent.height/10
//        anchors.bottom: parent.bottom

//        color: "#bbffaa"

//        Button {
//            id: swipe_ctrl_btn_word

//            anchors.left: parent.left
//            anchors.bottom: parent.bottom

//            width: parent.width/4
//            height: parent.height
//            text: "word"

//            onClicked: {
//                swipe_view.currentIndex = 0
//            }
//        }

//        Button {
//            id: swipe_ctrl_btn_word_list


//            anchors.left: swipe_ctrl_btn_word.right
//            anchors.bottom: parent.bottom

//            width: parent.width/4
//            height: parent.height
//            text: "word"

//            onClicked: {
//                swipe_view.currentIndex = 1
//            }
//        }
//        Button {

//            id: swipe_ctrl_btn_statistics


//            anchors.left: swipe_ctrl_btn_word_list.right
//            anchors.bottom: parent.bottom

//            width: parent.width/4
//            height: parent.height
//            text: "word"


//            onClicked: {
//                swipe_view.currentIndex = 2
//            }
//        }
//        Button {

//            id: swipe_ctrl_btn_account


//            anchors.left: swipe_ctrl_btn_statistics.right
//            anchors.bottom: parent.bottom


//            width: parent.width/4
//            height: parent.height
//            text: "word"

//            flat: true


//            icon: "qrc:/image/mark_transparent.png";

//            onClicked: {
//                swipe_view.currentIndex = 3
//            }
//        }


//    }






    footer: TabBar {
        id: tabBar

        currentIndex: swipe_view.currentIndex

        TabButton {
            id:  tab_btn_1

            Comp_Icon_buttom {
                anchors.fill: parent
                btn_function: "word"
                image_path: "qrc:/image/word_tr.png"

            }

        }

        TabButton {
            id:  tab_btn_2

            Comp_Icon_buttom {
                anchors.fill: parent

                btn_function: "word_list"
                image_path: "qrc:/image/word_list_tr.png"
            }

        }

        TabButton {
            id:  tab_btn_3

            Comp_Icon_buttom {
                anchors.fill: parent

                btn_function: "statistics"
                image_path: "qrc:/image/statistics_tr.png"
            }

        }
        TabButton {
            id:  tab_btn_4

            Comp_Icon_buttom {
                anchors.fill: parent

                btn_function: "account"
                image_path: "qrc:/image/account_tr.png"
            }

        }


//        TabButton {
//            id: tab_btn_4
////            text: "我的"
//            Rectangle {
//                id: page_ctrl_account_rec

//                anchors.fill: parent
////                color: "yellow"
//                Image {
//                    id: image_account
//                    anchors.fill: parent
//                    source: "qrc:/image/mark_transparent.png"
//                }
//            }

//            MouseArea {
////                propagateComposedEvents: true
//                anchors.fill: parent
//                onClicked: {
//                    console.log("x="+mouseX+" y="+mouseY)
//                    swipe_view.currentIndex = 3
//                }
//            }
//        }
    }
}

