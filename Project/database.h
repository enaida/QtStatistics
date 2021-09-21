#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>

class Database
{

    QSqlDatabase db;

private:
    static Database* instance;
    Database(Database const&);       // Not implemented.
    void operator=(Database const&); // Not implemented.
    Database();
    void updateSumaAktivnosti(QString id);

public:
    static Database* getInstance();
    QStringList getStudentInfoByID(QString id);
    QStringList getStudentInfoByBroj(QString broj_indeksa);
    QStringList getPassedStudentsOcjena();
    QStringList getPassedStudentsUkupno();
    int getPassedStudents();
    int getNotPassedStudents();
    void updateStudentInfoByID(QString column, QString newValue, QString id);
    void updateStudentFinalnaOcjenaByID(QString id);
};

#endif // DATABASE_H
