#ifndef PDV_1_H
#define PDV_1_H

#include <QDialog>

namespace Ui {
class pdv_1;
}

class pdv_1 : public QDialog
{
    Q_OBJECT

public:
    explicit pdv_1(QWidget *parent = nullptr);
    ~pdv_1();

private slots:
    void on_btn_voltar_clicked();

    void on_btn_pdv_clicked();

    void on_btn_edita_venda_clicked();

    void on_btn_relatorio_clicked();

private:
    Ui::pdv_1 *ui;
};

#endif // PDV_1_H
