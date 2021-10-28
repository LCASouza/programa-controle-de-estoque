#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inserirproduto.h"
#include "removerproduto.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->searchButton->setIcon(QIcon("lupa.png"));
    ui->refreshButtonTable->setIcon(QIcon("reload.png"));

    //Carregar a lista de produtos.
    //Carregar o primeiro produto da tabela produtos para a interface.
    inicio();

    setLines();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setLines(){
    ui->searchLine->setValidator(new QIntValidator(0, 10000000, this));
    ui->quantDecLineChange->setValidator(new QIntValidator(0, 10000000, this));
    ui->quantIncLineChange->setValidator(new QIntValidator(0, 10000000, this));
    ui->costLineChange->setValidator(new QDoubleValidator(0, 10000000, 2, this));
    ui->precoLineChange->setValidator(new QDoubleValidator(0, 10000000, 2, this));
}


void MainWindow::loadTable(){
    QSqlQuery qry;
    qry.exec("SELECT * FROM produtos;");

    if(qry.size()>0){
        ui->productsTable->setRowCount(qry.size());

        int row=0;
        while(qry.next()){
            QString x = qry.value(1).toString();
            QString w = qry.value(6).toString();
            QString y = "R$ "+qry.value(4).toString();
            QString z = qry.value(2).toString();
            ui->productsTable->setItem(row, 0, new QTableWidgetItem(x));
            ui->productsTable->setItem(row, 1, new QTableWidgetItem(w));
            ui->productsTable->setItem(row, 2, new QTableWidgetItem(y));
            ui->productsTable->setItem(row, 3, new QTableWidgetItem(z));
            row++;
        }
    }

    //ui->productsTable->setSortingEnabled(true);
    //ui->productsTable->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::loadInfo(){
    QSqlQuery qry;
    qry.exec("SELECT * FROM produtos;");
    if(qry.size()>0){
        qry.next();

        ui->nameText->setText(qry.value(2).toString());
        ui->marcaText->setText(qry.value(3).toString());
        ui->codeText->setText(qry.value(1).toString());
        ui->quantText->setText(qry.value(6).toString()+" UNIDADES DISPONIVEIS");
        ui->valueText->setText(qry.value(4).toString());
        ui->costText->setText(qry.value(5).toString());
    }
}


void MainWindow::inicio(){
    loadInfo();
    loadTable();
}


void MainWindow::on_quitButton_clicked()
{
    auto escolha = QMessageBox::question(this, "Encerramento", "Finalizar o programa?", QMessageBox::Yes | QMessageBox::No);

    if(escolha == QMessageBox::Yes){
        QApplication::quit();
    }
}


void MainWindow::on_insertButton_clicked()
{
    inserirproduto inserir;

    inserir.exec();
}


void MainWindow::on_removeButton_clicked()
{
    removerproduto remover;

    remover.exec();
}


void MainWindow::on_refreshButtonTable_clicked()
{
    ui->productsTable->setRowCount(0);
    loadTable();
}


void MainWindow::on_productsTable_activated(const QModelIndex &index)
{
    QString codigo = ui->productsTable->model()->data(index).toString();

    ui->rowLabel->setText(QString::number(ui->productsTable->currentRow()));

    QSqlQuery qry;

    qry.prepare("SELECT * FROM produtos WHERE codigo = '"+codigo+"' OR nome = '"+codigo+"';");

    if(qry.exec()){
        while(qry.next()){
            ui->nameText->setText(qry.value(2).toString());
            ui->marcaText->setText(qry.value(3).toString());
            ui->codeText->setText(qry.value(1).toString());
            ui->quantText->setText(qry.value(6).toString()+" UNIDADES DISPONIVEIS");
            ui->valueText->setText(qry.value(4).toString());
            ui->costText->setText(qry.value(5).toString());
        }
    }
}


void MainWindow::on_searchLine_returnPressed()
{
    QString codeL = ui->searchLine->text();

    QSqlQuery qry;
    qry.exec("SELECT * FROM produtos WHERE codigo = '"+codeL+"';");

    if(qry.size()>0){
        qry.next();

        ui->productsTable->setRowCount(qry.size());

        QString x = qry.value(1).toString();
        QString y = qry.value(6).toString();
        QString z = qry.value(2).toString();
        ui->productsTable->setItem(0, 0, new QTableWidgetItem(x));
        ui->productsTable->setItem(0, 1, new QTableWidgetItem(y));
        ui->productsTable->setItem(0, 2, new QTableWidgetItem(z));

        qry.finish();
    }
}


void MainWindow::on_searchLineMarca_returnPressed()
{
    QString marcaL = ui->searchLineMarca->text();

    QSqlQuery qry;
    qry.exec("SELECT * FROM produtos WHERE marca = '"+marcaL+"';");

    if(qry.size()>0){
        ui->productsTable->setRowCount(qry.size());

        int row=0;
        while(qry.next()){
            QString x = qry.value(1).toString();
            QString w = qry.value(6).toString();
            QString y = "R$ "+qry.value(4).toString();
            QString z = qry.value(2).toString();
            ui->productsTable->setItem(row, 0, new QTableWidgetItem(x));
            ui->productsTable->setItem(row, 1, new QTableWidgetItem(w));
            ui->productsTable->setItem(row, 2, new QTableWidgetItem(y));
            ui->productsTable->setItem(row, 3, new QTableWidgetItem(z));
            row++;
        }

        qry.finish();
    }
}


void MainWindow::on_searchButton_clicked()
{
    QString codeL = ui->searchLine->text();
    QString marcaL = ui->searchLineMarca->text();

    if(codeL != ""){
        on_searchLine_returnPressed();
    }
    else if(marcaL != ""){
        on_searchLineMarca_returnPressed();
    }
    else if(codeL != "" && marcaL != ""){
        on_searchLine_returnPressed();
    }
}


