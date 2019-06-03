#include "createconndialog.h"
#include "ui_createconndialog.h"
#include <QString>
#include "handler.h"
#include "conn.h"

CreateConnDialog::CreateConnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateConnDialog)
{
    ui->setupUi(this);
//    this->ui->ip->setText("localhost");
//    this->ui->connName->setText("localhost");
    this->ui->ip->setText("10.70.93.52");
    this->ui->connName->setText("10.70.93.52");
    this->ui->port->setText("9200");    
    this->ui->ip->setTextMargins(5,0,0,0);
    this->ui->port->setTextMargins(5,0,0,0);
    this->ui->connName->setTextMargins(5,0,0,0);
    this->ui->userName->setTextMargins(5,0,0,0);
    this->ui->password->setTextMargins(5,0,0,0);

    connect(this->ui->btn_submit,SIGNAL(clicked()),this,SLOT(sumbit()));
    connect(this->ui->btn_cancel,SIGNAL(clicked()),this,SLOT(cancel()));
}

CreateConnDialog::~CreateConnDialog()
{
    delete ui;
}

void CreateConnDialog::sumbit(){
    QString connName = this->ui->connName->text();
    QString ip = this->ui->ip->text();
    QString port = this->ui->port->text();
    QString userName = this->ui->userName->text();
    QString pwd = this->ui->password->text();

    if(connName.isEmpty()){
        this->ui->connName->setFocus();
        return;
    }
    if(ip.isEmpty()){
        this->ui->ip->setFocus();
        return;
    }
    Handler * handler = Handler::getInstance();
    if(port.isEmpty() || (!handler->isDigitString(port))){
        this->ui->port->setFocus();
        return;
    }

    // 通知树形菜单添加一条记录
    Conn *conn = new Conn(handler->getUUID(),connName,userName,pwd,ip,port);
    handler->addConn(conn);
    this->close();


}

void CreateConnDialog::cancel(){

}
