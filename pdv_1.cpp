#include "pdv_1.h"
#include "ui_pdv_1.h"
#include "pdv_2.h"
#include "pdv_editar.h"
#include "store.h"
#include "relatorios.h"

pdv_1::pdv_1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pdv_1)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

pdv_1::~pdv_1()
{
    delete ui;
}

void pdv_1::on_btn_voltar_clicked()
{
    close();
}

void pdv_1::on_btn_pdv_clicked()
{
    pdv_2 janela;
    this->close();
    janela.exec();

}

void pdv_1::on_btn_edita_venda_clicked()
{
    pdv_editar janela;

    if(store::tipo_acesso == "A" or store::tipo_acesso == "a"){
        this->close();
        janela.exec();
    }

    else if(store::tipo_acesso == "S" or store::tipo_acesso == "s")
    {
        this->close();
        janela.exec();
    }

    else{
        QMessageBox::warning(this,"Erro","Acesso não permitido!");
    }

}

void pdv_1::on_btn_relatorio_clicked()
{
    relatorios janela;
    janela.exec();
}
