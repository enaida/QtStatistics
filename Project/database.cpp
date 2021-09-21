#include "database.h"
#include <QSqlError>

Database* Database::instance = NULL;

Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\SQLITE\\zadaca.db");
    bool ok = db.open();
    qDebug() << ok;
    qDebug() << db.lastError().text();
}

Database* Database::getInstance()
{
    if (instance == 0)
    {
        instance = new Database();
    }

    return instance;
}

QStringList Database::getStudentInfoByID(QString id)
{
    QString sql;
    QStringList result;
    QSqlQuery query;
    sql = "SELECT * FROM students WHERE id = ";
    sql.append(id);
    query.exec(sql);
    query.first();
    for(int i = 0; i < 11; i++)
        result.push_back(query.value(i).toString());
    return result;
}

QStringList Database::getStudentInfoByBroj(QString broj_indeksa)
{
    QString sql;
    QStringList result;
    QSqlQuery query;
    sql = "SELECT * FROM students WHERE broj_indeksa = '";
    sql.append(broj_indeksa);
    sql.append("'");
    query.exec(sql);
    query.first();
    for(int i = 0; i < 11; i++)
        result.push_back(query.value(i).toString());
    return result;
}

int Database::getPassedStudents()
{
    QString sql;
    QString result;
    QSqlQuery query;
    sql = "SELECT count(id) FROM students WHERE finalna_ocjena > 5 ";
    query.exec(sql);
    query.first();
    result.append(query.value(0).toString());
    return result.toInt();
}

int Database::getNotPassedStudents()
{
    QString sql;
    QString result;
    QSqlQuery query;
    sql = "SELECT count(id) FROM students WHERE finalna_ocjena <= 5 OR finalna_ocjena IS NULL ";
    query.exec(sql);
    query.first();
    result.append(query.value(0).toString());
    return result.toInt();
}

QStringList Database::getPassedStudentsOcjena()
{
    QString sql;
    QStringList result;
    QSqlQuery query;
    sql = "SELECT finalna_ocjena, COUNT(finalna_ocjena) FROM students where finalna_ocjena >= 5 GROUP BY finalna_ocjena";
    query.exec(sql);
    query.first();
    while (query.next()) {
        result.push_back(query.value(0).toString());
        result.push_back(query.value(1).toString());
    }
    return result;
}

QStringList Database::getPassedStudentsUkupno()
{
    QString sql;
    QStringList result;
    QSqlQuery query;
    sql = "SELECT suma_predispitnith_aktivnosti + zavrsni_ispit, ";
    sql.append("COUNT(suma_predispitnith_aktivnosti + zavrsni_ispit)");
    sql.append(" FROM students where finalna_ocjena > 5 GROUP BY suma_predispitnith_aktivnosti + zavrsni_ispit");
    query.exec(sql);
    query.first();
    while (query.next()) {
        result.push_back(query.value(0).toString());
        result.push_back(query.value(1).toString());
    }
    return result;
}

void Database::updateStudentInfoByID(QString column, QString newValue, QString id)
{
    QString sql;
    QSqlQuery query;
    sql = "UPDATE students SET ";
    sql.append(column);
    sql.append(" = ");
    sql.append(newValue);
    sql.append(" WHERE id = ");
    sql.append(id);
    query.exec(sql);
    updateSumaAktivnosti(id);
    updateStudentFinalnaOcjenaByID(id);
    qDebug() << query.lastError().text();
}

void Database::updateSumaAktivnosti(QString id)
{
    QString sql;
    QSqlQuery query;
    sql = "UPDATE students SET suma_predispitnith_aktivnosti = `prisustvo ` + ";
    sql.append(" aktivnost_na_nastavi + ");
    sql.append(" projekat + ");
    sql.append(" test ");
    sql.append(" WHERE id = ");
    sql.append(id);
    query.exec(sql);
}

void Database::updateStudentFinalnaOcjenaByID(QString id)
{
    QString sql;
    QSqlQuery query;
    sql = "UPDATE students SET finalna_ocjena = ";
    sql.append("ROUND((suma_predispitnith_aktivnosti * 1.0 / 10 +");
    sql.append(" zavrsni_ispit * 1.0 / 10), 0)");
    sql.append(" WHERE id = ");
    sql.append(id);
    if (query.exec(sql) >= 5)
    qDebug() << query.lastError().text();
}
