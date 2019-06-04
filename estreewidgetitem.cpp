#include "estreewidgetitem.h"
#include <QDebug>
#include "handler.h"
#include "httputils.h"
#include "esindextabwidegt.h"
#include "indexinfodialog.h"
#include "conninfodialog.h"

EsTreeWidgetItem::EsTreeWidgetItem(QTreeWidget *parent) : QTreeWidgetItem(parent)
{
    conn = NULL;
}
EsTreeWidgetItem::EsTreeWidgetItem(QTreeWidgetItem *parent) : QTreeWidgetItem(parent)
{
    conn = NULL;
}

EsTreeWidgetItem::~EsTreeWidgetItem(){
    if (conn != NULL && this->esItemType == CONN){
        delete conn;
    }
}

void EsTreeWidgetItem::doubleClickConn(){
    QString ip = conn->getIp();
    QString port = conn->getPort();
    QString url = "http://"+ip+":"+port+"/_cluster/state";
    HttpUtils * util = HttpUtils::getInstance();
    QString res = util->Get(url);
    conn->parseIndics(res);

    for (int i = 0; i < conn->getIndexSize(); i++) {
        EsTreeWidgetItem *docItem = new EsTreeWidgetItem(this);
        docItem->setText(0,conn->getIndics()[i].getName());
        docItem->setIcon(0,QIcon(":/icon/pic/index.png"));
        docItem->setEsItemType(INDEX);
        docItem->setEsIndex(&conn->getIndics()[i]);
        docItem->setConn(conn);

        QString *aliasNamesPtr = conn->getIndics()[i].getAliasNames();
        if(aliasNamesPtr != NULL){
            int aliasSize = sizeof(aliasNamesPtr)/sizeof (aliasNamesPtr[0]);
            QStringList aliasList;
            for(int j = 0; j < aliasSize; j++){
                aliasList<<aliasNamesPtr[j];
            }
            docItem->setToolTip(0,aliasList.join(","));
            QColor color("green");
            docItem->setTextColor(0,color);
        }
        this->addChild(docItem);
    }
}

void EsTreeWidgetItem::doubleClickIndex(){
    // tab页
    Conn* conn = this->getConn();
    EsIndex* esIndex = this->getEsIndex();
    Handler* hand = Handler::getInstance();
    emit hand->addTabSignal(conn,esIndex,ADD);
}

void EsTreeWidgetItem::showConnInfo(){
    qDebug()<<this->getConn()->getIp();
    ConnInfoDialog * dialog = new ConnInfoDialog;
    dialog->setWindowTitle("连接信息");
    dialog->flushConnInfo(this->conn);
    dialog->exec();
}

void EsTreeWidgetItem::showIndexInfo(){
    qDebug()<<this->getEsIndex()->getMappings();
    IndexInfoDialog * dialog = new IndexInfoDialog;
    dialog->setWindowTitle("索引信息");
    dialog->flushIndexInfo(this->getEsIndex());
    dialog->exec();
}

Conn* EsTreeWidgetItem::getConn(){
    return this->conn;
}

void EsTreeWidgetItem::setConn(Conn *conn){
    this->conn = conn;
}

bool EsTreeWidgetItem::isOpen(){
    return this->open;
}

void EsTreeWidgetItem::setOpen(bool open){
    this->open = open;
}

ESItemType EsTreeWidgetItem::getEsItemType(){
    return this->esItemType;
}

void EsTreeWidgetItem::setEsItemType(ESItemType itemType){
    this->esItemType = itemType;
}

void EsTreeWidgetItem::setEsIndex(EsIndex *esIndex){
    this->esIndex = esIndex;
}

EsIndex* EsTreeWidgetItem::getEsIndex(){
    return this->esIndex;
}

