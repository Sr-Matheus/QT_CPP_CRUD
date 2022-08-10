#ifndef CADASTRO_PRODUTOS_2_H
#define CADASTRO_PRODUTOS_2_H

#include <QDialog>
#include <QMessageBox>
#include "Conexao.h"

namespace Ui {
class cadastro_produtos_2;
}

class cadastro_produtos_2 : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_produtos_2(QWidget *parent = nullptr);
    ~cadastro_produtos_2();
    Conexao banco;

private slots:
    void on_btn_voltar_clicked();


    //void on_text_textChanged();

    void on_btn_cancelar_clicked();

    void on_btn_salvar_clicked();

private:
    Ui::cadastro_produtos_2 *ui;
    bool verifica_produto_cadastrado(QString cod);
};

#endif // CADASTRO_PRODUTOS_2_H
