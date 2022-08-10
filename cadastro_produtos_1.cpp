#include "cadastro_produtos_1.h"
#include "ui_cadastro_produtos_1.h"
#include "cadastro_produtos_2.h"
#include "cadastro_produtos_editar.h"

cadastro_produtos_1::cadastro_produtos_1(QWidget *parent) : QDialog(parent), ui(new Ui::cadastro_produtos_1)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui->tw_produtos->setAlternatingRowColors(true);

    if(!banco.abrir_conexao())
    {
        QMessageBox::warning(this,"Erro","Erro ao abrir banco de dados");
    }
    atualiza_produtos();
}

cadastro_produtos_1::~cadastro_produtos_1()
{
    delete ui;
    banco.fechar_conexao();
}

void cadastro_produtos_1::on_btn_voltar_clicked()
{
    close();
}

void cadastro_produtos_1::on_btn_cadastrar_clicked()
{

    cadastro_produtos_2 janela;
    this->close();
    janela.exec();

}

void cadastro_produtos_1::atualiza_produtos()
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


    ui->tw_produtos->setColumnWidth(0,150);
    ui->tw_produtos->setColumnWidth(1,300);
    ui->tw_produtos->setColumnWidth(2,85);
    ui->tw_produtos->setColumnWidth(3,160);


    QStringList cabecalho={"CÓDIGO","PRODUTO","ESTOQUE","VALOR DE VENDA"};
    ui->tw_produtos->setHorizontalHeaderLabels(cabecalho);
    ui->tw_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_produtos->verticalHeader()->setVisible(false);

}

void cadastro_produtos_1::on_btn_excluir_clicked()
{
    int linha = ui->tw_produtos->currentRow();


        if(linha==-1)
        {
            QMessageBox::warning(this,"Excluir","Selecione um produto para excluir!");
        }
        else
        {
            
                QMessageBox msgBox;
                msgBox.setWindowTitle("Excluir");

                msgBox.setWindowIcon(QPixmap(":/Imgs/UI/PNG/icon.png"));
                msgBox.setStyleSheet(".QLabel {color: rgb(255, 255, 255);} .QMessageBox{background-color: rgb(52, 73, 94); color: rgb(255, 255, 255);}.QPushButton{ background-color: rgb(52, 152, 219); border-radius:1px; color: rgb(255, 255, 255); width: 50px; height: 30px;} .QPushButton:hover{background-color: rgb(41, 128, 185);}");
                msgBox.setFont(QFont("Roboto",12));
                
                msgBox.setText(("Deseja excluir produto?"));
                QAbstractButton *myYesButton = msgBox.addButton(("Sim"), QMessageBox::YesRole);
                QAbstractButton *myNoButton = msgBox.addButton(("Não"), QMessageBox::NoRole);
                
                msgBox.setIcon(QMessageBox::Question);
                msgBox.exec();

                    if(msgBox.clickedButton() == myYesButton)
                    {
                            QString id = ui->tw_produtos->item(linha,0)->text();

                            QSqlQuery exclui;
                            exclui.prepare("delete from tb_produtos where id_produto="+id);

                            if(exclui.exec())
                            {
                                ui->tw_produtos->removeRow(linha);
                                QMessageBox::warning(this,"Exclusão","Produto excluído!");
                            }

                            else
                            {
                                QMessageBox::warning(this,"Erro", "Erro ao excluir");
                            }
                    }

                    if(msgBox.clickedButton() == myNoButton)
                    {
                        
                    }


                    }

}

void cadastro_produtos_1::remover_linhas(QTableWidget *tw)
{
    while(tw->rowCount()>0)
    {
        tw->removeRow(0);
    }
}

void cadastro_produtos_1::on_btn_editar_clicked()
{

    QString codigo;
    int linha = ui->tw_produtos->currentRow();

    if(linha==-1){
        QMessageBox::warning(this," ","Só da para editar se tiver um produto selecionado");
    }else{

        codigo = ui->tw_produtos->item(linha,0)->text();
        cadastro_produtos_editar janela(this, codigo);
        janela.exec();
        this->close();
    }

}

void cadastro_produtos_1::on_btn_pesquisar_clicked()
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

void cadastro_produtos_1::on_tw_produtos_cellDoubleClicked(int row, int column)
{
    QString codigo;
    int linha = ui->tw_produtos->currentRow();

    if(linha==-1){
        QMessageBox::warning(this,"","selecione um produto para editar");
    }else{

        codigo = ui->tw_produtos->item(linha,0)->text();
        cadastro_produtos_editar janela(this, codigo);
        janela.exec();
        this->close();
    }
}
