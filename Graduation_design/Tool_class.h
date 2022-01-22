#ifndef TOOL_CLASS_H
#define TOOL_CLASS_H

#include <QString>
#include <QVector>
#include <QDebug>

class Tool_class
{
public:
    Tool_class()
    {
        qDebug() << "Tool_class construct" << endl;
    }
    QString signal_type;
    QVector<QString> db_name;

    QString getSignal_type() const;
    void setSignal_type(const QString &value);


    void read_excel_to_db( QString db_table_name, QString file_path );
    void create_db_table( QString table_name );

};




#endif // TOOL_CLASS_H
