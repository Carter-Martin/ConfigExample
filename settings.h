#ifndef SETTINGS_H
#define SETTINGS_H
#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>

class Settings : public QObject {
    // Q_PROPERTY should have a NOTIFY, which calls a function when
    // the variable is changed
    Q_OBJECT
        Q_PROPERTY(int height READ getHeight WRITE setHeight);
        Q_PROPERTY(int width READ getWidth WRITE setWidth);

public:
    explicit Settings(QObject *parent = nullptr);

    Q_INVOKABLE int getHeight() { return _height; }
    Q_INVOKABLE int getWidth() { return _width; }
    static Settings *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

public slots:
    void setHeight(int newHeight);
    void setWidth(int newWidth);
private:
    int _height;
    int _width;

    static Settings* ptr;
};

#endif // SETTINGS_H
