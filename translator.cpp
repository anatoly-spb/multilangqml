#include "translator.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

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
            qDebug() << "" << fileInfo.fileName() << " loaded";
            QString language = fileInfo.baseName().remove(0, file.length() + 1);
            languages_ << language;
            translators_[language] = std::move(translator);
        }
    }
    qDebug() << "Languages " << languages_;
    return !languages_.empty();
}

void Translator::setLanguage(const QString& language)
{
    QCoreApplication::installTranslator(translators_[language].get());
    emit languageChanged();
}
