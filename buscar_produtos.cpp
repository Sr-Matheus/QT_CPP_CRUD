#include "buscar_produtos.h"
#include "ui_buscar_produtos.h"


buscar_produtos::buscar_produtos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buscar_produtos)
{
    ui->setupUi(this);
    ui->tw_produtos->setAlternatingRowColors(true);

    if(!banco.aberta_conexao())
    {
        if(!banco.abrir_conexao())
        {
            QMessageBox::warning(this,"Erro banco de dados","Erro ao abrir banco de dados");
        }
    }

    atualiza_produtos();
}

buscar_produtos::~buscar_produtos()
{
    delete ui;

}

void buscar_produtos::on_btn_voltar_clicked()
{
    pdv_2::codigo_busca = "";
    close();
}


void buscar_produtos::atualiza_produtos()
{

    QSqlQuery query;
    query.prepare("select * from tb_produtos order by descricao_produto");

    if(query.exec())
    {
        int cont = 0;
        ui->tw_produtos->setColumnCount(4);
       while(query.next())
        {
            double valor_em_real;
            ui->tw_produtos->insertRow(cont);
            ui->tw_produtos->setItem(cont,0, new QTableWidgetItem(query.value(0).toString()));
            ui->tw_produtos->setItem(cont,1, new QTableWidgetItem(query.value(1).toString()));
            ui->tw_produtos->setItem(cont,2, new QTableWidgetItem(query.value(3).toString()));
            //ui->tw_produtos->setItem(cont,3, new QTableWidgetItem("R$ "+query.value(5).toString())); - Dessa forma o valor não fica formatado com duas casas!
            valor_em_real = query.value(5).toDouble();

            ui->tw_produtos->setItem(cont,3, new QTableWidgetItem("R$ "+ QString::number(valor_em_real,'f',2)));
            ui->tw_produtos->setRowHeight(cont,50);
            cont++;
        }
    }
    else
    {
        QMessageBox::information(this,"Ops","Ops, os produtos não puderam ser exibidos");
    }


    ui->tw_produtos->setColumnWidth(0,135);
    ui->tw_produtos->setColumnWidth(1,300);
    ui->tw_produtos->setColumnWidth(2,70);
    ui->tw_produtos->setColumnWidth(3,110);


    QStringList cabecalho={"CÓDIGO","PRODUTO","ESTOQUE","VALOR DE VENDA"};
    ui->tw_produtos->setHorizontalHeaderLabels(cabecalho);
    ui->tw_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_produtos->verticalHeader()->setVisible(false);

}

void buscar_produtos::on_btn_pesquisar_clicked()
{
    QString pesquisa;
    pesquisa = ui->le_pesquisar->text();

    QSqlQuery query_pesquisa;

    remover_linhas(ui->tw_produtos);

    query_pesquisa.prepare("select * from tb_produtos  where id_produto = '"+pesquisa+"' or descricao_produto like '%"+pesquisa+"%'");

    if(query_pesquisa.exec())
    {
        int cont = 0;
        ui->tw_produtos->setColumnCount(4);

        while(query_pesquisa.next())
        {
            ui->tw_produtos->insertRow(cont);
            ui->tw_produtos->setItem(cont,0, new QTableWidgetItem(query_pesquisa.value(0).toString()));
            ui->tw_produtos->setItem(cont,1, new QTableWidgetItem(query_pesquisa.value(1).toString()));
            ui->tw_produtos->setItem(cont,2, new QTableWidgetItem(query_pesquisa.value(3).toString()));
            ui->tw_produtos->setItem(cont,3, new QTableWidgetItem("R$ "+query_pesquisa.value(5).toString()));
            ui->tw_produtos->setRowHeight(cont,50);
            cont++;
        }
       ui->le_pesquisar->clear();
       ui->le_pesquisar->setFocus();
    }

    else
    {
         QMessageBox::information(this,"Ops","Ops, produtos não encontrado");
    }

}


void buscar_produtos::remover_linhas(QTableWidget *tw)
{
    while(tw->rowCount()>0)
    {
        tw->removeRow(0);
    }
}

void buscar_produtos::on_btn_adicionar_item_clicked()
{
    int linha = ui->tw_produtos->currentRow();
    QString codigo;

    if(linha==-1){
        QMessageBox::warning(this," ","Só da para editar se tiver um produto selecionado");
    }else{
        codigo = ui->tw_produtos->item(linha,0)->text();
        pdv_2::codigo_busca = codigo;
        this->close();
    }

}
