#ifndef CADASTRO_USUARIOS_H
#define CADASTRO_USUARIOS_H

#include <QDialog>
#include "Conexao.h"
#include <QMessageBox>
#include <QTableWidget>

namespace Ui {
class cadastro_usuarios;
}

class cadastro_usuarios : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_usuarios(QWidget *parent = nullptr);
    ~cadastro_usuarios();

private slots:
    void on_btn_voltar_clicked();

    void on_btn_excluir_clicked();

    void on_btn_cadastrar_clicked();

private:
    Ui::cadastro_usuarios *ui;
    Conexao banco;
    void atualiza_usuarios();
    void remover_linhas(QTableWidget *tw);
};

#endif // CADASTRO_USUARIOS_H
