import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import Tool_InterAction 1.0
import QtQuick.LocalStorage 2.12
import QtQuick.Controls.Material 2.12
import "database.js" as DB


Page {

    Component.onCompleted: {

        console.log( DB.getindex() )
        console.log( DB.readData_by_index( DB.get_current_DB_index() ) )

        page_word_main_show_word.text = DB.readData_by_index( DB.get_current_DB_index() )[1]

        page_word_main_show_word_info.text =
            "\nINDEX: " + DB.readData_by_index( DB.get_current_DB_index() )[0] +
            "\nWORD: " + DB.readData_by_index( DB.get_current_DB_index() )[1] +
            "\nSOUNDMARK: " +DB.readData_by_index(DB.get_current_DB_index())[2]+
            "\nMEANING: "+DB.readData_by_index( DB.get_current_DB_index())[3]
    }


    Image {
        id: page_word_background
        source: "qrc:/image/pic_5_phone.jpg"
        anchors.fill: parent
    }


    Rectangle {
        id: page_word_rec_main
        width: parent.width
        height: parent.height * 9 / 10
        color: "transparent"





        Rectangle {

            id: page_word_main_show_word_rec
            color: "transparent"
            width: parent.width
            height: parent.height * 3 / 15

//            Image {
//                id: page_word_main_show_word_background
//                source: "qrc:/image/pic_1.jpg"
//                anchors.fill: parent
//            }

            Text {
                id: page_word_main_show_word
                anchors.fill: parent

                text: DB.readData_by_index( 100 )[1]


                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font.family: "Source Code Pro"
                font.pixelSize: Qt.application.font.pixelSize * 3


            }
        }





        Rectangle {
            id: page_word_main_show_word_info_rec
            color: "transparent"
//            Image {
//                id: page_word_main_show_word_info_background
//                source: "qrc:/image/tager_background.jpg"
//                anchors.fill: parent

//            }

            width: parent.width
            height: parent.height * 12 / 15

            anchors.bottom:  page_word_rec_main.bottom

            Text {

                id: page_word_main_show_word_info
                anchors.fill: parent

                wrapMode: Text.WordWrap
                text: "null"
                font.family: "Source Code Pro"
                font.pixelSize: Qt.application.font.pixelSize * 2
                opacity: 0

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("MouseArea Trigger,"+
                                    "X: " + mouseX +
                                    "Y: " + mouseY);
                        page_word_main_show_word_info.opacity = !page_word_main_show_word_info.opacity
                    }
                }


            }

        }
    }




    Rectangle {
        id: page_word_rec_ctrl_btn
        anchors.top: page_word_rec_main.bottom
        width: parent.width
        height: parent.height / 10

        color: "transparent"

        Rectangle {
            width: parent.width/4
            height: parent.height

            anchors.left: parent.left
            id: page_word_btn_prior_rec
            color: "transparent"

            Comp_Icon_buttom {
                anchors.fill: parent
                id: page_word_btn_prior
//                text: "上一个"
                btn_function: "word_prior"
                image_path: "qrc:/image/left_tr.png"

            }

        }

        Rectangle {
            width: parent.width/4
            height: parent.height
            id: page_word_btn_mark_rec
            color: "transparent"

            anchors.left: page_word_btn_prior_rec.right

            Comp_Icon_buttom {

                id: page_word_btn_mark
                anchors.fill: parent
//                text: "标记"
                image_path: "qrc:/image/mark_tr.png"

            }

        }

        Rectangle {

            width: parent.width/4
            height: parent.height
            id: page_word_btn_kill_rec
            color: "transparent"

            anchors.left: page_word_btn_mark_rec.right
            Comp_Icon_buttom {
                id: page_word_btn_kill
                anchors.fill: parent
                image_path: "qrc:/image/success_tr.png"
//                text: "秒杀"
            }
        }


        Rectangle {
            width: parent.width/4
            height: parent.height
            id: page_word_btn_next_rec
            anchors.left: page_word_btn_kill_rec.right
            color: "transparent"

            Comp_Icon_buttom {

                id: page_word_btn_next
                anchors.fill: parent
//                text: "下一个"

                btn_function: "word_next"
                image_path: "qrc:/image/right_tr.png"


            }
        }
    }
}



