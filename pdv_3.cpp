#include "pdv_3.h"
#include "ui_pdv_3.h"

double pdv_3::total = 0.0;
double pdv_3::valor_pago = 0.0;
double pdv_3::total_dinheiro = 0.0;
double pdv_3::total_cheque = 0.0;
double pdv_3::total_cartao_cr = 0.0;
double pdv_3::total_cartao_db = 0.0;
double pdv_3::valor_total_com_desconto = 0.0;



pdv_3::pdv_3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pdv_3)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui->frame->setFocus();
    set_valor();
}

pdv_3::~pdv_3()
{
    delete ui;
}

void pdv_3::on_btn_cancelar_venda_clicked()
{
    close();
}

void pdv_3::set_valor()
{
   double sub_total = pdv_2::get_total;
   total = sub_total;
   valor_total_com_desconto = total;
   ui->lb_subtotal_valor->setText("R$ " + QString::number(sub_total,'f',2));
   ui->lb_total->setText("R$ " + QString::number(sub_total,'f',2));
}

void pdv_3::on_le_dinheiro_returnPressed()
{
    calculo_total_pago();
    calcula_troco();
}

void pdv_3::on_le_cheque_returnPressed()
{
    calculo_total_pago();
    calcula_troco();
}

void pdv_3::on_le_cartao_credito_returnPressed()
{
    calculo_total_pago();
    calcula_troco();
}

void pdv_3::on_le_cartao_debito_returnPressed()
{
    calculo_total_pago();
    calcula_troco();
}

void pdv_3::on_le_desconto_returnPressed()
{
    calculo_desconto_em_porcento();
}

void pdv_3::on_le_desconto_2_returnPressed()
{
    calculo_desconto_em_real();
}

void pdv_3::calculo_total_pago()
{
    QString aux = ui->le_dinheiro->text();
    std::replace(aux.begin(),aux.end(),',','.');
    total_dinheiro = aux.toDouble();

    aux = ui->le_cheque->text();
    std::replace(aux.begin(),aux.end(),',','.');
    total_cheque = aux.toDouble();

    aux = ui->le_cartao_credito->text();
    std::replace(aux.begin(),aux.end(),',','.');
    total_cartao_cr = aux.toDouble();

    aux = ui->le_cartao_debito->text();
    std::replace(aux.begin(),aux.end(),',','.');
    total_cartao_db = aux.toDouble();

    valor_pago = total_cheque + total_dinheiro + total_cartao_cr + total_cartao_db;
    ui->lb_pago_valor->setText("R$ " + QString::number(valor_pago,'f',2));
}


void pdv_3::calculo_desconto_em_real()
{
    QString aux = ui->le_desconto_2->text();
    std::replace(aux.begin(),aux.end(),',','.');
    double desc = aux.toDouble();


    if(desc <= total)
    {
        valor_total_com_desconto = total - desc;
        ui->lb_total->setText("R$ " + QString::number(valor_total_com_desconto,'f',2));
        calcula_troco_com_desconto(&valor_total_com_desconto);
    }
}


void pdv_3::calcula_troco()
{
        if(valor_pago>0)
        {
            double troco = valor_pago - total;
            ui->lb_troco_valor->setText("R$" + QString::number(troco,'f',2));
        }
        else
        {
            ui->lb_troco_valor->setText("R$ 0.00");
        }
}





void pdv_3::calculo_desconto_em_porcento()
{
    QString aux = ui->le_desconto->text();
    std::replace(aux.begin(),aux.end(),',','.');

    double valor_porcentagem = aux.toDouble();


    valor_total_com_desconto = total - ((valor_porcentagem/100) * total);

    ui->lb_total->setText("R$ " + QString::number(valor_total_com_desconto,'f',2));

    calcula_troco_com_desconto(&valor_total_com_desconto);
}

void pdv_3::calcula_troco_com_desconto(double *desc)
{
    double troco = valor_pago - *desc;
    ui->lb_troco_valor->setText("R$ " + QString::number(troco,'f',2));
}

void pdv_3::zerar_variaveis_static()
{
    pdv_3::total = 0.0;
    pdv_3::valor_pago = 0.0;
    pdv_3::total_dinheiro = 0.0;
    pdv_3::total_cheque = 0.0;
    pdv_3::total_cartao_cr = 0.0;
    pdv_3::total_cartao_db = 0.0;
    pdv_3::valor_total_com_desconto = 0.0;
}

void pdv_3::on_btn_finalizar_venda_clicked()
{
    if(valor_pago >= total)
    {
        pdv_2::finalizado = true;
        QMessageBox::warning(this,"",pdv_2::finaliza_venda());
        zerar_variaveis_static();
        close();
    }
    else
    {
        QMessageBox::critical(this,"Pagamento Inferiror","Pagamento inferior, por gentileza conferir Valor pago");
    }
}
