#include "validar_licenca.h"

validar_licenca::validar_licenca()
{
    data_atual = data_atual.currentDate();
    mac_atual = get_mac::get_mac_add();

    if(!banco.aberta_conexao())
    {
        if(!banco.abrir_conexao())
        {

        }
    }
    status = verifica_status();

}

validar_licenca::~validar_licenca()
{
    banco.fechar_conexao();
}


int validar_licenca::verifica_status()
{
    int retorno = 0;
    QSqlQuery query;
    query.prepare("select status_ativo from tb_ativacao");

    if(query.exec())
    {
        query.first();
        retorno = query.value(0).toInt();
    }

    return retorno;
}

bool validar_licenca::verifica_data()
{
    bool retorno = false;

    QSqlQuery query;
    query.prepare("select data_ativo from tb_ativacao");

    if(query.exec())
    {
        query.first();
        data_licenca = QDate::fromString(query.value(0).toString(),"dd/MM/yyyy");
    }

    if(data_atual <= data_licenca)
    {
        retorno = true;
    }

    return retorno;
}

bool validar_licenca::verifica_mac()
{
    bool retorno = false;

    QSqlQuery query;
    query.prepare("select mac_add from tb_ativacao");

    if(query.exec())
    {
        query.first();
        mac_licenca = query.value(0).toString();
    }

    if(mac_licenca == mac_atual)
    {
        retorno = true;
    }
    
    return retorno;
}

bool validar_licenca::retorno()
{
    bool retorno = false;

    if(status == 1)
    {
        if(verifica_data() and verifica_mac())
        {
            retorno = true;
        }

        else
        {
            status = 0;
            retorno=false;
            QSqlQuery query;
            query.exec("update tb_ativacao set status_ativo = 0");
        }
    }

    else
    {
        retorno = false;
    }

    return retorno;
}
