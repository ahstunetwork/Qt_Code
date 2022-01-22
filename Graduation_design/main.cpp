//#include <QGuiApplication>
#include <QtWidgets/QApplication>
#include <QQmlApplicationEngine>
#include <QTextCodec>
#include "Tool_interaction.h"

int main(int argc, char *argv[])
{
//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForLocale(codec);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //qml fileDialog error
    QCoreApplication::setOrganizationName("Some organization");

//    QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.setOfflineStoragePath("/storage/emulated/0/data/");  //设置数据库存储路径
    qmlRegisterType<Tool_InterAction>("Tool_InterAction",1,0,"Tool_InterAction");




    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
