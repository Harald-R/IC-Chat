#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backend.h"
#include "dbmanager.h"
#include "testsuitedb.h"

#include <iostream>

int main(int argc, char *argv[])
{
    //qputenv("QSG_VISUALIZE", "overdraw");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Backend>("io.qt.Backend", 1, 0, "Backend");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) { return -1; }

    TestSuiteDB tests;
    tests.performTests();

    if( tests.passed() )
        DbManager::connect();
    else
        return -1;

    return app.exec();
}
