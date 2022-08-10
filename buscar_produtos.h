#ifndef BUSCAR_PRODUTOS_H
#define BUSCAR_PRODUTOS_H

#include <QDialog>
#include <QMessageBox>
#include <QTableWidget>
#include "pdv_2.h"
#include "Conexao.h"

namespace Ui {
class buscar_produtos;
}

class buscar_produtos : public QDialog
{
    Q_OBJECT

public:
    explicit buscar_produtos(QWidget *parent = nullptr);
    ~buscar_produtos();

private slots:
    void on_btn_voltar_clicked();

    void on_btn_pesquisar_clicked();

    void on_btn_adicionar_item_clicked();

private:
    Ui::buscar_produtos *ui;
    Conexao banco;
    void atualiza_produtos();
    void remover_linhas(QTableWidget *tw);
};

#endif // BUSCAR_PRODUTOS_H
