#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "database.h"
#include "statistika.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_searchButton_clicked();
    void on_previousButton_clicked();
    void on_nextButton_clicked();
    void on_prisustvoButton_clicked();
    void on_nastaviButton_clicked();
    void on_projekatButton_clicked();
    void on_testButton_clicked();
    void on_zavrsniButton_clicked();
    void on_prolaznostStatistikaButton_clicked();

    void on_prolaznostOcjenaStatistikaButton_clicked();

    void on_prolaznostBodovimaStatistika_clicked();

private:
    void setHeaderLabels();
    void setTableData();
    void setTableDataByID(QString id);
    void setTableDataByBroj(QString broj_indeksa);
    void setColumnsData();
    void setMaxValuesData();
    void setUpukno();
    void setLabelBackground();

private:
    Statistika *statistika;
    Database *database;
    QStringList studentInfo;
    QStandardItemModel *model;
    QStringList *horiziontalHeader, *firstColumnData, *thirdColumnData;
    QStringList *maxValuesData;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
