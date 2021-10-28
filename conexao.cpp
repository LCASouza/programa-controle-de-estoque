#include <iostream>
#include <QMessageBox>
#include <QApplication>

static QSqlDatabase bancoDados = QSqlDatabase::addDatabase("QMYSQL");

static void connectionToDB(){
    bancoDados.setHostName("localhost");
    bancoDados.setUserName("root");
    bancoDados.setPassword("DxfzP5u2");
    bancoDados.setDatabaseName("estoque");

    if(!bancoDados.open()){
        auto mensagem = QMessageBox();
        mensagem.setWindowTitle("Error");
        mensagem.setText("Não foi possivel acessar o banco de dados!");
        mensagem.setIcon(QMessageBox().Critical);

        mensagem.exec();
    }
}
