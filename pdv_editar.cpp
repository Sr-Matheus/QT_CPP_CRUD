 #include "pdv_editar.h"
#include "ui_pdv_editar.h"
#include "store.h"
#include <QDebug>
#include <QPrinter>
#include <QPainter>
#include  <QDir>


pdv_editar::pdv_editar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pdv_editar)
{
    if(store::tipo_acesso == "A" or store::tipo_acesso == "S")
    {
        ui->setupUi(this);
        setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
        ui->tw_1->setAlternatingRowColors(true);
        ui->tw_2->setAlternatingRowColors(true);
    }

    set_tw_1_style();
}

pdv_editar::~pdv_editar()
{
    delete ui;
}

void pdv_editar::on_btn_voltar_clicked()
{
    close();
}

void pdv_editar::set_tw_1_style()
{
    ui->tw_1->horizontalHeader()->setVisible(true);
    ui->tw_1->setColumnCount(8);
    QStringList cabecalho = {"ID","Data","Hora","Colab","Total", "V. Total desc", "V. Pago","PGTO"};
    ui->tw_1->setHorizontalHeaderLabels(cabecalho);
    ui->tw_1->verticalHeader()->setVisible(false);

    ui->tw_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tw_1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_1->setEditTriggers(QAbstractItemView::NoEditTriggers);

    set_tw_1_values();
}

void pdv_editar::set_tw_1_values()
{
    int contlinhas = 0;

    banco.abrir_conexao();
    QSqlQuery query, query2;
    query.prepare("select * from tb_vendas");
    query.exec();
    query.first();

    do
    {
        ui->tw_1->insertRow(contlinhas);
        ui->tw_1->setItem(contlinhas,0, new QTableWidgetItem(query.value(0).toString()));
        ui->tw_1->setItem(contlinhas,1, new QTableWidgetItem(query.value(1).toString()));
        ui->tw_1->setItem(contlinhas,2, new QTableWidgetItem(query.value(2).toString()));
        ui->tw_1->setItem(contlinhas,3, new QTableWidgetItem(query.value(3).toString()));

        double valor_4 = query.value(4).toDouble();
        double valor_5 = query.value(5).toDouble();
        double valor_6 = query.value(6).toDouble();


        ui->tw_1->setItem(contlinhas,4, new QTableWidgetItem(QString::number(valor_4,'f',2)));
        ui->tw_1->setItem(contlinhas,5, new QTableWidgetItem(QString::number(valor_5,'f',2)));
        ui->tw_1->setItem(contlinhas,6, new QTableWidgetItem(QString::number(valor_6,'f',2)));
        ui->tw_1->setItem(contlinhas,7, new QTableWidgetItem(query.value(7).toString()));
    }
    while(query.next());



}

void pdv_editar::set_tw_1_values(QString data_ini, QString data_fim)
{
    ui->tw_1->setRowCount(0);
    banco.abrir_conexao();
    int contlinhas = 0;
    QSqlQuery query, query2;
    query.prepare("select * from tb_vendas where data_venda between '" + data_ini + "'and'" + data_fim + "'");
    query.exec();
    query.first();

    do
    {
        ui->tw_1->insertRow(contlinhas);
        ui->tw_1->setItem(contlinhas,0, new QTableWidgetItem(query.value(0).toString()));
        ui->tw_1->setItem(contlinhas,1, new QTableWidgetItem(query.value(1).toString()));
        ui->tw_1->setItem(contlinhas,2, new QTableWidgetItem(query.value(2).toString()));
        ui->tw_1->setItem(contlinhas,3, new QTableWidgetItem(query.value(3).toString()));
        ui->tw_1->setItem(contlinhas,4, new QTableWidgetItem(query.value(4).toString()));
        ui->tw_1->setItem(contlinhas,5, new QTableWidgetItem(query.value(5).toString()));
        ui->tw_1->setItem(contlinhas,6, new QTableWidgetItem(query.value(6).toString()));
        ui->tw_1->setItem(contlinhas,7, new QTableWidgetItem(query.value(7).toString()));
    }
    while(query.next());

}

void pdv_editar::set_tw_2_style()
{
    ui->tw_2->horizontalHeader()->setVisible(true);
    ui->tw_2->setColumnCount(5);
    QStringList cabecalho = {"ID","Produto","QTDE","V. Un.","V. Total"};
    ui->tw_2->setHorizontalHeaderLabels(cabecalho);
    ui->tw_2->verticalHeader()->setVisible(false);
    ui->tw_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    set_tw_2_values();
}

