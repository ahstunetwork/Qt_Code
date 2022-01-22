import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import Tool_InterAction 1.0
import QtQuick.LocalStorage 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import "database.js" as DB
import QtCharts 2.3

Page {

    Rectangle {
        id: page_3_statistics_btn_rec
        width: parent.width
        height: parent.height/4
        color: "white"


        ButtonGroup {
            id: page_chart_btn_group
        }
        Column {
//            Label { text: "选择图标" }
            RadioButton {
                text: "学习记录折线图"
                ButtonGroup.group: page_chart_btn_group
                onClicked: {
                    line_series_chart.visible = !line_series_chart.visible
                }
            }
            RadioButton {
                text: "学习情况柱状图"
                ButtonGroup.group: page_chart_btn_group
            }
            RadioButton {
                text: "总览图"
                ButtonGroup.group: page_chart_btn_group
            }
        }


    }
    Rectangle {
        id: page_3_statistics_chart_rec
        width: parent.width
        height: parent.height*3/4
        color: "#bbffaa"
        anchors.top: page_3_statistics_btn_rec.bottom


        ChartView {
            title: "line"
            anchors.fill: parent

            LineSeries {
                id: line_series_chart
                visible: false
                name: "lineSeries"
                XYPoint{ x: 0; y: 0}
                XYPoint{ x: 1.1; y: 2.1}
                XYPoint{ x:1.9; y:3.3}
            }

        }






    }



}
