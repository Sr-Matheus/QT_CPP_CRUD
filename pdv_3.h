#ifndef PDV_3_H
#define PDV_3_H

#include <QDialog>
#include <pdv_2.h>

namespace Ui {
class pdv_3;
}

class pdv_3 : public QDialog
{
    Q_OBJECT

public:
    explicit pdv_3(QWidget *parent = nullptr);
    ~pdv_3();

    static double total;
    static double valor_pago;
    static double total_dinheiro;
    static double total_cheque;
    static double total_cartao_cr;
    static double total_cartao_db;
    static double valor_total_com_desconto;

private slots:
    void on_btn_cancelar_venda_clicked();

    void on_le_dinheiro_returnPressed();

    void on_le_cheque_returnPressed();

    void on_le_cartao_credito_returnPressed();

    void on_le_cartao_debito_returnPressed();

    void on_le_desconto_returnPressed();

    void on_le_desconto_2_returnPressed();

    void on_btn_finalizar_venda_clicked();

private:
    Ui::pdv_3 *ui;
    void set_valor();
    void calculo_total_pago();
    void calculo_desconto_em_real();
    void calculo_desconto_em_porcento();
    void calcula_troco();
    void calcula_troco_com_desconto(double *desc);
    void zerar_variaveis_static();
};

#endif // PDV_3_H
