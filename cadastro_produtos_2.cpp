#include "cadastro_produtos_2.h"
#include "ui_cadastro_produtos_2.h"


cadastro_produtos_2::cadastro_produtos_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastro_produtos_2)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui->btn_voltar->setFocus();
    ui->le_codigo->clear();
}

cadastro_produtos_2::~cadastro_produtos_2()
{
    delete ui;
}

void cadastro_produtos_2::on_btn_voltar_clicked()
{
    close();
}


void cadastro_produtos_2::on_btn_cancelar_clicked()
{
    QMessageBox::StandardButton retorno = QMessageBox::question(this,"Sair","Deseja realmente cancelar?", QMessageBox::Yes|QMessageBox::No);

    if(retorno == QMessageBox::Yes)
    {
        close();
    }
}

void cadastro_produtos_2::on_btn_salvar_clicked()
{
    if(!banco.abrir_conexao())
    {
        QMessageBox::warning(this,"Erro","Erro ao abrir banco de dados");
    } else {

        QString aux;
        QString codigo = ui->le_codigo->text();
        QString descricao = ui->le_descricao->text();
        QString observacao = ui->le_observacao->text();
        QString quantidade;
        QString valor_compra;
        QString valor_venda;
        QString unidade;

        if(ui->comboBox->currentText() == "UNIDADE")
        {
           unidade = "UN";
        }

        else
        {
            unidade = "KG";
        }




        aux = ui->le_preco_custo->text();
        std::replace(aux.begin(),aux.end(),',','.');

        valor_compra = aux;

        aux = ui->le_preco_venda->text();
        std::replace(aux.begin(),aux.end(),',','.');
        valor_venda = aux;

        aux = ui->le_estoque->text();
        std::replace(aux.begin(),aux.end(),',','.');
        quantidade = aux;

        QSqlQuery inserindo;
        inserindo.prepare("insert into tb_produtos (id_produto,descricao_produto,quantidade_produto,valor_compra,valor_venda,observacao_produto,unidade) values"
        "("+codigo+",'"+descricao+"',"+QString::number(quantidade.toDouble())+","+QString::number(valor_compra.toFloat())+","+QString::number(valor_venda.toFloat())+",'"+observacao+"','"+unidade+"')");


        if(codigo=="")
        {
            ui->label->setText("* CAMPOS OBRIGATÓRIOS");
            ui->label->setStyleSheet("color: rgb(231, 76, 60);");
            ui->line->setStyleSheet("background-color: transparent;border-top: none;border-bottom: 2px solid;border-bottom-color: rgb(231, 76, 60);");
        }

        if(descricao=="")
        {
                ui->label->setText("* CAMPOS OBRIGATÓRIOS");
                ui->label->setStyleSheet("color: rgb(231, 76, 60);");
                ui->line_2->setStyleSheet("background-color: transparent;border-top: none;border-bottom: 2px solid;border-bottom-color: rgb(231, 76, 60);");
        }

        if(valor_venda==""){

            ui->label->setText("* CAMPOS OBRIGATÓRIOS");
            ui->label->setStyleSheet("color: rgb(231, 76, 60);");
            ui->line_3->setStyleSheet("background-color: transparent;border-top: none;border-bottom: 2px solid;border-bottom-color: rgb(231, 76, 60);");
        }

        else{

        if(!inserindo.exec())
        {
            if(verifica_produto_cadastrado(codigo))
            {
              QMessageBox::warning(this,"","Produto já cadastrado");

            }
            QMessageBox::warning(this,"","Erro ao inserrir produto!");
        }else{
            QMessageBox::information(this,"","Produto salvo com sucesso!");

                QMessageBox msgBox;
                msgBox.setWindowTitle("Continuar cadastrando?");

                msgBox.setWindowIcon(QPixmap(":/Imgs/UI/PNG/icon.png"));
                msgBox.setStyleSheet(".QLabel {color: rgb(255, 255, 255);} .QMessageBox{background-color: rgb(52, 73, 94); color: rgb(255, 255, 255);}.QPushButton{ background-color: rgb(52, 152, 219); border-radius:1px; color: rgb(255, 255, 255); width: 50px; height: 30px;} .QPushButton:hover{background-color: rgb(41, 128, 185);}");
                msgBox.setFont(QFont("Roboto",12));
                
                msgBox.setText(("Deseja salvar outro produto?"));
                QAbstractButton *myYesButton = msgBox.addButton(("SIM"), QMessageBox::YesRole);
                QAbstractButton *myNoButton = msgBox.addButton(("NÃO"), QMessageBox::NoRole);
                
                msgBox.setIcon(QMessageBox::Question);
                msgBox.exec();

                    if(msgBox.clickedButton() == myYesButton)
                    {
                            ui->le_codigo->clear();
                            ui->le_estoque->clear();
                            ui->le_descricao->clear();
                            ui->le_preco_custo->clear();
                            ui->le_preco_venda->clear();
                            ui->le_observacao->clear();
                            ui->line->setStyleSheet("background-color:transparent;border-top: none;border-bottom: 2px solid;border-bottom-color: rgb(189, 195, 199);");
                            ui->line_2->setStyleSheet("background-color:transparent;border-top: none;border-bottom: 2px solid;border-bottom-color: rgb(189, 195, 199);");
                            ui->line_3->setStyleSheet("background-color:transparent;border-top: none;border-bottom: 2px solid;border-bottom-color: rgb(189, 195, 199);");
                            ui->le_codigo->setFocus(); 
                    }

                    if(msgBox.clickedButton() == myNoButton)
                    {
                        close();
                    }

            
        }


    }
        banco.fechar_conexao();
}
}


bool cadastro_produtos_2::verifica_produto_cadastrado(QString cod)
{
    bool retorno = false;
    QSqlQuery verifica;
    verifica.prepare("select * from tb_produtos where id_produto = " + cod);

    if(verifica.exec())
    {
        verifica.first();
        if(verifica.value(0)==cod)
        {
            retorno = true;
            qDebug() << "Foi até aqui";
        }
    }


    return retorno;
}
