#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "translator.h"

int main(int argc, char* argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    qRegisterMetaType<Translator*>("Translator*");
    Translator translator;
    app.setApplicationName("multilangqml");
    if (translator.load(app.applicationDirPath(), app.applicationName())) {
        translator.setLanguage(translator.languages().first());
    }
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("globalTranslator", &translator);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
