#include "pdv_2.h"
#include "ui_pdv_2.h"
#include "store.h"
#include "pdv_editar.h"

QString pdv_2::codigo_busca = "";
double pdv_2::get_total = 0.0;
bool pdv_2::finalizado = false;
int pdv_2::id_da_venda = 0;

pdv_2::pdv_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pdv_2)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui->tw_produtos->setAlternatingRowColors(true);

    if(!banco.aberta_conexao())
    {
        if(!banco.abrir_conexao())
        {
            QMessageBox::warning(this,"Erro banco de dados","Erro ao abrir banco de dados");
        }
    }

    set_tw_produtos();
    contador_linhas = 0;

}

pdv_2::~pdv_2()
{
    delete ui;
}

void pdv_2::on_btn_voltar_clicked()
{
    close();
}

void pdv_2::on_btn_finalizar_venda_clicked()
{
    if(contador_linhas > 0)
    {
        pdv_3 janela;
        janela.exec();

        if(finalizado)
        {

           adiciona_produtos();
        }
    }
    else
    {
        QMessageBox::warning(this,"Produtos","É necessário um produto para finalizar a venda!");
    }
}

void pdv_2::on_btn_edita_venda_clicked()
{
    pdv_editar janela;
    janela.exec();
}


void pdv_2::set_tw_produtos()
{
    ui->tw_produtos->setColumnCount(5);
    ui->tw_produtos->setColumnWidth(0,149);
    ui->tw_produtos->setColumnWidth(1,300);
    ui->tw_produtos->setColumnWidth(2,80);
    ui->tw_produtos->setColumnWidth(3,80);
    ui->tw_produtos->setColumnWidth(4,90);

    QStringList cabecalhos = {"CÓDIGO","PRODUTO","VALOR UN.","QTDE","TOTAL"};
    ui->tw_produtos->setHorizontalHeaderLabels(cabecalhos);

    ui->tw_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_produtos->verticalHeader()->setVisible(false);

}


void pdv_2::on_btn_adicionar_item_clicked()
{
    QSqlQuery query;

    QString id_item = ui->le_pesquisar->text();
    double valtot;
    double quantidade;

    query.prepare("select  id_produto, descricao_produto,valor_venda,quantidade_produto from tb_produtos where id_produto="+id_item);

    if(query.exec())
    {
       query.first();

       if(query.value(0).toString()!="")
       {
           ui->tw_produtos->insertRow(contador_linhas);
           ui->tw_produtos->setItem(contador_linhas,0,new QTableWidgetItem(query.value(0).toString()));
           double valor_venda = query.value(2).toDouble();
           ui->tw_produtos->setItem(contador_linhas,1,new QTableWidgetItem(query.value(1).toString()));
           ui->tw_produtos->setItem(contador_linhas,2,new QTableWidgetItem(QString::number(valor_venda,'f',2)));

           QString cod_cod = ui->le_pesquisar->text();

                if(verifica_repetido(ui->tw_produtos,cod_cod))
                {
                    QMessageBox::warning(this,"Produto","Produto já inserido");
                    ui->tw_produtos->removeRow(contador_linhas);
                    reseta_campos();
                }


                else
                {

                        if(ui->le_qtd->text()!="")
                        {
                            /*valtot = ui->le_qtd->text().toDouble() * query.value(2).toDouble();*/
                            QString auxiliar = ui->le_qtd->text();
                            std::replace(auxiliar.begin(),auxiliar.end(),',','.');

                            quantidade = auxiliar.toDouble();
                        }

                        else
                        {
                            /*valtot = query.value(2).toDouble() * 1;
                            ui->tw_produtos->setItem(contador_linhas,3,new QTableWidgetItem("1"));*/
                            quantidade = 1.0;
                        }

                        if(quantidade>query.value(3).toDouble())
                        {
                            QMessageBox::warning(this,"Estoque","Estoque insuficiente");
                            //contador_linhas++;
                            ui->tw_produtos->removeRow(contador_linhas);

                        }

                        else
                        {

                            ui->tw_produtos->setItem(contador_linhas,3,new QTableWidgetItem(QString::number(quantidade)));

                            valtot = query.value(2).toDouble() * quantidade;

                            ui->tw_produtos->setItem(contador_linhas,4,new QTableWidgetItem(QString::number(valtot,'f',2)));
                            ui->tw_produtos->setRowHeight(contador_linhas,50);
                            contador_linhas++;
                            //QString::number(double n, char format = 'g', int precision = 6);
                            ui->lb_total->setText("R$ "+ QString::number(calcula_total(ui->tw_produtos,4),'f',2));
                            get_total = calcula_total(ui->tw_produtos,4);
                            ui->lb_produtos->setText(QString::number(contador_linhas));
                            reseta_campos();
                        }
            }



       }

       else
       {
           QMessageBox::warning(this,"Ops","Poxa não conseguimos encontrar esse produto\n\n                  (︶︹︺) ");
       }



    }else{
        QMessageBox::warning(this,"Ops","Poxa não conseguimos inserir esse produto, tenta de novo!");
        ui->le_qtd->clear();
        ui->le_pesquisar->clear();
        ui->le_pesquisar->setFocus();
    }

}

