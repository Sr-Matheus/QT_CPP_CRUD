#include "janela_login.h"
#include "ui_janela_login.h"
#include "store.h"
#include "validar_licenca.h"

janela_login::janela_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::janela_login)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);


    ui->label_2->setFocus();
    if(!banco.aberta_conexao())
    {
        if(!banco.abrir_conexao())
        {
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }


}

janela_login::~janela_login()
{
    delete ui;
}


void janela_login::on_btn_login_clicked()
{
        QString username, password;
        username = ui->le_login->text();
        password = ui->le_senha->text();

        validar_licenca var;
            if(!var.retorno())
            {
                QMessageBox::critical(this,"","Programa não ativado!");
                system("taskkill /im Wefix_Store.exe /f");
            }

        QSqlQuery querry;


        querry.prepare("select * from tb_login where username_login ='"+username+
                       "'and senha_login='"+password+"'");


        if(querry.exec()){
            querry.first();
            if(querry.value(1).toString()!="")
            {
                store::logado = true;
                store::id_login = querry.value(0).toInt();
                store::username_logado = querry.value(1).toString();
                store::tipo_acesso=querry.value(3).toString();
                close();
            }else{
                ui->label_info->setText("USUÁRIO ou SENHA incorretos!");
                ui->le_senha->clear();
                ui->le_login->setFocus();
                }

            }
            banco.fechar_conexao();
}

void janela_login::on_btn_fechar_clicked()
{

        QMessageBox msgBox;
        msgBox.setWindowTitle("Deseja Sair?");

        msgBox.setWindowIcon(QPixmap(":/Imgs/UI/PNG/icon.png"));
        msgBox.setStyleSheet(".QLabel {color: rgb(255, 255, 255);} .QMessageBox{background-color: rgb(52, 73, 94); color: rgb(255, 255, 255);}.QPushButton{ background-color: rgb(52, 152, 219); border-radius:1px; color: rgb(255, 255, 255); width: 50px; height: 30px;} .QPushButton:hover{background-color: rgb(41, 128, 185);}");
        msgBox.setFont(QFont("Roboto",12));

        msgBox.setText(("Deseja Sair?"));
        QAbstractButton *myYesButton = msgBox.addButton(("Sim"), QMessageBox::YesRole);
        QAbstractButton *myNoButton = msgBox.addButton(("Não"), QMessageBox::NoRole);

        msgBox.setIcon(QMessageBox::Question);
        msgBox.exec();

            if(msgBox.clickedButton() == myYesButton)
            {
                close();
                QProcess::execute("taskkill /im Wefix_Store.exe /f");
            }

            if(msgBox.clickedButton() == myNoButton)
            {

            }

}

void janela_login::on_pushButton_clicked()
{

}

void janela_login::on_btn_info_clicked()
{
    QMessageBox::information(this,"Versão",
                             "WEFIX STORE™\nVersão  2020 r0.1.5");
}
