#ifndef JANELA_CADASTROS_H
#define JANELA_CADASTROS_H

#include <QDialog>

namespace Ui {
class Janela_cadastros;
}

class Janela_cadastros : public QDialog
{
    Q_OBJECT

public:
    explicit Janela_cadastros(QWidget *parent = nullptr);
    ~Janela_cadastros();

private slots:
    void on_btn_voltar_clicked();

    void on_btn_produtos_clicked();

    void on_btn_clientes_clicked();

private:
    Ui::Janela_cadastros *ui;
};

#endif // JANELA_CADASTROS_H
