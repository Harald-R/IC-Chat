#include <QGuiApplication>
#include <QStandardPaths>
#include <QSqlDatabase>
#include <QSqlError>
#include <QtQml>

#include "clienthandler.h"
#include "groupsmodel.h"

#include "sqlcontactmodel.h"
#include "sqlconversationmodel.h"

static void connectToDatabase()
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        database = QSqlDatabase::addDatabase("QSQLITE");
        if (!database.isValid())
            qFatal("Cannot add database: %s", qPrintable(database.lastError().text()));
    }

    const QDir writeDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!writeDir.mkpath("."))
        qFatal("Failed to create writable directory at %s", qPrintable(writeDir.absolutePath()));

    // Ensure that we have a writable location on all devices.
    const QString fileName = writeDir.absolutePath() + "/chat-database.sqlite3";
    // When using the SQLite driver, open() will create the SQLite database if it doesn't exist.
    database.setDatabaseName(fileName);
    if (!database.open()) {
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
        QFile::remove(fileName);
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    ClientHandler clientHandler;
    clientHandler.connectToServer();

    // TODO: replace with actual credentials once login page exists
    QString msg = "SRV:login:user_1:password";
    clientHandler.sendMessage(msg);

    GroupsModel groupsModel;
    clientHandler.requestUserGroups(&groupsModel);

//    qmlRegisterType<SqlContactModel>("SqlDB", 1, 0, "SqlContactModel");
    qmlRegisterType<SqlConversationModel>("SqlDB", 1, 0, "SqlConversationModel");

    connectToDatabase();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("groupsModel", &groupsModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
