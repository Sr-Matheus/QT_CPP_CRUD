#ifndef CADASTRO_PRODUTOS_1_H
#define CADASTRO_PRODUTOS_1_H

#include <QDialog>
#include <QTableWidget>
#include "Conexao.h"

namespace Ui {
class cadastro_produtos_1;
}

class cadastro_produtos_1 : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_produtos_1(QWidget *parent = nullptr);
    ~cadastro_produtos_1();

    Conexao banco;

    void atualiza_produtos();
    void remover_linhas(QTableWidget *tw);

private slots:
    void on_btn_voltar_clicked();

    void on_btn_cadastrar_clicked();

    void on_btn_excluir_clicked();

    void on_btn_editar_clicked();

    void on_btn_pesquisar_clicked();

    void on_tw_produtos_cellDoubleClicked(int row, int column);

private:
    Ui::cadastro_produtos_1 *ui;



};

#endif // CADASTRO_PRODUTOS_1_H
