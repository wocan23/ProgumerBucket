#ifndef ESINDEX_H
#define ESINDEX_H

#include <QString>
#include <QMap>

class EsIndex
{
private:
    QString name;
    QStringList aliasNames;
    QString settings;
    QMap<QString,QString> mappings;
public:
    EsIndex();

    void setName(QString name);
    void setAliasNames(QStringList aliasNames);
    void setSettings(QString settings);
    void setMappings(QMap<QString,QString> mappings);

    QString getName();
    QStringList getAliasNames();
    QString getSettings();
    QMap<QString,QString> getMappings();
};

#endif // ESINDEX_H
