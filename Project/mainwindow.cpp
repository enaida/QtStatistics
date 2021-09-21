#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBitmap>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database = Database::getInstance();

    QPixmap pixmap(":/resources/images/Logo.JPG");
    ui->logo->setPixmap(pixmap);
    ui->logo->setMask(pixmap.mask());
    ui->logo->show();

    horiziontalHeader = new QStringList();
    setHeaderLabels();
    firstColumnData = new QStringList();
    thirdColumnData = new QStringList();
    maxValuesData = new QStringList();
    setMaxValuesData();
    setColumnsData();

    model = new QStandardItemModel(7,4,this);
    model->setHorizontalHeaderLabels(*horiziontalHeader);
    setTableDataByID("1");
    ui->studentTable->setModel(model);
    ui->studentTable->verticalHeader()->hide();
    ui->studentTable->setColumnWidth(0, 230);
    ui->studentTable->setColumnWidth(1, 90);
    ui->studentTable->setColumnWidth(2, 90);
    ui->studentTable->setColumnWidth(3, 90);
    setLabelBackground();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setHeaderLabels()
{
    horiziontalHeader->push_back("Aktivnost");
    horiziontalHeader->push_back("Ocjena");
    horiziontalHeader->push_back("Opseg");
    horiziontalHeader->push_back("Procenat");
}

void MainWindow::setColumnsData()
{
    firstColumnData->push_back("Prisustvo");
    firstColumnData->push_back("Aktivnost na nastavi");
    firstColumnData->push_back("Projekat");
    firstColumnData->push_back("Test");
    firstColumnData->push_back("Suma predispitnih aktivnosti");
    firstColumnData->push_back("Zavrsni ispit");
    firstColumnData->push_back("Ukupno");

    thirdColumnData->push_back("0 - 5");
    thirdColumnData->push_back("0 - 5");
    thirdColumnData->push_back("0 - 20");
    thirdColumnData->push_back("0 - 20");
    thirdColumnData->push_back("0 - 50");
    thirdColumnData->push_back("0 - 50");
    thirdColumnData->push_back("0 - 100");

}

void MainWindow::setMaxValuesData()
{
    maxValuesData->push_back("5");
    maxValuesData->push_back("5");
    maxValuesData->push_back("20");
    maxValuesData->push_back("20");
    maxValuesData->push_back("50");
    maxValuesData->push_back("50");
    maxValuesData->push_back("100");
}

void MainWindow::setTableDataByID(QString id)
{
    studentInfo = database->getStudentInfoByID(id);
    setTableData();
}

void MainWindow::setTableDataByBroj(QString broj_indeksa)
{
    studentInfo = database->getStudentInfoByBroj(broj_indeksa);
    setTableData();
}

void MainWindow::setUpukno()
{
    QModelIndex indexSumaValue = model->index(4,1);
    double sumaValue = model->data(indexSumaValue).toDouble();
    QModelIndex indexZavrsniValue = model->index(5,1);
    double zavrsniValue = model->data(indexZavrsniValue).toDouble();
    double ukupno = sumaValue + zavrsniValue;
    QModelIndex indexUkupnoValue = model->index(6,1);
    model->setData(indexUkupnoValue, QString::number(ukupno));
    double procentage = ukupno / maxValuesData->at(6).toDouble() * 100;
    QModelIndex indexUkupnoProcentage = model->index(6,3);
    model->setData(indexUkupnoProcentage, QString::number(procentage).append(" %"));
}

void MainWindow::setTableData()
{
    for(int i = 0; i < 7; i++)
    {
        QModelIndex index = model->index(i,0);
        model->setData(index, firstColumnData->at(i));
    }

    for(int i = 0; i < 7; i++)
    {
        QModelIndex index = model->index(i,2);
        model->setData(index, thirdColumnData->at(i));
    }

    ui->prezimeText->setPlainText(studentInfo.at(1));
    ui->imeText->setPlainText(studentInfo.at(2));
    ui->indeksText->setPlainText(studentInfo.at(3));

    for(int i = 0; i < 6; i++)
    {
        QString value = studentInfo.at(i + 4);
        QModelIndex index = model->index(i,1);
        if(value.size() < 1)
            value.push_back("0");
        model->setData(index, value);
        double procentage = value.toDouble() / maxValuesData->at(i).toDouble() * 100;
        index = model->index(i,3);
        model->setData(index, QString::number(procentage).append(" %"));
    }
    setUpukno();
    if(studentInfo.at(10).toLong() > 4)
        ui->finalnaOcjenaValue->setText(studentInfo.at(10));
    else
        ui->finalnaOcjenaValue->setText("");
}

