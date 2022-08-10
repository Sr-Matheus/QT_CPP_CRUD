#include "msg_suporte.h"
#include "ui_msg_suporte.h"

msg_suporte::msg_suporte(QWidget *parent) :
    QDialog(parent),

ui(new Ui::msg_suporte)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

msg_suporte::~msg_suporte()
{
    delete ui;
}

void msg_suporte::on_btn_fechar_clicked()
{
    close();
}
