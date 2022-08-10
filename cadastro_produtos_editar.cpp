#include "cadastro_produtos_editar.h"
#include "ui_cadastro_produtos_editar.h"

static QString id;

cadastro_produtos_editar::cadastro_produtos_editar(QWidget *parent, QString id_produto) :
    QDialog(parent),
    ui(new Ui::cadastro_produtos_editar)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
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
        //ui->le_fornecedor->setText(query.value(2).toString()); - FORNECEDOR DESABILITADO;
        ui->le_estoque->setText(query.value(3).toString());
        ui->le_preco_custo->setText(query.value(4).toString());
        ui->le_preco_venda->setText(query.value(5).toString());
        ui->le_observacao->setText(query.value(6).toString());
        QString unidade = query.value(7).toString();

        if(unidade == "UN")
        {
            ui->comboBox->setCurrentIndex(0);
        }
        else
        {
            ui->comboBox->setCurrentIndex(1);
        }
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
   //QString fornecerdor =  ui->le_fornecedor->text();
   QString observacao =  ui->le_observacao->text();
   QString aux;
   QString estoque;
   QSqlQuery query;

    aux = ui->le_preco_custo->text();
    std::replace(aux.begin(),aux.end(),',','.');
    QString valor_compra = aux;

    aux = ui->le_preco_venda->text();
    std::replace(aux.begin(),aux.end(),',','.');
    QString valor_venda = aux;

    aux = ui->le_estoque->text();
    std::replace(aux.begin(),aux.end(),',','.');
    estoque = aux;

    QString unidade;

    if(ui->comboBox->currentText() == "UNIDADE")
    {
       unidade = "UN";
    }

    else
    {
        unidade = "KG";
    }

   query.prepare ("update tb_produtos set descricao_produto = '"+descricao+"', quantidade_produto = '"+QString::number(estoque.toDouble())+"', valor_compra = '"+QString::number(valor_compra.toFloat())+"', valor_venda = '"+QString::number(valor_venda.toFloat())+"', observacao_produto = '"+observacao+"', unidade ='"+unidade+"' where id_produto = "+id);

	
	QMessageBox msgBox;
    msgBox.setWindowTitle("Salvar?");

    msgBox.setWindowIcon(QPixmap(":/Imgs/UI/PNG/icon.png"));
    msgBox.setStyleSheet(".QLabel {color: rgb(255, 255, 255);} .QMessageBox{background-color: rgb(52, 73, 94); color: rgb(255, 255, 255);}.QPushButton{ background-color: rgb(52, 152, 219); border-radius:1px; color: rgb(255, 255, 255); width: 50px; height: 30px;} .QPushButton:hover{background-color: rgb(41, 128, 185);}");
    msgBox.setFont(QFont("Roboto",12));
    msgBox.setText(("Quer mesmo salvar alterações?"));
    QAbstractButton *myYesButton = msgBox.addButton(("Sim"), QMessageBox::YesRole);
    QAbstractButton *myNoButton = msgBox.addButton(("Não"), QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.exec();

        if(msgBox.clickedButton() == myYesButton)
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

        if(msgBox.clickedButton() == myNoButton)
        {

        }

}

void cadastro_produtos_editar::on_btn_cancelar_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Cancelar?");

    msgBox.setWindowIcon(QPixmap(":/Imgs/UI/PNG/icon.png"));
    msgBox.setStyleSheet(".QLabel {color: rgb(255, 255, 255);} .QMessageBox{background-color: rgb(52, 73, 94); color: rgb(255, 255, 255);}.QPushButton{ background-color: rgb(52, 152, 219); border-radius:1px; color: rgb(255, 255, 255); width: 50px; height: 30px;} .QPushButton:hover{background-color: rgb(41, 128, 185);}");
    msgBox.setFont(QFont("Roboto",12));
    
    msgBox.setText(("Quer mesmo descartar as alterações?"));
    QAbstractButton *myYesButton = msgBox.addButton(("Sim"), QMessageBox::YesRole);
    QAbstractButton *myNoButton = msgBox.addButton(("Não"), QMessageBox::NoRole);
    
    msgBox.setIcon(QMessageBox::Question);
    msgBox.exec();

        if(msgBox.clickedButton() == myYesButton)
        {
            close();
        }

        if(msgBox.clickedButton() == myNoButton)
        {
            
        }
}
