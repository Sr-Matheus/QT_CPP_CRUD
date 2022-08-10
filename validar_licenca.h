#ifndef VALIDAR_LICENCA_H
#define VALIDAR_LICENCA_H

#include "get_mac_add.h"
#include <QString>
#include <QDateTime>
#include "Conexao.h"
#include <QMessageBox>
#include <QSql>

class validar_licenca
{
public:
	validar_licenca();
	~validar_licenca();
    bool retorno();

private:
	QDate data_atual, data_licenca; QString mac_atual, mac_licenca; int status;
    Conexao banco;

    bool abre_conexao();
    int verifica_status();
	bool verifica_data();
    bool verifica_mac();
	
};

#endif
