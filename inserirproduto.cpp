#include "inserirproduto.h"
#include "ui_inserirproduto.h"

inserirproduto::inserirproduto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inserirproduto)
{
    ui->setupUi(this);

    ui->costLine->setValidator(new QDoubleValidator(0, 10000000, 2, this));
    ui->valueLine->setValidator(new QDoubleValidator(0, 10000000, 2, this));
    ui->codeLine->setValidator(new QIntValidator(0, 10000000, this));
    ui->quantLine->setValidator(new QIntValidator(0, 10000000, this));
}

inserirproduto::~inserirproduto()
{
    delete ui;
}

void inserirproduto::on_cancelButton_clicked()
{
    this->close();
}


void inserirproduto::on_eraseButton_clicked()
{
    ui->codeLine->clear();
    ui->costLine->clear();
    ui->nameLine->clear();
    ui->quantLine->clear();
    ui->valueLine->clear();
    ui->marcaLine->clear();
}


void inserirproduto::on_saveButton_clicked()
{
    QSqlQuery qry, query, guery;

    QString codeL = ui->codeLine->text();
    QString marcaL = ui->marcaLine->text();
    QString costL = ui->costLine->text();
    QString nameL = ui->nameLine->text();
    QString quantL = ui->quantLine->text();
    QString valueL = ui->valueLine->text();

    query.exec("SELECT * FROM produtos WHERE codigo = '"+codeL+"';");
    guery.exec("SELECT * FROM produtos WHERE nome = '"+nameL+"';");

    if(query.size()>0){
        QMessageBox::warning(this, "Alerta", "Já existe um produto cadastrado com este código!\n"
                                             "Insira outro código e tente novamente.");
    }
    else if(guery.size()>0){
        QMessageBox::warning(this, "Alerta", "Já existe um produto cadastrado com este nome!\n"
                                             "Insira outro nome e tente novamente.");
    }
    else{
        QMessageBox msg;

        auto escolha = QMessageBox::question(this, "Confirmação", "Inserir produto?", QMessageBox::Yes | QMessageBox::No);

        if(escolha == QMessageBox::Yes){
            qry.exec("INSERT INTO produtos (codigo, nome, marca, preco, custo, quantidade) VALUES('"+codeL+"', '"+nameL+"', '"+marcaL+"', '"+valueL+"', '"+costL+"', '"+quantL+"');");
            qry.finish();
            this->close();
        }
    }
    guery.finish();
    query.finish();
}

