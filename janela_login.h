#ifndef JANELA_LOGIN_H
#define JANELA_LOGIN_H

#include <QDialog>
#include "Conexao.h"
#include <QMessageBox>

namespace Ui {
class janela_login;
}

class janela_login : public QDialog
{
    Q_OBJECT

public:
    explicit janela_login(QWidget *parent = nullptr);
    ~janela_login();
    Conexao banco;
    int id;
    QString acess = "B";

private slots:
    void on_btn_login_clicked();

    void on_btn_fechar_clicked();

    void on_pushButton_clicked();

    //void set_logado();

    void on_btn_info_clicked();

private:
    Ui::janela_login *ui;
    bool logado = false;

};


#endif // JANELA_LOGIN_H
