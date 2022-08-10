#include "janela_cadastros.h"
#include "ui_janela_cadastros.h"
#include "cadastro_produtos_1.h"
#include "cadastro_usuarios.h"

Janela_cadastros::Janela_cadastros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Janela_cadastros)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

Janela_cadastros::~Janela_cadastros()
{
    delete ui;
}

void Janela_cadastros::on_btn_voltar_clicked()
{
    close();
}

void Janela_cadastros::on_btn_produtos_clicked()
{
   cadastro_produtos_1 janela;
   janela.exec();
}

void Janela_cadastros::on_btn_clientes_clicked()
{
    cadastro_usuarios janela;
    janela.exec();
}
