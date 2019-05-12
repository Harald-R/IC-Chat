#include <QGuiApplication>
#include <QStandardPaths>
#include <QtQml>

#include "Network/clienthandler.h"
#include "Network/authenticator.h"
#include "Models/groupsmodel.h"
#include "Models/conversationmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // Create data models for QML and authenticator
    GroupsModel groupsModel;
    ConversationModel conversationModel;
    Authenticator authenticator;

    // Open communication with server
    ClientHandler clientHandler(&authenticator, &groupsModel, &conversationModel);
    clientHandler.connectToServer();

    // Link models to UML
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("groupsModel", &groupsModel);
    engine.rootContext()->setContextProperty("conversationModel", &conversationModel);
    engine.rootContext()->setContextProperty("clientHandler", &clientHandler);
    engine.rootContext()->setContextProperty(QStringLiteral("authenticator"), &authenticator);

    engine.load(QUrl(QStringLiteral("qrc:/Resources/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