void MainWindow::on_precoButton_clicked()
{
    QString valueL = ui->precoLineChange->text();
    QString codeL = ui->codeText->text();

    if(valueL!="" && codeL!=""){
        auto escolha = QMessageBox::question(this, "Confirmação", "Alterar o preço do produto?", QMessageBox::Yes | QMessageBox::No);

        if(escolha == QMessageBox::Yes){
            QSqlQuery qry;
            qry.exec("UPDATE produtos SET preco = '"+valueL+"' WHERE codigo = '"+codeL+"'");
            ui->precoLineChange->clear();
            QMessageBox::information(this, "Sucesso", "Alteração realizada com sucesso!");
            ui->valueText->setText(valueL);
            ui->productsTable->setItem(ui->rowLabel->text().toInt(), 2, new QTableWidgetItem("R$ "+valueL));
        }
    }
}


void MainWindow::on_nomeButton_clicked()
{
    QString nameL = ui->nameLineChange->text();
    QString codeL = ui->codeText->text();

    if(nameL!="" && codeL!=""){
        auto escolha = QMessageBox::question(this, "Confirmação", "Alterar o nome do produto?", QMessageBox::Yes | QMessageBox::No);

        if(escolha == QMessageBox::Yes){
            QSqlQuery qry;
            qry.exec("UPDATE produtos SET nome = '"+nameL+"' WHERE codigo = '"+codeL+"'");
            ui->nameLineChange->clear();
            QMessageBox::information(this, "Sucesso", "Alteração realizada com sucesso!");
            ui->nameText->setText(nameL);
            ui->productsTable->setItem(ui->rowLabel->text().toInt(), 3, new QTableWidgetItem(nameL));
        }
    }
}


void MainWindow::on_marcaButton_clicked()
{
    QString marcaL = ui->marcaLineChange->text();
    QString codeL = ui->codeText->text();

    if(marcaL!="" && codeL!=""){
        auto escolha = QMessageBox::question(this, "Confirmação", "Alterar a marca do produto?", QMessageBox::Yes | QMessageBox::No);

        if(escolha == QMessageBox::Yes){
            QSqlQuery qry;
            qry.exec("UPDATE produtos SET marca = '"+marcaL+"' WHERE codigo = '"+codeL+"'");
            ui->marcaLineChange->clear();
            QMessageBox::information(this, "Sucesso", "Alteração realizada com sucesso!");
            ui->marcaText->setText(marcaL);
        }
    }
}


void MainWindow::on_custoButton_clicked()
{
    QString costL = ui->costLineChange->text();
    QString codeL = ui->codeText->text();

    if(costL!="" && codeL!=""){
        auto escolha = QMessageBox::question(this, "Confirmação", "Alterar o custo do produto?", QMessageBox::Yes | QMessageBox::No);

        if(escolha == QMessageBox::Yes){
            QSqlQuery qry;
            qry.exec("UPDATE produtos SET custo = '"+costL+"' WHERE codigo = '"+codeL+"'");
            ui->costLineChange->clear();
            QMessageBox::information(this, "Sucesso", "Alteração realizada com sucesso!");
            ui->costText->setText(costL);
        }
    }
}


void MainWindow::on_incButton_clicked()
{
    QString addQuant = ui->quantIncLineChange->text();
    QString codeL = ui->codeText->text();

    if(addQuant!="" && codeL!=""){
        auto escolha = QMessageBox::question(this, "Confirmação", "Adicionar '"+addQuant+"' unidades do produto?", QMessageBox::Yes | QMessageBox::No);

        QSqlQuery query;

        query.exec("SELECT * FROM produtos WHERE codigo = '"+codeL+"'");
        query.next();
        int x = query.value(6).toInt();
        addQuant = QString::number(addQuant.toInt()+x);
        query.finish();

        if(escolha == QMessageBox::Yes){
            QSqlQuery qry;
            qry.exec("UPDATE produtos SET quantidade = '"+addQuant+"' WHERE codigo = '"+codeL+"'");
            ui->quantIncLineChange->clear();
            QMessageBox::information(this, "Sucesso", "Alteração realizada com sucesso!");
            ui->quantText->setText(addQuant+" UNIDADES DISPONIVEIS");
            ui->productsTable->setItem(ui->rowLabel->text().toInt(), 1, new QTableWidgetItem(addQuant));
        }
    }
}


void MainWindow::on_decButton_clicked()
{
    QString decQuant = ui->quantDecLineChange->text();
    QString codeL = ui->codeText->text();

    if(decQuant!="" && codeL!=""){
        auto escolha = QMessageBox::question(this, "Confirmação", "Remover '"+decQuant+"' unidades de produto?", QMessageBox::Yes | QMessageBox::No);

        QSqlQuery query;

        query.exec("SELECT * FROM produtos WHERE codigo = '"+codeL+"'");
        query.next();
        int x = query.value(6).toInt();
        decQuant = QString::number(x-decQuant.toInt());
        query.finish();

        if(escolha == QMessageBox::Yes){
            QSqlQuery qry;
            qry.exec("UPDATE produtos SET quantidade = '"+decQuant+"' WHERE codigo = '"+codeL+"'");
            ui->quantDecLineChange->clear();
            QMessageBox::information(this, "Sucesso", "Alteração realizada com sucesso!");
            ui->quantText->setText(decQuant+" UNIDADES DISPONIVEIS");
            ui->productsTable->setItem(ui->rowLabel->text().toInt(), 1, new QTableWidgetItem(decQuant));
        }
    }
}

