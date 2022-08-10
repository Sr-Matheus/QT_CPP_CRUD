#ifndef CADASTRO_USUARIO_EDITAR_H
#define CADASTRO_USUARIO_EDITAR_H

#include <QDialog>
#include <QMessageBox>
#include "Conexao.h"

namespace Ui {
class cadastro_usuario_editar;
}

class cadastro_usuario_editar : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_usuario_editar(QWidget *parent = nullptr, QString usuario = "");
    ~cadastro_usuario_editar();

private:
    Ui::cadastro_usuario_editar *ui;
    void preenche_dados();
    Conexao banco;
};

#endif // CADASTRO_USUARIO_EDITAR_H
