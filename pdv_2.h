#ifndef PDV_2_H
#define PDV_2_H

#include <QDialog>
#include "Conexao.h"
#include "pdv_3.h"
#include "buscar_produtos.h"
#include "pdv_editar.h"
#include "QMessageBox"
#include <QString>
#include <QList>
#include <cstdlib>
#include <cmath>
#include <QTableWidget>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QDir>
#include <QDesktopServices>

namespace Ui {
class pdv_2;
}

class pdv_2 : public QDialog
{
    Q_OBJECT

public:
    explicit pdv_2(QWidget *parent = nullptr);
    ~pdv_2();

    static QString codigo_busca;
    static double get_total;
    static bool finalizado;
    static int id_da_venda;
    Conexao banco;
    int contador_linhas;

    void reseta_campos();
    void set_codigo(QString);
    void set_pointer(pdv_2 &var);

   static QString finaliza_venda();

private slots:
    void on_btn_voltar_clicked();

    void on_btn_finalizar_venda_clicked();

    void on_btn_edita_venda_clicked();

    void on_btn_adicionar_item_clicked();

    void on_btn_remover_item_clicked();

    void on_btn_cancelar_venda_clicked();

    void on_btn_buscar_produtos_clicked();

private:
    Ui::pdv_2 *ui;
    void set_tw_produtos();
    bool verifica_repetido(QTableWidget *tw,QString cod_produto);
    double calcula_total(QTableWidget *tw, int coluna);
    void adiciona_produtos();
    void remove_linhas(QTableWidget *tw);
    void imprimir_venda();
    bool permitir_impressao();

};

#endif // PDV_2_H
