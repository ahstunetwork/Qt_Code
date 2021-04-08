#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAxObject>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QString filePath = "E:\\test.xlsx";
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    work_books->dynamicCall("Open (const QString&)", filePath);
    QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
    QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets

    int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
    if(sheet_count > 0)
    {

        QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);
        QAxObject *used_range = work_sheet->querySubObject("UsedRange");
        QAxObject *rows = used_range->querySubObject("Rows");
        int row_count = rows->property("Count").toInt();  //获取行数

        QString txt = work_sheet->querySubObject("Cells(int,int)", 1, 1)->property("Value").toString(); //获取单元格内容
        qDebug() << "Row_count is : " << row_count;
        qDebug() << "The info is  : " << txt;


        work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
        excel.dynamicCall("Quit(void)");  //退出
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
