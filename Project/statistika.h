#ifndef STATISTIKA_H
#define STATISTIKA_H

#include <QDialog>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPieSeries>
#include <QPieSlice>


namespace Ui {
class Statistika;
}

class Statistika : public QDialog
{
    Q_OBJECT

public:
    explicit Statistika(QWidget *parent = 0);
    ~Statistika();
    void setChartData(QStringList dataName, QVector<int> dataValues, QString chartTitle);

private:
    QPieSeries* series;
    QPieSlice* slice;
    QChart* chart;
    Ui::Statistika *ui;
};

#endif // STATISTIKA_H
