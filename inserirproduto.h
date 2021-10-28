#ifndef INSERIRPRODUTO_H
#define INSERIRPRODUTO_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

namespace Ui {
class inserirproduto;
}

class inserirproduto : public QDialog
{
    Q_OBJECT

public:
    explicit inserirproduto(QWidget *parent = nullptr);
    ~inserirproduto();

private slots:
    void on_cancelButton_clicked();

    void on_eraseButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::inserirproduto *ui;
};

#endif // INSERIRPRODUTO_H
