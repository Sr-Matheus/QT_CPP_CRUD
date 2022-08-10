#ifndef RELATORIOS_H
#define RELATORIOS_H

#include <QDialog>

namespace Ui {
class relatorios;
}

class relatorios : public QDialog
{
    Q_OBJECT

public:
    explicit relatorios(QWidget *parent = nullptr);
    ~relatorios();

private slots:
    void on_btn_voltar_clicked();

private:
    Ui::relatorios *ui;
};

#endif // RELATORIOS_H
