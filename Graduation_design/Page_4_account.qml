import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import Tool_InterAction 1.0
import QtQuick.LocalStorage 2.12
import QtQuick.Controls.Material 2.12
import "database.js" as DB


Page {


    Dialog {
        id: switch_operate_db_dialog
        title: "Switch"
        property var page_4_book_name: "null"

        ComboBox {
            id: select_book_name_to_switch
            currentIndex: 0
            textRole: "name"
            font.family: "Source Code Pro"
            font.pixelSize: Qt.application.font.pixel
//            flat: true
            anchors.margins: 20

            model: page_4_word_list_list_model
            onCurrentIndexChanged: {
            }
        }


        ListModel {
            id: page_4_word_list_list_model
            Component.onCompleted: {
                var db_table_name_list = DB.load_db_table_as_word_list();
                for( var i = 0; i < db_table_name_list.length; i++ )
                {
                    console.log( " component.oncompleted " + db_table_name_list[i] )
                    if( db_table_name_list[i] === "para_info" || db_table_name_list[i] ==="extra_info" )
                    {
                    }
                    else
                    {
                        page_4_word_list_list_model.append(
                                    {
                                        "name": db_table_name_list[i],
                                        "date": Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss.zzz ddd"),
                                        "number" : "undefined"
                                    })

                    }
                }
            }
        }

        standardButtons: Dialog.Reset | Dialog.Ok |Dialog.Cancel
        onAccepted: {
            page_4_book_name = select_book_name_to_switch.currentText

            console.log(DB.get_operate_db_table_name());
            DB.set_operate_db_table_name( page_4_book_name )
        }

    }




    Rectangle {
        id: page_account_show_user_info_rec
        width: parent.width
        height: parent.height / 3
        anchors.top: parent.top
        color: "#bbffaa"


        Image {
            id: page_account_show_user_info
            source: "qrc:/image/pic_3_pc.jpg"
            anchors.fill: parent
        }
    }

    Rectangle {

        id: page_account_setting_rec
        width: parent.width
        height: parent.height*2 / 3
        anchors.top: page_account_show_user_info_rec.bottom
        color: "yellow"


        // switch the word_list
        Button {
            id: switch_word_list_btn
            text: "switch"
            width: parent.width
            height: parent.height / 7
            anchors.top: parent.top
            onClicked: {
//                var file_path = file_dialog.open()
                switch_operate_db_dialog.open()

            }
        }
        Button {
            id: setting_btn
            text: "setting"
            width: parent.width
            height: parent.height / 7
            anchors.top: switch_word_list_btn.bottom
        }
        Button {
            id: about_software_btn
            text: "about"
            width: parent.width
            height: parent.height / 7
            anchors.top: setting_btn.bottom

            onClicked: {
                about_dlg.open();
            }

            Dialog {
                id: about_dlg
                title: "about"
                Text {
                    text: "time: 2022/1/14/21:25\n"+
                      "tech stack:\n" +
                      "C++/Qt\n"+
                      "JavaScript & Qml\n"+
                      "sql"
                    font.pixelSize: Qt.application.font.pixelSize*1.5;
                    font.family: "Source Code Pro"
                }

            }


        }
        Button {
            id: exit_proc_btn
            text: "exit"
            width: parent.width
            height: parent.height / 7
            anchors.top: about_software_btn.bottom

            onClicked: {
                Qt.quit();
            }

        }
    }
}
