#include "store.h"
#include "ui_store.h"
#include <QCloseEvent>

int store::id_login;
bool store::logado;
QString store::tipo_acesso;
QString store::username_logado;

store::store(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::store)
{
    ui->setupUi(this);
    janela_login login;

    login.exec();

}
store::~store()
{
    delete ui;
}

bool store::verifica_logado()
{
    return logado;
}

void store::on_btn_pdv_clicked()
{
    pdv_1 janela;
    janela.exec();
}

void store::on_btn_info_clicked()
{
    QMessageBox::information(this,"Versão","WEFIX STORE™\nVersão  2020 r0.1.5");
}


void store::on_btn_cadastros_clicked()
{
    if(tipo_acesso == "A" or tipo_acesso == "S"){
        Janela_cadastros janela;
        janela.exec();
    }else{
        QMessageBox::warning(this,"Erro","Acesso não permitido!");
    }
}

void store::on_btn_suporte_clicked()
{
    janela_suporte janela;
    janela.exec();
}


void store::closeEvent (QCloseEvent *event)
{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Sair");

        msgBox.setWindowIcon(QPixmap(":/Imgs/UI/PNG/icon.png"));
        msgBox.setStyleSheet(".QLabel {color: rgb(255, 255, 255);} .QMessageBox{background-color: rgb(52, 73, 94); color: rgb(255, 255, 255);}.QPushButton{ background-color: rgb(52, 152, 219); border-radius:1px; color: rgb(255, 255, 255); width: 50px; height: 30px;} .QPushButton:hover{background-color: rgb(41, 128, 185);}");
        msgBox.setFont(QFont("Roboto",12));

        msgBox.setText(("Deseja sair da aplicação?"));
        QAbstractButton *myYesButton = msgBox.addButton(("Sim"), QMessageBox::YesRole);
        QAbstractButton *myNoButton = msgBox.addButton(("Não"), QMessageBox::NoRole);

        msgBox.setIcon(QMessageBox::Question);
        msgBox.exec();

            if(msgBox.clickedButton() == myYesButton)
            {
                event->accept();
                QProcess::execute("taskkill /im Wefix_Store.exe /f");
            }

            if(msgBox.clickedButton() == myNoButton)
            {
                event->ignore();

            }
}

