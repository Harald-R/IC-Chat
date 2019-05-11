#include <QGuiApplication>
#include <QStandardPaths>
#include <QtQml>

#include "Network/clienthandler.h"
#include "Models/groupsmodel.h"
#include "Models/conversationmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // Create data models for QML
    GroupsModel groupsModel;
    ConversationModel conversationModel;

    // Open communication with server
    ClientHandler clientHandler(&groupsModel, &conversationModel);
    clientHandler.connectToServer();

    // TODO: replace with actual credentials once login page exists
    QString  msg = "SRV|login|user_1|password";
    clientHandler.sendMessage(msg);

    // Request groups that the user belongs to
    clientHandler.requestUserGroups();

    // TODO: get actual user id from clientHandler; blocking method?
    // Set user id in model
    conversationModel.setmyUserId("25");

    // Link models to UML
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("groupsModel", &groupsModel);
    engine.rootContext()->setContextProperty("conversationModel", &conversationModel);
    engine.rootContext()->setContextProperty("clientHandler", &clientHandler);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
