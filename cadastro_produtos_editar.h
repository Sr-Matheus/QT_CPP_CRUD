#ifndef CADASTRO_PRODUTOS_EDITAR_H
#define CADASTRO_PRODUTOS_EDITAR_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include "Conexao.h"

namespace Ui {
class cadastro_produtos_editar;
}

class cadastro_produtos_editar : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_produtos_editar(QWidget *parent = nullptr, QString id_produto = "");
    ~cadastro_produtos_editar();
    Conexao banco;

private slots:
    void on_btn_voltar_clicked();

    void on_btn_salvar_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::cadastro_produtos_editar *ui;
    void preenche_dados();
};

#endif // CADASTRO_PRODUTOS_EDITAR_H
