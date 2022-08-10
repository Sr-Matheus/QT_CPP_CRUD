#ifndef PDV_EDITAR_H
#define PDV_EDITAR_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>
#include <QDesktopServices>
#include <QTableWidget>
#include "Conexao.h"

namespace Ui {
class pdv_editar;
}

class pdv_editar : public QDialog
{
    Q_OBJECT

public:
    explicit pdv_editar(QWidget *parent = nullptr);
    ~pdv_editar();
    Conexao banco;

private slots:
    void on_btn_voltar_clicked();

    void on_tw_1_itemSelectionChanged();

    void on_btn_filtrar_clicked();

    void on_btn_gerar_pdf_clicked();

    void on_btn_exibir_vendas_clicked();

private:
    Ui::pdv_editar *ui;
    void set_tw_1_values();
    void set_tw_1_values(QString, QString);
    void set_tw_1_style();
    void set_tw_2_values();
    void set_tw_2_style();
    void remove_tw_values(QTableWidget *tw);
    void impressao();
};

#endif // PDV_EDITAR_H
