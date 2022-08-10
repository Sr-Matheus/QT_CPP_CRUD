#include "cadastro_usuarios.h"
#include "ui_cadastro_usuarios.h"
#include "cadastro_usuarios_2.h"
#include "cadastro_usuario_editar.h"
#include "store.h"


cadastro_usuarios::cadastro_usuarios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastro_usuarios)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    if(!banco.aberta_conexao())
    {
        if(!banco.abrir_conexao())
        {
            QMessageBox::critical(this,"Erro","Erro ao abrir banco de dados");
        }
    }

    ui->tw_usuarios->setAlternatingRowColors(true);
    atualiza_usuarios();

}

cadastro_usuarios::~cadastro_usuarios()
{
    delete ui;
}



void cadastro_usuarios::atualiza_usuarios()
{
    QSqlQuery query;
    query.prepare("select * from tb_login where acesso_login != 'S' or 's'");

    if(query.exec())
    {
        int cont = 0;
        ui->tw_usuarios->setColumnCount(3);
       while(query.next())
        {

            ui->tw_usuarios->insertRow(cont);
            ui->tw_usuarios->setItem(cont,0, new QTableWidgetItem(query.value(0).toString()));
            ui->tw_usuarios->setItem(cont,1, new QTableWidgetItem(query.value(1).toString()));


            if(query.value(3)=="A")
            {
                ui->tw_usuarios->setItem(cont,2, new QTableWidgetItem("Administrador"));
            }
            else
            {
                ui->tw_usuarios->setItem(cont,2, new QTableWidgetItem("Usuário"));
            }

            ui->tw_usuarios->setRowHeight(cont,50);
            cont++;
        }
    }

    else
    {
        QMessageBox::information(this,"Ops","Ops, os usuários não puderam ser exibidos");
    }

    ui->tw_usuarios->setColumnWidth(0,100);
    ui->tw_usuarios->setColumnWidth(1,342);
    ui->tw_usuarios->setColumnWidth(2,241);




    QStringList cabecalho={"ID","USUÁRIO","ACESSO"};
    ui->tw_usuarios->setHorizontalHeaderLabels(cabecalho);
    ui->tw_usuarios->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_usuarios->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_usuarios->verticalHeader()->setVisible(false);

}

void cadastro_usuarios::on_btn_voltar_clicked()
{
    close();
}

void cadastro_usuarios::on_btn_excluir_clicked()
{
    int linha = ui->tw_usuarios->currentRow();


        if(linha==-1)
        {
            QMessageBox::warning(this,"Excluir","Selecione um usuário para excluir!");
        }

        else
        {
            QMessageBox msgBox;
                msgBox.setWindowTitle("Excluir");

                msgBox.setWindowIcon(QPixmap(":/Imgs/UI/PNG/icon.png"));
                msgBox.setStyleSheet(".QLabel {color: rgb(255, 255, 255);} .QMessageBox{background-color: rgb(52, 73, 94); color: rgb(255, 255, 255);}.QPushButton{ background-color: rgb(52, 152, 219); border-radius:1px; color: rgb(255, 255, 255); width: 50px; height: 30px;} .QPushButton:hover{background-color: rgb(41, 128, 185);}");
                msgBox.setFont(QFont("Roboto",12));
                
                msgBox.setText(("Deseja excluir usuário?"));
                QAbstractButton *myYesButton = msgBox.addButton(("Sim"), QMessageBox::YesRole);
                QAbstractButton *myNoButton = msgBox.addButton(("Não"), QMessageBox::NoRole);
                
                msgBox.setIcon(QMessageBox::Question);
                msgBox.exec();

                if(msgBox.clickedButton() == myYesButton)
                    {
                            QString nome = ui->tw_usuarios->item(linha,0)->text();

                            if(nome != store::username_logado)
                            {

                                QSqlQuery exclui;
                                exclui.prepare("delete from tb_login where username_login = '"+nome+"'");

                                if(exclui.exec())
                                {
                                    ui->tw_usuarios->removeRow(linha);
                                    QMessageBox::warning(this,"Exclusão","Usuário excluído!");
                                }

                                else
                                {
                                    QMessageBox::warning(this,"Erro", "Erro ao excluir");
                                }
                            }

                            else
                            {
                                QMessageBox::warning(this,"","Não é possível excluir usuário logado!");
                            }
                    }

                    if(msgBox.clickedButton() == myNoButton)
                    {
                        
                    }
        }
        
}

void cadastro_usuarios::on_btn_cadastrar_clicked()
{
    cadastro_usuarios_2 janela;
    this->close();
    janela.exec();
}



void cadastro_usuarios::remover_linhas(QTableWidget *tw)
{
    while(tw->rowCount()>0)
    {
        tw->removeRow(0);
    }
}

