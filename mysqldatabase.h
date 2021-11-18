#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H
 #include <QtSql>
 #include <QSqlDatabase>
 #include <QSqlQuery>
 #include <QSqlDriver>

class MySqlDatabase : public QSqlDatabase
{
public:
    MySqlDatabase();
    QSqlDatabase MySqlDB;

    bool ConnectDB();

private:

};

#endif // MYSQLDATABASE_H
