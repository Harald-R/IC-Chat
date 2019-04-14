#include <QGuiApplication>
#include <QStandardPaths>
#include <QSqlDatabase>
#include <QSqlError>
#include <QtQml>

#include "dbmanager.h"
#include "contactsmodel.h"
#include "conversationmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<ContactsModel>("SqlDB", 1, 0, "ContactsModel");
    qmlRegisterType<ConversationModel>("SqlDB", 1, 0, "ConversationModel");

    DbManager::connect();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
