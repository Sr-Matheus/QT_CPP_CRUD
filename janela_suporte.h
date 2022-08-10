#ifndef JANELA_SUPORTE_H
#define JANELA_SUPORTE_H

#include <QDialog>

namespace Ui {
class janela_suporte;
}

class janela_suporte : public QDialog
{
    Q_OBJECT

public:
    explicit janela_suporte(QWidget *parent = nullptr);
    ~janela_suporte();

private slots:
    void on_btn_voltar_clicked();

    void on_btn_ligar_clicked();

    void on_btn_comentario_clicked();

    void on_btn_acesso_clicked();

private:
    Ui::janela_suporte *ui;
};

#endif // JANELA_SUPORTE_H
