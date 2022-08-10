#ifndef CADASTRO_USUARIOS_2_H
#define CADASTRO_USUARIOS_2_H

#include <QDialog>
#include "Conexao.h"
#include <QMessageBox>


namespace Ui {
class cadastro_usuarios_2;
}

class cadastro_usuarios_2 : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_usuarios_2(QWidget *parent = nullptr);
    ~cadastro_usuarios_2();

private slots:
    void on_btn_voltar_clicked();

    void on_btn_salvar_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::cadastro_usuarios_2 *ui;
    bool verifica_campos_incompletos();
    bool verifica_senhas_iguais();
    void salvar_no_banco();

    Conexao banco;
};

#endif // CADASTRO_USUARIOS_2_H
