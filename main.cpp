#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QXmlStreamReader>
#include <QFile>
#include <iostream>
#include "settings.h"


void ReadFile(int* vals){
    // Note that the file must be in the current working directory
    QFile file("Config.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file" << file.errorString();
        exit(0);
    }
    QXmlStreamReader reader(&file);
    if (reader.readNextStartElement()) {
        if (reader.name().toString() == "Window") {
            while (reader.readNextStartElement()) {
                if (reader.name().toString() == "Height") {
                    int s = std::stoi(reader.readElementText().toStdString());
                    vals[0] = s;
                }
                else if (reader.name().toString() == "Width") {
                    int s = std::stoi(reader.readElementText().toStdString());
                    vals[1] = s;
                }
                else
                    reader.skipCurrentElement();
            }
        }
        else
            reader.raiseError(QObject::tr("Incorrect file"));
    }
}



int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // A singleton can only be instantiated once, so qmlInstance and instance return the
    // same pointer.
    qmlRegisterSingletonType<Settings>("settings", 1, 0, "Settings", &Settings::qmlInstance);

    int* vals = new int[2];
    ReadFile(vals);
    Settings* s = Settings::instance();
    s->setHeight(vals[0]);
    s->setWidth(vals[1]);
    delete []vals;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
