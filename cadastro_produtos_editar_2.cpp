#include "cadastro_produtos_editar.h"
#include "ui_cadastro_produtos_editar.h"

static QString id;

cadastro_produtos_editar::cadastro_produtos_editar(QWidget *parent, QString id_produto) :
    QDialog(parent),
    ui(new Ui::cadastro_produtos_editar)
{
    ui->setupUi(this);
    id = id_produto;


    if(!banco.abrir_conexao())
    {
        QMessageBox::warning(this,"Erro","Erro ao abrir conexão");
    }

    preenche_dados();

}

cadastro_produtos_editar::~cadastro_produtos_editar()
{
    delete ui;
    banco.fechar_conexao();
}

void cadastro_produtos_editar::on_btn_voltar_clicked()
{
    close();
}

void cadastro_produtos_editar::preenche_dados()
{
    QSqlQuery query;
    query.prepare("select * from tb_produtos where id_produto="+id);

    if(query.exec())
    {
        query.first();
        ui->le_codigo->setText(query.value(0).toString());
        ui->le_descricao->setText(query.value(1).toString());
        ui->le_fornecedor->setText(query.value(2).toString());
        ui->le_estoque->setText(query.value(3).toString());
        ui->le_preco_custo->setText(query.value(4).toString());
        ui->le_preco_venda->setText(query.value(5).toString());
        ui->le_observacao->setText(query.value(6).toString());
    }
    else
    {
        QMessageBox::warning(this,"","Deu não");
    }
}

void cadastro_produtos_editar::on_btn_salvar_clicked()
{
   QString codigo =  ui->le_codigo->text();
   QString descricao =  ui->le_descricao->text();
   QString fornecerdor =  ui->le_fornecedor->text();
   QString estoque =  ui->le_estoque->text();
   QString observacao =  ui->le_observacao->text();
   QString aux;
   QSqlQuery query;

    aux = ui->le_preco_custo->text();
    std::replace(aux.begin(),aux.end(),',','.');
    QString valor_compra = aux;

    aux = ui->le_preco_venda->text();
    std::replace(aux.begin(),aux.end(),',','.');
    QString valor_venda = aux;


   query.prepare ("update tb_produtos set descricao_produto = '"+descricao+"', id_fornecedor = '"+QString::number(fornecerdor.toInt())+"', quantidade_produto = '"+QString::number(estoque.toInt())+"', valor_compra = '"+QString::number(valor_compra.toFloat())+"', valor_venda = '"+QString::number(valor_venda.toFloat())+"', observacao_produto = '"+observacao+"' where id_produto = "+id);


   QMessageBox::StandardButton retorno;
   retorno = QMessageBox::question(this,"Salvar","Deseja salvar alterações nesse produto?", QMessageBox::Yes|QMessageBox::No);

   if(retorno == QMessageBox::Yes)
   {

        if(!query.exec())
        {
            QMessageBox::warning(this,"","Erro ao editar produto!");
            close();
        }

        else
        {
            QMessageBox::information(this,"","Produto salvo com sucesso!");
            close();
        }
   }

   if(retorno == QMessageBox::No)
    {
        close();
    }


}

void cadastro_produtos_editar::on_btn_cancelar_clicked()
{
    QMessageBox::StandardButton retorno;
    retorno = QMessageBox::question(this,"Salvar","Deseja cancelar alterações nesse produto?", QMessageBox::Yes|QMessageBox::No);


    if(retorno == QMessageBox::Yes)
    {
        close();
    }
}
