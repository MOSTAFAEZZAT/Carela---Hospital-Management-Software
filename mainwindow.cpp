
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime >

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->removeTab(1);


    QDateTime local(QDateTime::currentDateTime());

    QString Time1=  local.toString();

     qDebug() << Time1;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    QStringList driverNmaeList = QSqlDatabase::drivers();

    qDebug() << driverNmaeList ;

    QSqlDatabase Databas  = QSqlDatabase::database();
    /* if(QSqlDatabase::contains("qt_sql_default_connection")){
        Databas = QSqlDatabase::database("qt_sql_default_connection");
      qDebug() <<  "1" ;}
    else{
        Databas = QSqlDatabase::addDatabase("Q");
      qDebug() <<  "2" ;
    }*/
    Databas =   QSqlDatabase::addDatabase("QMYSQL", "SecConnection");
    Databas.setHostName("localhost") ;
    Databas.setUserName("root");
    Databas.setPassword("root");
    Databas.setDatabaseName("clinic_database");
    if( QSqlDatabase::contains( "SecConnection" ) )
    {
      QSqlDatabase db = QSqlDatabase::database( "SecConnection" );
      qDebug() << "Donnne" ;
      //now do some stuff with it
    }
    else
    {
      qDebug()  << "something error" ;

        // connection not found, do something
    }


    if(Databas.open()){
        qDebug() <<  "Connected" ;
    }else {

       qDebug() << Databas.lastError().text();
      qDebug() << "not Connected";
    }

    QSqlQuery qr (Databas) ;
    qr.exec("select * from Employees") ;
    while(qr.next()) {
        qDebug() << qr.value(1) ;

    }

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(Databas);
    QString User = ui->lineEdit_Username_3->text();
    QString Pass = ui->lineEdit_2_Password_3->text() ;
        if(QString(User).isNull()||QString(Pass).isNull()) {

        QMessageBox::information(this,"Result","Pls Fill The User and Password") ;
        return ;
    }

         qry->prepare(" select Employees.Name COLLATE latin1_general_cs LIKE 'a%' , Employees.Password COLLATE latin1_general_cs LIKE 'a%' from  Employees WHERE Name = :User  AND  Password = :Pass ");
         qry->bindValue(":User", User) ;
         qry->bindValue(":Pass",Pass) ;

            if(qry->exec())
            {
                if(qry->next())
                {
                model->setQuery(*qry);
                QString  S =  qry->value(0).toString() + "Login Successed ";
                QMessageBox::information(this,"Result",S) ;
                hide();
             //   mainprocess = new MainProcess(this) ;



              showingdata.show();

                }
                else
                    {
                   QMessageBox::information(this,"Result","Sorry Try Again") ;
                   qDebug() << qry->lastError();
                    }

              }
              else {
                QMessageBox::information(this,"Result","Sorry Try Again") ;
                qDebug() << qry->lastError();}
}

void MainWindow::on_pushButton_4_clicked()
{

    ui->tabWidget->removeTab(0);
    ui->tabWidget->insertTab(1,ui->widget,"SignUp");
}



void MainWindow::on_pushButton_8_clicked()
{
    QSqlDatabase Databas  = QSqlDatabase::database();
  /*if(QSqlDatabase::contains("qt_sql_default_connection")){
      Databas = QSqlDatabase::database("qt_sql_default_connection");
    qDebug() <<  "1" ;}
  else{
      Databas = QSqlDatabase::addDatabase("QMYSQL");
    qDebug() <<  "2" ;
  }*/
   Databas =   QSqlDatabase::addDatabase("QMYSQL", "SecConnection");
  Databas.setHostName("localhost") ;
  Databas.setUserName("root");
  Databas.setPassword("root");
  Databas.setDatabaseName("clinic_database");
   Databas.open();
   QSqlQuery *qry = new QSqlQuery(Databas);


  QString User = ui->lineEdit_Username_4->text();
  QString Pass = ui->lineEdit_2_Password_4->text() ;
// QString ss = " INSERT  Name , Password INTO Employees  WHERE Name == :User AND Password == :Pass " ;
    qry->prepare(" INSERT INTO Employees (Name,Password) VALUES(:User,:Pass) ");
  qry->bindValue(":User", User);
    qry->bindValue(":Pass",Pass);

       if(qry->exec()) {

        QMessageBox::information(this,"Reslut","User Registered Successfully");

     }else {

           QMessageBox::information(this,"Reslut","not WellDone");
           QMessageBox::information(this,"Reslut",qry->lastError().text());


       }
      Databas.close() ;

}

void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget->removeTab(0);
    ui->tabWidget->insertTab(0,ui->widget_2,"Login");
}
