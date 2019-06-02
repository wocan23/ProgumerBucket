#include "esutils.h"
#include "httputils.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QMap>
#include <QList>

EsUtils::EsUtils()
{

}

QList<QMap<QString,QString>> EsUtils::query(QString url){
    QString res = HttpUtils::Get(url);
    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(res.toUtf8(),&parseError);
    // 最外层是一个object/数组，这里是object
    QJsonObject obj = document.object();
    QJsonObject hitObj = obj.value("hits").toObject();
    QJsonArray hitArr = hitObj.value("hits").toArray();
    int size = hitArr.size();
    QList<QMap<QString,QString>> *list = new QList<QMap<QString,QString>>;
    for (int i = 0 ; i < size; i ++) {
        QMap<QString,QString>* map = new QMap<QString,QString>;
        QJsonObject obj = hitArr.at(i).toObject();
        QStringList  keys = obj.keys();
        for (int j = 0; j < keys.size(); j++) {
            QString key = keys.at(j);
            QJsonValue v = obj.value(key);          
            if(v.isObject()){
                QStringList sourceKeys = v.toObject().keys();
                for( int k = 0; k < sourceKeys.size(); k ++){
                    QString skey = keys.at(k);
                    QJsonValue sv = obj.value(skey);
                    map->insert(j,JsonValueToString(sv));
                }
            }
            map->insert(j,JsonValueToString(v));
        }
        list->insert(i,*map);
    }
    return *list;

}

QString EsUtils::JsonValueToString(QJsonValue value){
    QString rsvalue;
    if(value.isString()){
        rsvalue = value.toString();

    }
    if(value.isDouble()){
        double svalue = value.toDouble();
        rsvalue = QString::number(svalue);

    }
    if(value.toBool()){
        bool svalue = value.toBool();
        rsvalue = QString::number(svalue);
    }
    return rsvalue;
}
