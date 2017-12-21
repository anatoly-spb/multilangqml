#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QTranslator>
#include <QVariant>

#include <map>
#include <memory>

class Translator : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString language READ language NOTIFY languageChanged)
    Q_PROPERTY(QStringList languages READ languages NOTIFY languagesChanged)

public:
    explicit Translator(QObject* parent = nullptr);

    QString language() const;
    QStringList languages() const;
    bool load(const QString& dir, const QString file);
    Q_INVOKABLE void setLanguage(const QString& language);

signals:
    void languageChanged();
    void languagesChanged();

public slots:

private:
    QString language_;
    QStringList languages_;
    std::map<QString, std::unique_ptr<QTranslator>> translators_;
};

#endif // TRANSLATOR_H