void pdv_2::on_btn_remover_item_clicked()
{
     int linha = ui->tw_produtos->currentRow();

     if(linha==-1)
     {
         QMessageBox::warning(this,"Excluir","Selecione um produto para excluir!");
     }

     else
     {
          ui->tw_produtos->removeRow(linha);
          ui->lb_total->setText("R$ "+ QString::number(calcula_total(ui->tw_produtos,4),'f',2));
          contador_linhas--;
          ui->lb_produtos->setText(QString::number(contador_linhas));
     }
}


void pdv_2::reseta_campos()
{
    ui->le_pesquisar->clear();
    ui->le_qtd->clear();
    ui->le_pesquisar->setFocus();
}

double pdv_2::calcula_total(QTableWidget *tw, int coluna)
{
    double total = 0.0;
    int total_linhas = tw->rowCount();

        for (int i = 0 ; i < total_linhas; i++)
        {
            total += tw->item(i,coluna)->text().toDouble();
        }

        return total;
}

void pdv_2::on_btn_cancelar_venda_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("WEFIX STORE");

    msgBox.setWindowIcon(QPixmap(":/Imgs/UI/PNG/icon.png"));
    msgBox.setStyleSheet(".QLabel {color: rgb(255, 255, 255);} .QMessageBox{background-color: rgb(52, 73, 94); color: rgb(255, 255, 255);}.QPushButton{ background-color: rgb(52, 152, 219); border-radius:1px; color: rgb(255, 255, 255); width: 50px; height: 30px;} .QPushButton:hover{background-color: rgb(41, 128, 185);}");
    msgBox.setFont(QFont("Roboto",12));
    msgBox.setText(("Têm certeza que deseja cancelar venda?"));
    QAbstractButton *myYesButton = msgBox.addButton(("Sim"), QMessageBox::YesRole);
    QAbstractButton *myNoButton = msgBox.addButton(("Não"), QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.exec();

        if(msgBox.clickedButton() == myYesButton)
        {
            close();
        }

        if(msgBox.clickedButton() == myNoButton)
        {

        }

}

void pdv_2::on_btn_buscar_produtos_clicked()
{
    buscar_produtos janela;
    janela.exec();
    ui->le_pesquisar->setText(codigo_busca);
}


bool pdv_2::verifica_repetido(QTableWidget *tw, QString cod_produto)
{
    int cont = tw->rowCount(), condicao = 0;

    if(cont == -1)
    {
      return false;
    }

    if(cont >= 0)
    {
        for (int i = 0; i<cont ; i++)
        {
            if(tw->item(i,0)->text() == cod_produto)
            {
                condicao++;
            }
        }
    }

    if(condicao >= 2)
    {
        condicao = 0;
        return true;
    }else
    {
        return false;
    }


}

QString pdv_2::finaliza_venda()
{
    QString msg_fim_venda = "";
    double total  = pdv_3::total;
    double total_com_desconto  = pdv_3::valor_total_com_desconto;
    double total_pago = pdv_3::valor_pago;
    int id_venda_2;
    QString data = QDate::currentDate().toString("dd/MM/yyyy");
    QString hora = QTime::currentTime().toString("hh:mm:ss");

    QSqlQuery query;
    query.prepare("insert into tb_vendas (data_venda,hora_venda,id_login,valor_venda, valor_com_desconto, valor_pago, id_tipo_pagamento) values ('"+data+"','"+hora+"','"+QString::number(store::id_login)+"','"+QString::number(total,'f',2)+"','"+QString::number(total_com_desconto,'f',2)+"','"+QString::number(total_pago,'f',2)+"','1')");

    if(!query.exec())
    {
        msg_fim_venda = "Erro ao registrar venda";
    }

    else
    {
        query.prepare("select id_vendas from tb_vendas order by id_vendas desc limit 1");
        query.exec();
        query.first();
        id_venda_2 = query.value(0).toInt();
        msg_fim_venda = "Venda Concluida\n ID Venda: 0"+QString::number(id_venda_2)+"\n Valor Total: R$"+QString::number(total_com_desconto,'f',2);

        id_da_venda = id_venda_2;

    }

    return msg_fim_venda;
}

void pdv_2::adiciona_produtos()
{
    int total_linhas = ui->tw_produtos->rowCount();
    int linha = 0;
    int id_venda;
    QSqlQuery id;

    id.prepare("select id_vendas from tb_vendas order by id_vendas desc limit 1");
    id.exec();
    id.first();
    id_venda = id.value(0).toInt();

    while (linha<total_linhas)
    {
        QString codigo_prod = ui->tw_produtos->item(linha,0)->text();
        QString prod = ui->tw_produtos->item(linha,1)->text();
        QString val_un = ui->tw_produtos->item(linha,2)->text();
        QString qtde = ui->tw_produtos->item(linha,3)->text();
        QString val_tot = ui->tw_produtos->item(linha,4)->text();
        QSqlQuery inserir,estoque;
        double estoque_atual, estoque_modificado;

        inserir.prepare("insert into tb_produtos_vendas (id_vendas,produto,quantidade, valor_unitario, valor_total ) values ('"+QString::number(id_venda)+"','"+prod+"','"+qtde+"','"+val_un+"','"+val_tot+"') ");
        inserir.exec();

        estoque.prepare("select * from tb_produtos where id_produto = '"+codigo_prod+"'");
        estoque.exec();
        estoque.first();
        estoque_atual = estoque.value(3).toDouble();
        estoque_modificado = qtde.toDouble();
        estoque_atual = estoque_atual-estoque_modificado;

        estoque.prepare("update tb_produtos set quantidade_produto = '"+QString::number(estoque_atual)+"' where id_produto = '"+codigo_prod+"'");
        estoque.exec();

        linha++;
    }

    remove_linhas(ui->tw_produtos);

}

