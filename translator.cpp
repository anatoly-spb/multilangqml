#include "translator.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

#include <algorithm>

Translator::Translator(QObject* parent)
    : QObject(parent)
{
}

QString Translator::language() const
{
    return language_;
}

QStringList Translator::languages() const
{
    return languages_;
}

bool Translator::load(const QString& dir, const QString file)
{
    QDir directory{ dir };
    QStringList filters;
    filters << file + "_*.qm";
    directory.setNameFilters(filters);
    QFileInfoList fileInfoList = directory.entryInfoList(QDir::Files, QDir::Name);
    languages_.clear();
    translators_.clear();
    foreach (QFileInfo fileInfo, fileInfoList) {
        auto translator = std::make_unique<QTranslator>();
        if (translator->load(fileInfo.fileName(), dir)) {
            qDebug().noquote() << fileInfo.fileName() << "loaded";
            QString language = fileInfo.baseName().remove(0, file.length() + 1);
            languages_ << language;
            translators_[language] = std::move(translator);
        } else {
            qDebug().noquote() << "Loading" << fileInfo.fileName() << "failed";
        }
    }
    qDebug() << "Languages " << languages_;
    return !languages_.empty();
}

void Translator::setLanguage(const QString& language)
{
    auto it = translators_.find(language);
    if (it != translators_.end()) {
        std::for_each(translators_.begin(), translators_.end(), [](auto&& e) {
            QCoreApplication::removeTranslator(e.second.get());
        });
        QCoreApplication::installTranslator(it->second.get());
        emit languageChanged();
    }
}
