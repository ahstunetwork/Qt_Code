#include "Tool_interaction.h"
#include "Tool_class.h"
#include "Word.h"
//#include <QAxObject>
#include <iomanip>
#include <iostream>
#include <QSqlDatabase>
//#include <QMessageBox>
#include <QSqlQuery>
//#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QString>


QString Tool_class::getSignal_type() const
{
    return signal_type;
}

void Tool_class::setSignal_type(const QString &value)
{
    signal_type = value;
}

void Tool_class::read_excel_to_db( QString db_table_name, QString file_path_qml )
{
    qDebug() << "read_excel_to_db schedule" << endl;
    // convert path from qml's path(file:///C:/) to Qt/C++'s path(C:/)
    QStringList file_path_str = file_path_qml.split("///");
//    qDebug() << "the file_path is: " << file_path_str[1];

    QFile file( file_path_str[1] );
    if( !file.exists() )
    {
        qDebug() << "file not exist !" << endl;
    }


    file.open( QIODevice::ReadOnly | QIODevice::Text );

    QTextStream file_stream( &file );
    file_stream.setAutoDetectUnicode(true);

    QVector<Word> word_vec;
    int index = 0;
    while( !file_stream.atEnd() )
    {
        Word word_temp;
        QString line_str = file_stream.readLine();
        QStringList list_temp = line_str.split(",");
        word_temp.setIndex( index++ );
        word_temp.setWord( list_temp[0]);
        word_temp.setSoundmark(list_temp[1]);
        word_temp.setMeaning( list_temp[2] );
        word_temp.setStudy_count( 0 );
        word_temp.setIs_marked( false );
        word_vec.push_back( word_temp );
    }




    // database operation
    QSqlDatabase db;
    if( QSqlDatabase::contains("qt_sql_default_connection" ))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
//    db = QSqlDatabase::addDatabase("QSQLITE");



    db.setDatabaseName("C:\\storage\\emulated\\0\\data\\Databases\\a88c4f5b498664c0552787c2028b57e5.sqlite");

    db.open();
    if( ! db.isOpen() )
    {
        qDebug() << "database not open";
        return;
    }
    QSqlQuery query;

    // debug
//    query.exec( "INSERT INTO qqq VALUES(1,\"dog\",\"dg\",\"狗\",0,\"0\");" );

    for( int i = 0; i < word_vec.size(); i++ )
    {
        QString sql_str = QString("INSERT INTO %1 VALUES("
                          "%2,\"%3\",\"%4\",\"%5\",%6,\"%7\");")
                .arg( db_table_name )
                .arg(word_vec.at(i).getIndex())
                .arg(word_vec.at(i).getWord())
                .arg(word_vec.at(i).getSoundmark())
                .arg(word_vec.at(i).getMeaning())
                .arg(word_vec.at(i).getStudy_count())
                .arg(word_vec.at(i).getIs_marked());
        qDebug() << sql_str;

        if( query.exec( sql_str ) )
        {
            qDebug() << "Tool_class::read_excel_to_db:No." << i << " sql exec success";

        }
        else {
            qDebug() << "Tool_class::read_excel_to_db:sql exec failure";
        }

    }


    db.close();



    // 2022/01/19
    // change the way of read excel,beacuse QAXobjext
    // can not compile to Android

//    if( file_path_qml.isEmpty() )
//    {
//        qDebug() << "you have not choose any excel file !";
//        return;
//    }

//    QVector<Word> word_vec;

////    file_path_qml = "C:/Code/resource/word_list_test.xlsx";
//    if( file_path_qml.isNull() )
//    {
//        return;
//    }

//    QString filePath = file_path_qml;

//    QAxObject excel("Excel.Application");
//    excel.setProperty("Visible", false);
//    QAxObject *work_books = excel.querySubObject("WorkBooks");
//    work_books->dynamicCall("Open (const QString&)", filePath);
//    QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
//    QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets

//    int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
//    if(sheet_count > 0)
//    {
//        QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);
//        QAxObject *used_range = work_sheet->querySubObject("UsedRange");

//        QAxObject *rows = used_range->querySubObject("Rows");
//        int row_count = rows->property("Count").toInt();  //获取行数
//        QAxObject *cols = used_range->querySubObject("Columns");
//        int col_count = cols->property("Count").toInt();  //获取列数



//        qDebug() << "rows:" << row_count << "  cols: " << col_count;

//        int word_count = 0;
//        for( int i = 1; i < row_count; i++ )
//        {
//            Word word_temp;
//            ++ word_count;

//            int index_ = word_count;
////                int index_ = work_sheet->querySubObject("Cells(int,int)", i, 1)->property("Value").toInt();
//            QString word_ = work_sheet->querySubObject("Cells(int,int)", i, 1)->property("Value").toString();
//            QString soundmark_ = work_sheet->querySubObject("Cells(int,int)", i, 2)->property("Value").toString();
//            QString meaning_ = work_sheet->querySubObject("Cells(int,int)", i, 3)->property("Value").toString();

//            word_temp.setIndex(index_);
//            word_temp.setWord( word_ );
//            word_temp.setSoundmark(soundmark_);
//            word_temp.setMeaning(meaning_);
//            word_temp.setStudy_count( 0 );
//            word_temp.setIs_marked( false );


//            word_vec.push_back( word_temp );
//        }

//        for( int i = 0; i < word_vec.size() ; i++ )
//        {
////            std::cout << "hello world" << endl;
//            qDebug() << "vec[" << i << "]"
//                     << word_vec.at(i).getIndex()
//                     << word_vec.at(i).getWord()
//                     << word_vec.at(i).getSoundmark()
//                     << word_vec.at(i).getMeaning()
//                     << word_vec.at(i).getStudy_count()
//                     << word_vec.at(i).getIs_marked();
//        }
//        work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
//        excel.dynamicCall("Quit(void)");  //退出
//    }


//    create_db_table( "word_list_unorder" );

//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("word_list.sqlite");


//    // check flag to decide create table
////    if(  true  )
////    {
////        create_db_table( "mytable" );
////    }

//    db.open();
//    if( ! db.isOpen() )
//    {
////        QMessageBox msgbox("error","open database error");
//        qDebug() << "database not open";
//        return;
//    }
//    QSqlQuery query;

//    for( int i = 0; i < word_vec.size(); i++ )
//    {
//        QString sql_str = QString("INSERT INTO word_list_unorder VALUES("
//                          "%1,\"%2\",\"%3\",\"%4\",%5,\"%6\")").arg(word_vec.at(i).getIndex())
//                .arg(word_vec.at(i).getWord())
//                .arg(word_vec.at(i).getSoundmark())
//                .arg(word_vec.at(i).getMeaning())
//                .arg(word_vec.at(i).getStudy_count())
//                .arg(word_vec.at(i).getIs_marked());
//        qDebug() << sql_str;

//        if( query.exec( sql_str ) )
//        {
//            qDebug() << "No." << i << " sql exec success";

//        }
//        else {
//            qDebug() << "sql exec failure";
//        }
//    }
//    db.close();

    return;
}

void Tool_class::create_db_table(QString db_table_name)
{
    qDebug() << db_table_name << endl;

    // create table
    // 2022/01/20 now this function is useless
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("word_list.sqlite");
//    db.open();
//    if( ! db.isOpen() )
//    {
////        QMessageBox msgbox("error","open database error");
//        return;
//    }

//    QString sql_str = "CREATE TABLE " +
//                      db_table_name +
//                      "( "
//                      "word_index INT,"
//                      "word VARCHAR,"
//                      "soundmark VARCHAR,"
//                      "meaning VARCHAR,"
//                      "study_count INT,"
//                      "is_marked bool)";

//    QSqlQuery query;
//    qDebug() << sql_str;
//    if( query.exec( sql_str ) )
//    {
//        qDebug() << "create_table success";
//    }
//    else {
//        qDebug() << "create_table failure";
//    }
//    db.close();
}
