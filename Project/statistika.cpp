#include "statistika.h"
#include "ui_statistika.h"

Statistika::Statistika(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistika)
{
    ui->setupUi(this);
    series = new QPieSeries();
    chart = new QChart();
}

Statistika::~Statistika()
{
    delete ui;
}

void Statistika::setChartData(QStringList dataName, QVector<int> dataValues, QString chartTitle)
{
    for(int i = 0; i < dataValues.size(); i++)
    {
       series->append(dataName.at(i), dataValues.at(i));
    }

    chart->addSeries(series);
    chart->setTitle(chartTitle);

    ui->graphicsView->setChart(chart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}
