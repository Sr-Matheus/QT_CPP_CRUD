#ifndef MSG_SUPORTE_H
#define MSG_SUPORTE_H

#include <QDialog>

namespace Ui {
class msg_suporte;
}

class msg_suporte : public QDialog
{
    Q_OBJECT

public:
    explicit msg_suporte(QWidget *parent = nullptr);
    ~msg_suporte();

private slots:
    void on_btn_fechar_clicked();

private:
    Ui::msg_suporte *ui;
};

#endif // MSG_SUPORTE_H
