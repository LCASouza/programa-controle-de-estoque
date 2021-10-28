#include "removerproduto.h"
#include "ui_removerproduto.h"

removerproduto::removerproduto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::removerproduto)
{
    ui->setupUi(this);

    ui->codeLine->setFocus();
    ui->searchButton->setIcon(QIcon("lupa.png"));
    ui->codeLine->setValidator(new QIntValidator(0, 10000000, this));
}

removerproduto::~removerproduto()
{
    delete ui;
}

void removerproduto::on_codeLine_returnPressed()
{
    QString codeL = ui->codeLine->text();

    QSqlQuery qry;
    qry.exec("SELECT * FROM produtos WHERE codigo = '"+codeL+"';");

    if(qry.size()>0){
        qry.next();
        ui->nameLabel->setText(qry.value(2).toString());
        ui->valueLabel->setText("VALOR: R$ "+qry.value(4).toString());
        ui->quantLabel->setText("QUANTIDADE: "+qry.value(6).toString());
        ui->costLabel->setText("CUSTO: R$ "+qry.value(5).toString());
    }

    qry.finish();
}


void removerproduto::on_removeButton_clicked()
{
    QString codeL = ui->codeLine->text();

    if(codeL!=""){
        QSqlQuery qry;

        auto escolha = QMessageBox::question(this, "Confirmação", "Remover produto?", QMessageBox::Yes | QMessageBox::No);

        qry.exec("SELECT * FROM produtos WHERE codigo = '"+codeL+"';");

        if(qry.size()>0){
            if(escolha == QMessageBox::Yes){
                qry.exec("DELETE FROM produtos WHERE codigo = '"+codeL+"';");
                this->close();
            }
        }
        else{
            QMessageBox::warning(this, "Alerta", "Não existe um produto com esse código!");
        }
    }
}


void removerproduto::on_cancelButton_clicked()
{
    this->close();
}


void removerproduto::on_searchButton_clicked()
{
    if(ui->codeLine->text()!=""){
       on_codeLine_returnPressed();
    }
}

