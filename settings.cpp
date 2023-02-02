#include "settings.h"

Settings* Settings::ptr = nullptr;
Settings::Settings(QObject *parent) : QObject(parent)
{
    // Default values
    _height = 200;
    _width = 800;
}

void Settings::setHeight(int newHeight){
    _height = newHeight;
}
void Settings::setWidth(int newWidth){
    _width = newWidth;
}

Settings* Settings::instance(){
    if(ptr == nullptr){
        ptr = new Settings;
    }
    return ptr;
}

QObject* Settings::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return instance();
}
