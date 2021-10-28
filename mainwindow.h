#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QTableWidget>
#include <QMessageBox>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadTable();
    void loadInfo();
    void setLines();

    void on_quitButton_clicked();

    void on_insertButton_clicked();

    void on_productsTable_activated(const QModelIndex &index);

    void on_refreshButtonTable_clicked();

    void on_searchLine_returnPressed();

    void on_searchLineMarca_returnPressed();


    void on_searchButton_clicked();

    void on_removeButton_clicked();

    void on_precoButton_clicked();

    void on_nomeButton_clicked();

    void on_marcaButton_clicked();

    void on_custoButton_clicked();

    void on_incButton_clicked();

    void on_decButton_clicked();

private:
    Ui::MainWindow *ui;
    void inicio();
};
#endif // MAINWINDOW_H
