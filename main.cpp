#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>
#include <QMessageBox>

static QSqlDatabase bancoDados = QSqlDatabase::addDatabase("QMYSQL");

static bool connectionToDB();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!connectionToDB()){
        return 0;
    }

    LoginWindow login;
    login.setModal(true);
    login.exec();
    if(!login.isConnected()){
        return 0;
    }

    MainWindow w;
    w.show();

    return a.exec();
    bancoDados.close();
}

static bool connectionToDB(){
    bancoDados.setHostName("localhost");
    bancoDados.setUserName("username");
    bancoDados.setPassword("password");
    bancoDados.setDatabaseName("estoque");

    if(!bancoDados.open()){
        auto mensagem = QMessageBox();
        mensagem.setWindowTitle("Error");
        mensagem.setText("Não foi possivel acessar o banco de dados!");
        mensagem.setIcon(QMessageBox().Critical);

        mensagem.exec();
        return false;
    }
    else{
        qDebug() << "OK";
    }
    return true;
}
