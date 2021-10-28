#ifndef REMOVERPRODUTO_H
#define REMOVERPRODUTO_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QTableWidget>
#include <QMessageBox>

namespace Ui {
class removerproduto;
}

class removerproduto : public QDialog
{
    Q_OBJECT

public:
    explicit removerproduto(QWidget *parent = nullptr);
    ~removerproduto();

private slots:
    void on_codeLine_returnPressed();

    void on_removeButton_clicked();

    void on_cancelButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::removerproduto *ui;
};

#endif // REMOVERPRODUTO_H
