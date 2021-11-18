#include "mysqldatabase.h"
#include <QMessageBox>
#include <QtDebug>
MySqlDatabase::MySqlDatabase()
{



}
bool MySqlDatabase::ConnectDB(){



    MySqlDB  = QSqlDatabase::database();
    MySqlDB =   QSqlDatabase::addDatabase("QMYSQL", "FirstConnection");
    MySqlDB.setHostName("localhost") ;
    MySqlDB.setUserName("root");
    MySqlDB.setPassword("root");
    MySqlDB.setDatabaseName("clinic_database");

    if(MySqlDB.open())
   {

           qDebug() << "connected sqldatabase";
       return true ;

   }
   else
    {
       qDebug() << "Error in opneing " << MySqlDB.lastError().text();
       return false;
    }


}
