#include "janela_suporte.h"
#include "ui_janela_suporte.h"
#include "msg_suporte.h"
#include <QDesktopServices>
#include <QUrl>
#include <QDir>

janela_suporte::janela_suporte(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::janela_suporte)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

janela_suporte::~janela_suporte()
{
    delete ui;
}

void janela_suporte::on_btn_voltar_clicked()
{
    close();
}

void janela_suporte::on_btn_ligar_clicked()
{
    msg_suporte janela;
    janela.exec();
}

void janela_suporte::on_btn_comentario_clicked()
{
    QString link = "https://forms.gle/Pjr8tcqg3JLR1bYY7";
    QDesktopServices::openUrl(QUrl(link));
}

void janela_suporte::on_btn_acesso_clicked()
{

    //QString link1 = "file:///C:/Program Files (x86)/AnyDesk/AnyDesk.exe";
    //QString link2 = "file:///C:/Program Files/AnyDesk/AnyDesk.exe";
    QString nome = QDir::currentPath()+ "/" + "AnyDesk.exe";
    //QDesktopServices::openUrl(QUrl(link1));
    //QDesktopServices::openUrl(QUrl(link2));
    QDesktopServices::openUrl(QUrl::fromLocalFile(nome));
}
