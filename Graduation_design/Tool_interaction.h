#ifndef TOOL_INTERACTION_H
#define TOOL_INTERACTION_H
#include <QDebug>
#include <QString>
#include <Tool_class.h>

class Tool_InterAction : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QString signal_type READ getSignal_type WRITE setSignal_type NOTIFY signal_typeChanged)
    Q_PROPERTY(QString signal_info READ getSignal_info WRITE setSignal_info NOTIFY signal_infoChanged)

    QString signal_type;
    QString signal_info;

    Tool_class tool_class;

    Tool_InterAction()
    {
        qDebug() << "Tool_InterAction construct" << endl;
    }


    // tool_1    distribute signal to function
    // describe: when qml'page send some instructions,this signal will come to this
    // tool_interaction function first,like,trigger setSignal_type & setSignal_info,
    // at the end of setSignal_info function, call the schedule_function to
    // check schedule which function
    bool schedule_function();


    QString getSignal_type() const;
    void setSignal_type(const QString &value);

    QString getSignal_info() const;
    void setSignal_info(const QString &value);

    virtual ~Tool_InterAction() {}


signals:
    void signal_typeChanged();
    void signal_infoChanged();

};


#endif // TOOL_INTERACTION_H