void pdv_editar::set_tw_2_values()
{
    int contlinhas = 0;

    banco.abrir_conexao();
    QSqlQuery query1;
    query1.prepare("select id_movimentacao,produto,quantidade,valor_unitario,valor_total from tb_produtos_vendas where id_vendas = " + ui->tw_1->item(ui->tw_1->currentRow(),0)->text() + " order by id_movimentacao");
    query1.exec();
    query1.last();

    do
    {
        ui->tw_2->insertRow(contlinhas);
        ui->tw_2->setItem(contlinhas,0, new QTableWidgetItem(query1.value(0).toString()));
        ui->tw_2->setItem(contlinhas,1, new QTableWidgetItem(query1.value(1).toString()));
        ui->tw_2->setItem(contlinhas,2, new QTableWidgetItem(query1.value(2).toString()));
        ui->tw_2->setItem(contlinhas,3, new QTableWidgetItem(query1.value(3).toString()));
        ui->tw_2->setItem(contlinhas,4, new QTableWidgetItem(query1.value(4).toString()));

    }
    while(query1.previous());
}

void pdv_editar::on_tw_1_itemSelectionChanged()
{
    ui->tw_2->clear();
    ui->tw_2->setRowCount(0);
    set_tw_2_style();

}

void pdv_editar::on_btn_filtrar_clicked()
{
    QString data_ini = ui->de_data_1->text();
    QString data_fim = ui->de_data_2->text();

    set_tw_1_values(data_ini,data_fim);
}

void pdv_editar::on_btn_gerar_pdf_clicked()
{
    if(ui->tw_1->currentRow()!= -1)
    {
        impressao();
    }

    else
    {
        QMessageBox::warning(this,"","Selecione um item para gerar PDF");
    }
}

void pdv_editar::impressao()
{
    QString nome = QDir::currentPath()+ "/" +ui->tw_1->item(ui->tw_1->currentRow(),0)->text() + "_vendas.pdf";
    QPrinter printer;



    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QSizeF(72,3200), QPrinter::Millimeter);
    printer.setOutputFileName(nome);

    QPainter painter;

    if(!painter.begin(&printer))
    {
       qDebug()<< "Erro ao abrir PDF";
       return;
    }

    int linha = 300;
    int salto = 25;

    painter.drawPixmap(75,10,QPixmap(":/Imgs/UI/PNG/icon.png"));
    painter.drawText(10,150,"Controle de estoque: N° " + ui->tw_1->item(ui->tw_1->currentRow(),0)->text() );

    painter.drawText(10,200, "ID: "+ ui->tw_1->item(ui->tw_1->currentRow(),0)->text());
    painter.drawText(60,200, "Data: "+ ui->tw_1->item(ui->tw_1->currentRow(),1)->text());
    painter.drawText(165,200, "Hora: "+ ui->tw_1->item(ui->tw_1->currentRow(),2)->text());

    painter.drawText(2,250,"QTD");
    painter.drawText(35,250,"ITEM");
    painter.drawText(185,250,"VALOR * QTD");

    for (int i =0; i < ui->tw_2->rowCount();++i) {
     painter.drawText(2,linha, ui->tw_2->item(i,2)->text());
     painter.drawText(35,linha, ui->tw_2->item(i,1)->text());
     painter.drawText(200,linha, "R$ "+ ui->tw_2->item(i,4)->text());
     linha+=salto;
    }

    linha += salto;
    painter.drawText(2,linha,"------------------------------------------------------------");
    linha += salto;
    painter.drawText(0,linha, "V. Total: R$ "+ui->tw_1->item(ui->tw_1->currentRow(),4)->text());
    painter.drawText(130,linha, "V. c/ Desc.: R$ "+ui->tw_1->item(ui->tw_1->currentRow(),5)->text());

    linha += salto;
    painter.drawText(0,linha, "V. Pago: R$ "+ui->tw_1->item(ui->tw_1->currentRow(),6)->text());

    double calc1, calc2;
    calc1 = ui->tw_1->item(ui->tw_1->currentRow(),5)->text().toDouble();
    calc2 = ui->tw_1->item(ui->tw_1->currentRow(),6)->text().toDouble();

    calc1 = calc2 - calc1;

    painter.drawText(130,linha, "Troco: R$ "+QString::number(calc1,'f',2));

    linha += salto*2;
    painter.drawText(2,linha,"Este documento não vale como cupom fiscal");
    linha += salto*6;
    painter.drawText(2,linha,"------------------------------------------------------------");

    printer.newPage();

    painter.end();

    QDesktopServices::openUrl(QUrl::fromLocalFile(nome));
}

void pdv_editar::on_btn_exibir_vendas_clicked()
{
    remove_tw_values(ui->tw_1);
    set_tw_1_values();
}



void pdv_editar::remove_tw_values(QTableWidget *tw)
{
    while(tw->rowCount()>0)
    {
        tw->removeRow(0);
    }

}
