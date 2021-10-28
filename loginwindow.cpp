#include "loginwindow.h"
#include "ui_loginwindow.h"

static bool conectado=false;

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->userLine->setFocus();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

bool LoginWindow::isConnected(){
    return conectado;
}

void LoginWindow::on_loginButton_clicked()
{
    QString username=ui->userLine->text();
    QString passwd=ui->passwdLine->text();

    QSqlQuery qry;

    if(qry.exec("SELECT * FROM usuarios WHERE usuario='"+username+"' and senha='"+passwd+"';")){
        int qryCont=0;

        while(qry.next())
            qryCont++;

        if(qryCont > 0){
            conectado = true;
            this->close();
        }
        else{
            auto mensagem = QMessageBox();
            mensagem.setWindowTitle("Login Incorreto");
            mensagem.setText("Usuario ou senha incorretos!");
            mensagem.setIcon(QMessageBox().Critical);

            mensagem.exec();
        }
    }
}


void LoginWindow::on_quitButton_clicked()
{
    conectado = false;
    this->close();
}

