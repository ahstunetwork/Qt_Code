import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import Tool_InterAction 1.0
import QtQuick.LocalStorage 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import "database.js" as DB



Page {


    FileDialog {
        id: file_dialog_page_2
        title: "select a file"
        nameFilters: ["excel(*.xls *.xlsx *.csv)"]
        folder: shortcuts.desktop

        onAccepted: {

            import_dialog.book_name = "null";
            import_dialog.file_path = fileUrl;

            // 2022/01/20 traditon way
//            tool_interaction.signal_type = "read_excel_to_db"
//            tool_interaction.signal_info = fileUrl
        }

    }

    New_window_test {

        id: new_window_test
        visible: false
    }

    Dialog {
        id: add_new_dialog
        title: "Add New"

        TextField {
            id: text_field_name
            anchors.margins: 20
            placeholderText: "name: "
        }
        TextField {
            id: text_field_date

            anchors.top: text_field_name.bottom
            anchors.margins: 20
            placeholderText: "date: "
        }

        standardButtons: Dialog.Reset | Dialog.Ok |Dialog.Cancel

        onAccepted: {
            var name_ = text_field_name.text
            var date_ = text_field_date.text

            console.log(name_)
            if( name_ == "" || date_ == "" )
            {
                console.log("input error !")
            }
            else
            {
                word_list_list_model.append(
                            {
                                "name": text_field_name.text,
                                "date": text_field_date.text
                            })
                console.log( "create_db_table schedule" );
                DB.create_db_table( name_ );
            }

        }
        onRejected: {
            console.log()
        }
    }

    Dialog {
        id: delete_dialog
        title: "Delete"
        Text {
            id: tip_text
            anchors.margins: 20
            text: "输入单词本名称(永久删除):"
        }
        TextField {
            id: delete_dialog_name_inputField
            anchors.top: tip_text.bottom
            anchors.margins: 20
        }
        standardButtons: Dialog.Reset | Dialog.Ok |Dialog.Cancel
        onAccepted: {
            var i;
            var del_name = delete_dialog_name_inputField.text;
            for( i = 0; i < word_list_list_model.count; i++ )
            {
                var elem = word_list_list_model.get(i).name
//                console.log(elem)
                if( elem == delete_dialog_name_inputField.text )
                {
                    word_list_list_model.remove(i)
                }
            }
            console.log( "delete_db_table schedule" );
            DB.delete_db_table( del_name  )
            delete_dialog_name_inputField.text = "";

        }

    }

    Dialog {
        id: import_dialog
        title: "Import"

        property var book_name: "null"
        property var file_path: "null"
//        Component.onCompleted: {
//            for( var i = 0; i < word_list_list_model.count; i++ )
//            {
//                var book_name_arr = [];
//                book_name_arr.push( word_list_list_model.get(i).name )
//                console.log( "debug: " +  word_list_list_model.get(i).name)
//            }
//        }

        ComboBox {
            id: select_book_name_to_import
            currentIndex: 0
            textRole: "name"
            font.family: "Source Code Pro"
            font.pixelSize: Qt.application.font.pixel
//            flat: true
            anchors.margins: 20

            model: word_list_list_model
            onCurrentIndexChanged: {
            }
        }


        Button {
            id: select_file_btn_to_import
            anchors.top: select_book_name_to_import.bottom
            text: "select a file"
            anchors.margins: 20
            onClicked: {
                file_dialog_page_2.open()
            }
        }

        standardButtons: Dialog.Reset | Dialog.Ok |Dialog.Cancel
        onAccepted: {
            book_name = select_book_name_to_import.currentText
            console.log( "book_name: " + book_name + "\nfile_path: " + file_path);
            tool_interaction.signal_type = book_name;
            tool_interaction.signal_info = file_path;
        }

    }




    Image {
        id: page_word_background
        source: "qrc:/image/pic_4_phone.jpg"
        anchors.fill: parent
    }





    Rectangle {
        width: parent.width
        height: parent.height / 10

        anchors.top: parent.top
        color: "transparent"
        opacity: 1


        Rectangle {
            id: page_word_list_Title_rec
            width: parent.width*3/5
            height: parent.height
            anchors.left: parent.left
            color: "transparent"

            Label {
                width: parent.width
                height: parent.height
                anchors.fill: parent

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: "Word List"
                font.family: "Source Code Pro"
                font.pixelSize: Qt.application.font.pixel*3
            }

        }


        Rectangle {
            id: page_word_list_ComboBox_rec
            width: parent.width*2/5
            height: parent.height
            anchors.right: parent.right
            color: "transparent"

            ComboBox {
                id: page_word_list_ComboBox

                width: parent.width
                height: parent.height
                currentIndex: 0
                textRole: "text"
                font.family: "Source Code Pro"
                font.pixelSize: Qt.application.font.pixel*2
                flat: true

                model: ListModel {
                    id: page_word_list_ComboBox_listModel
                    ListElement { text: "Show List" ; color: "yellow" }
                    ListElement { text: "Add New"  ; color: "red" }

                    ListElement { text: "Delete"  ; color: "red" }
                    ListElement { text: "Import"; color: "brown" }
                }
                onCurrentIndexChanged: {

                    // debug
                    console.debug( page_word_list_ComboBox_listModel.get(currentIndex).text + ","
                                 + page_word_list_ComboBox_listModel.get(currentIndex).color)
                    // resolute corresponding signal
                    if(page_word_list_ComboBox_listModel.get(currentIndex).text == "Add New" )
                    {
                        add_new_dialog.open()
                    }
                    else if(page_word_list_ComboBox_listModel.get(currentIndex).text == "Delete" )
                    {
                        delete_dialog.open()
                    }
                    else if(page_word_list_ComboBox_listModel.get(currentIndex).text == "Import" )
                    {
                        import_dialog.open()
                    }

                    // reset combox current_index
                    currentIndex = 0
                }
            }
        }



    }

    Dialog {

    }


    Rectangle {

        id: page_word_list_main_rec

        width: parent.width
        height: parent.height * 9 / 10
        color: "transparent"
        anchors.bottom: parent.bottom

        ScrollView {
            anchors.fill: parent
            contentWidth: parent.width
            contentHeight: parent.height

            ListView {
                id: word_list_listview
                width: parent.width

                model: ListModel {


                    // when component load completed, then
                    // trigger this function to append some json object to
                    // this list_view model
                    Component.onCompleted: {
                        console.log("word_list_listView completed")

                        var db_table_name_list = DB.load_db_table_as_word_list();
//                        console.log( DB.load_db_table_as_word_list() )
                        for( var i = 0; i < db_table_name_list.length; i++ )
                        {
                            console.log( " component.oncompleted " + db_table_name_list[i] )
                            if( db_table_name_list[i] === "para_info" || db_table_name_list[i]==="extra_info" )
                            {
                            }
                            else
                            {
                                word_list_list_model.append(
                                            {
                                                "name": db_table_name_list[i],
                                                "date": Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss.zzz ddd"),
                                                "number" : "undefined"
                                            })

                            }
                        }


                    }



                    id: word_list_list_model

//                    ListElement {
//                        name:"考研单词本"
//                        date:"2022/01/18"
//                        number:"5500"
//                    }
//                    ListElement {
//                        name:"四级单词本"
//                        date:"2022/01/19"
//                        number:"4500"
//                    }
//                    ListElement {
//                        name:"六级单词本"
//                        date:"2022/01/20"
//                        number:"5500"
//                    }
//                    ListElement {
//                        name:"高考单词本"
//                        date:"2022/01/18"
//                        number:"3500"
//                    }

                }
                delegate: Component {
                    id: word_list_delegate
                    Rectangle {
                        width: word_list_listview.width
                        height: 100
                        color: "transparent"

                        Label{
                            anchors.fill: parent
                            text: name+"\n"+date+" \n"+number
                            font.family: "Source Code Pro"
                            font.pixelSize: Qt.application.font.pixelSize*2
                            color: if( index % 2 == 0)
                                   {
                                       return "#bbffaa"
                                   }else
                                   {
                                       return "#66ccff"
                                   }
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                console.log( "name="+name);
//                                new_window_test.visible = !new_window_test.visible
//                                add_new_dialog.open()
                            }
                        }
                    }
                }
            }
        }
    }
}
