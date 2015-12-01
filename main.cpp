#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    Client *client = new Client();
    context->setContextProperty("client", client);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

