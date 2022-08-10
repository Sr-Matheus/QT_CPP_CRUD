#include "cadastro_usuarios_2.h"
#include "ui_cadastro_usuarios_2.h"

cadastro_usuarios_2::cadastro_usuarios_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastro_usuarios_2)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

cadastro_usuarios_2::~cadastro_usuarios_2()
{
    delete ui;
    banco.fechar_conexao();
}

void cadastro_usuarios_2::on_btn_voltar_clicked()
{
    close();
}

void cadastro_usuarios_2::on_btn_salvar_clicked()
{
    bool teste = true;

    if(verifica_campos_incompletos())
    {
        QMessageBox::warning(this,"Wefix Store","Campos obrigátorios incompletos");
        teste = false;
    }

    if(!verifica_senhas_iguais())
    {
        QMessageBox::warning(this,"Wefix Store","As senhas não são iguais");
        teste = false;
    }

    if(teste)
    {
        salvar_no_banco();
    }


}

bool cadastro_usuarios_2::verifica_campos_incompletos()
{
    QString usuario="", senha1="", senha2="";
    usuario = ui->le_usuario->text();
    senha1 = ui->le_senha->text();
    senha2 = ui->le_senha_2->text();
    bool controle_da_funcao = false;

    if(usuario == "")
    {
        ui->line_1->setStyleSheet("background-color: transparent;border-top: none;border-bottom: 2px solid;border-bottom-color: rgb(231, 76, 60);");
        ui->label_erro->setStyleSheet("color: rgb(231, 76, 60);");
        controle_da_funcao = true;
    }

    if(senha1== "")
    {
        ui->line_2->setStyleSheet("background-color: transparent;border-top: none;border-bottom: 2px solid;border-bottom-color: rgb(231, 76, 60);");
        controle_da_funcao = true;
    }

    if (senha2 == "")
    {
        ui->line_3->setStyleSheet("background-color: transparent;border-top: none;border-bottom: 2px solid;border-bottom-color: rgb(231, 76, 60);");
        controle_da_funcao = true;
    }

    return controle_da_funcao;
}

bool cadastro_usuarios_2::verifica_senhas_iguais()
{
    QString senha, senha1;
    senha = ui->le_senha->text();
    senha1 = ui->le_senha_2->text();
    bool retorno = true;

    if(senha != senha1)
    {
        ui->line_2->setStyleSheet("background-color: transparent;border-top: none;border-bottom: 2px solid;border-bottom-color: rgb(231, 76, 60);");
        ui->line_3->setStyleSheet("background-color: transparent;border-top: none;border-bottom: 2px solid;border-bottom-color: rgb(231, 76, 60);");
        retorno = false;
    }

    return retorno;
}


void cadastro_usuarios_2::salvar_no_banco()
{
    QString nome, senha, acesso;

    nome= ui->le_usuario->text();
    senha = ui->le_senha->text();

    if(ui->comboBox->currentText() == "Administrador")
    {
        acesso = "A";
    }

    else
    {
        acesso = "B";
    }

    if(!banco.aberta_conexao())
    {
        if(!banco.abrir_conexao())
        {
            QMessageBox::critical(this,"Banco de dados","Erro ao abrir banco de dados");
        }
    }

    QSqlQuery query;

    query.prepare("insert into tb_login (username_login,senha_login,acesso_login) values ('"+nome+"','"+senha+"','"+acesso+"')");

    if(query.exec())
    {
        QMessageBox::warning(this,"Sucesso!","Usuário Cadastrado com sucesso");
        close();
    }

    else
    {
        QMessageBox::critical(this,"Erro","Erro ao salvar daodos de Usuário!");
    }
}




void cadastro_usuarios_2::on_btn_cancelar_clicked()
{
    close();
}
