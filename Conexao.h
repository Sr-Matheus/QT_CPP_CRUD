#ifndef CONEXAO_H
#define CONEXAO_H
#include <QtSql>

class Conexao
{

public:
     QSqlDatabase banco_de_dados;
     QString local;
     QString banco;
    Conexao()
    {
        local = qApp->applicationDirPath();
        banco = local+"/Base/base.db";
        banco_de_dados = QSqlDatabase::addDatabase("QSQLITE");
    }

    bool abrir_conexao()
    {

        banco_de_dados.setDatabaseName(banco);

        if(!banco_de_dados.open())
        {
          return false;

        } else{
            return true;
        }
    }

    bool aberta_conexao()
    {
        if(banco_de_dados.isOpen())
        {
          return true;

        } else{
            return false;
        }
    }

    void fechar_conexao(){
        banco_de_dados.close();
    }
};
#endif // CONEXAO_H