void MainWindow::setLabelBackground()
{
    QPalette paletteLabel = ui->finalnaOcjenaLabel->palette();
    paletteLabel.setColor(ui->finalnaOcjenaLabel->backgroundRole(), Qt::white);
    ui->finalnaOcjenaLabel->setAutoFillBackground(true);
    ui->finalnaOcjenaLabel->setPalette(paletteLabel);

    QPalette paletteValue = ui->finalnaOcjenaValue->palette();
    paletteValue.setColor(ui->finalnaOcjenaValue->backgroundRole(), Qt::white);
    ui->finalnaOcjenaValue->setAutoFillBackground(true);
    ui->finalnaOcjenaValue->setPalette(paletteValue);
}

void MainWindow::on_searchButton_clicked()
{
    setTableDataByBroj(ui->indeksText->toPlainText());
}

void MainWindow::on_previousButton_clicked()
{
    QString currentIDString = studentInfo.at(0);
    int currentID = currentIDString.toInt();
    if(currentID > 1)
    {
        currentID = currentID - 1;
        setTableDataByID(QString::number(currentID));
    }
}

void MainWindow::on_nextButton_clicked()
{
    QString currentIDString = studentInfo.at(0);
    int currentID = currentIDString.toInt();
    currentID = currentID + 1;
    if(currentID < 70)
    {
    setTableDataByID(QString::number(currentID));
    }
}

void MainWindow::on_prisustvoButton_clicked()
{
    QModelIndex indexPrisustvo = model->index(0,1);
    QString newValue = model->data(indexPrisustvo).toString();
    database->updateStudentInfoByID("`prisustvo `", newValue, studentInfo.at(0));
    setTableDataByID(studentInfo.at(0));
}

void MainWindow::on_nastaviButton_clicked()
{
    QModelIndex indexNastavi = model->index(1,1);
    QString newValue = model->data(indexNastavi).toString();
    database->updateStudentInfoByID("aktivnost_na_nastavi", newValue, studentInfo.at(0));
    setTableDataByID(studentInfo.at(0));
}

void MainWindow::on_projekatButton_clicked()
{
    QModelIndex indexProjekat = model->index(2,1);
    QString newValue = model->data(indexProjekat).toString();
    database->updateStudentInfoByID("projekat", newValue, studentInfo.at(0));
    setTableDataByID(studentInfo.at(0));
}

void MainWindow::on_testButton_clicked()
{
    QModelIndex indexTest = model->index(3,1);
    QString newValue = model->data(indexTest).toString();
    database->updateStudentInfoByID("test", newValue, studentInfo.at(0));
    setTableDataByID(studentInfo.at(0));
}

void MainWindow::on_zavrsniButton_clicked()
{
    QModelIndex indexTest = model->index(5,1);
    QString newValue = model->data(indexTest).toString();
    database->updateStudentInfoByID("zavrsni_ispit", newValue, studentInfo.at(0));
    setTableDataByID(studentInfo.at(0));
}

void MainWindow::on_prolaznostStatistikaButton_clicked()
{
    statistika = new Statistika();
    QVector<int> dataValues;
    QStringList dataName;
    dataName.push_back("passed");
    dataValues.push_back(database->getPassedStudents());
    dataName.push_back("not passed");
    dataValues.push_back(database->getNotPassedStudents());
    statistika->setChartData(dataName, dataValues, "Statistika: Prolaznost");
    statistika->show();
}

void MainWindow::on_prolaznostOcjenaStatistikaButton_clicked()
{
    statistika = new Statistika();
    QStringList result;
    QVector<int> dataValues;
    QStringList dataName;
    result = database->getPassedStudentsOcjena();
    for(int i = 0; i < result.size() / 2; i++)
    {
        dataName.push_back(result.at(2 * i));
        dataValues.push_back(result.at(2 * i + 1).toInt());
    }
    statistika->setChartData(dataName, dataValues, "Statistika: Prolaznost po ocjenama");
    statistika->show();
}

void MainWindow::on_prolaznostBodovimaStatistika_clicked()
{
    statistika = new Statistika();
    QStringList result;
    QVector<int> dataValues;
    QStringList dataName;
    result = database->getPassedStudentsUkupno();
    for(int i = 0; i < result.size() / 2; i++)
    {
        dataName.push_back(result.at(2 * i));
        dataValues.push_back(result.at(2 * i + 1).toInt());
    }
    statistika->setChartData(dataName, dataValues, "Statistika: Prolaznost po bodovima");
    statistika->show();
}
