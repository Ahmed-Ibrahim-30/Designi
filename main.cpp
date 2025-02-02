#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Utils/Logging.h"
#include "Controller/HomeDesignController.h"
#include "View/QMLResultView.h"

int main(int argc, char *argv[])
{

    // Register the C++ class
    qmlRegisterType<QMLResultView>("com.example", 1, 0, "QMLDrawing");

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;

    HomeDesignController homeDesignController(&engine);

    const QUrl url(u"qrc:/Designi/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