void pdv_2::remove_linhas(QTableWidget *tw)
{
    while(tw->rowCount()>0)
    {
        tw->removeRow(0);
    }

    contador_linhas = 0;
    reseta_campos();
    ui->lb_total->setText("R$ "+ QString::number(calcula_total(ui->tw_produtos,4),'f',2));
    ui->lb_produtos->setText(QString::number(contador_linhas));
}

bool pdv_2::permitir_impressao()
{
    bool permitir = false;
    QMessageBox msgBox;
       msgBox.setWindowTitle("Deseja imprimir venda?");

       msgBox.setWindowIcon(QPixmap(":/Imgs/UI/PNG/icon.png"));
       msgBox.setStyleSheet(".QLabel {color: rgb(255, 255, 255);} .QMessageBox{background-color: rgb(52, 73, 94); color: rgb(255, 255, 255);}.QPushButton{ background-color: rgb(52, 152, 219); border-radius:1px; color: rgb(255, 255, 255); width: 50px; height: 30px;} .QPushButton:hover{background-color: rgb(41, 128, 185);}");
       msgBox.setFont(QFont("Roboto",12));

       msgBox.setText(("Deseja imprimir venda?"));
       QAbstractButton *myYesButton = msgBox.addButton(("Sim"), QMessageBox::YesRole);
       QAbstractButton *myNoButton = msgBox.addButton(("Não"), QMessageBox::NoRole);

       msgBox.setIcon(QMessageBox::Question);
       msgBox.exec();

           if(msgBox.clickedButton() == myYesButton)
           {
               permitir = true;
               imprimir_venda();
               qDebug() << "permitir";
           }

           if(msgBox.clickedButton() == myNoButton)
           {
               permitir = false;
           }

    return permitir;
}

void pdv_2::imprimir_venda()
{

    qDebug() << "Entrou na impressao";



    //QString nome = QDir::currentPath()+ "/vendas.pdf";
    QString nome = QCoreApplication::applicationDirPath() + "/vendas.pdf";
    QString url = nome;

    QPrinter printer;
    QDate data_atual = data_atual.currentDate();
    QTime hora_atual = hora_atual.currentTime();


    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QSizeF(72,3200), QPrinter::Millimeter);
    printer.setOutputFileName(nome);

    QPainter painter;

    if(!painter.begin(&printer))
    {
       QMessageBox::critical(this,"","Não conseguimos gerar nada!");
        qDebug()<< "Erro ao abrir PDF";
       return;
    }

    int linha = 300;
    int salto = 25;

    painter.drawPixmap(75,10,QPixmap(":/Imgs/UI/PNG/icon.png"));

    painter.drawText(10,150,"Controle de estoque: N° " + QString::number(id_da_venda));

    painter.drawText(10,200, "ID: "+ QString::number(id_da_venda));
    painter.drawText(60,200, "Data: "+ data_atual.toString("dd/MM/yyyy"));
    painter.drawText(165,200, "Hora: "+ hora_atual.toString());

    painter.drawText(2,250,"QTD");
    painter.drawText(35,250,"ITEM");
    painter.drawText(185,250,"VALOR * QTD");

    for (int i =0; i < ui->tw_produtos->rowCount();++i) {
     painter.drawText(2,linha, ui->tw_produtos->item(i,3)->text());
     painter.drawText(35,linha, ui->tw_produtos->item(i,1)->text());
     painter.drawText(200,linha, "R$ "+ ui->tw_produtos->item(i,4)->text());
     linha+=salto;
    }


    double total_pago = pdv_3::valor_pago;
    linha += salto;
    painter.drawText(0,linha, "V. Total: R$ "+ QString::number(get_total,'f',2));
    painter.drawText(130,linha, "V. c/ Desc.: R$ "+ QString::number(pdv_3::valor_total_com_desconto,'f',2));
    linha += salto;
    painter.drawText(0,linha, "V. Pago: R$ "+ QString::number(total_pago,'f',2));
    painter.drawText(130,linha,"Troco: R$" + QString::number(pdv_3::valor_pago - get_total,'f',2));
    linha += salto*2;
    painter.drawText(2,linha,"Este documento não vale como cupom fiscal");
    linha += salto*6;
    painter.drawText(2,linha,"----------------------------------------------------------------------");

    printer.newPage();

    painter.end();

    QDesktopServices::openUrl(QUrl::fromLocalFile(url));

    qDebug() << "Open Url";
}

