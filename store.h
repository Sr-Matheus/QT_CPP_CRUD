#ifndef STORE_H
#define STORE_H

#include <QMainWindow>
#include <janela_login.h>
#include <pdv_1.h>
#include <janela_cadastros.h>
#include <janela_suporte.h>
#include <QtSql>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class store; }
QT_END_NAMESPACE

class store : public QMainWindow
{
    Q_OBJECT

public:
    store(QWidget *parent = nullptr);
    ~store();

    static bool logado;
    static QString tipo_acesso,username_logado;
    static int id_login;

    bool verifica_logado();

private slots:
    void on_btn_pdv_clicked();

    void on_btn_info_clicked();

    void on_btn_cadastros_clicked();

    void on_btn_suporte_clicked();

private:
    Ui::store *ui;
    void closeEvent (QCloseEvent *event);
};
#endif // STORE_H
