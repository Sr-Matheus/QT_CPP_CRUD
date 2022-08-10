#include "relatorios.h"
#include "ui_relatorios.h"

relatorios::relatorios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::relatorios)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

}

relatorios::~relatorios()
{
    delete ui;
}

void relatorios::on_btn_voltar_clicked()
{
    close();
}
