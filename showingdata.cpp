#include "showingdata.h"
#include "ui_showingdata.h"

ShowingData::ShowingData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowingData)
{
    ui->setupUi(this);

    this->setFixedSize(this->geometry().width(),this->geometry().height());

    ui->dateEdit_5->setMaximumDate(QDate::currentDate().addDays(365));
    ui->dateEdit_5->setMaximumDate(QDate::currentDate().addYears(5000));
    ui->dateEdit_5->setDisplayFormat("dd/MM/yyyy");
}



ShowingData::~ShowingData()
{
    delete ui;
}

void ShowingData::on_pushButton_2_clicked(){
    QString PatientsName_Showingdata = ui->lineEdit_showdataName->text();
    QString PhoneNumber_Showingdata = ui->lineEdit_2_showdataPhone->text();
    if(PatientsName_Showingdata.isEmpty()&&PhoneNumber_Showingdata.isEmpty()){

        QMessageBox::warning(this,"Error","You've to Write PhoneNumber or Patient'sName");
        return ;

    }
    qDebug() << "Hello Not respond" ;

     profile3 = new Profile3();
    profile3->Namedb = PatientsName_Showingdata ;
    profile3->Phonedb = PhoneNumber_Showingdata ;
    qDebug() << "Hello Not respond" ;

      qDebug() << "Hello Not respond" ;

    if(profile3->ViewProfile3()==false){
        return ;
    }

    qDebug() << "Hello Not respond" ;
    profile3->show();
      qDebug() << "Hello Not respond" ;
}

void ShowingData::on_dateEdit_5_dateChanged(const QDate &date){
    ui->dateEdit_5->setCalendarPopup(true);
    int year , month , day ;
    QDate dd = date ;
    dd.getDate(&year , &month , &day);
    Birthdate = ui->dateEdit_5->date().toString() ;
    qDebug()<< year << month << day ;


}
void ShowingData::getDate(){


     QDate  currentdate ;
     QDate  date1 = currentdate.currentDate();
     int day , month , year ;
     date1.getDate(&year , &month , &day);
     qDebug()  <<  day << month << year ;
      int day1 , month1, year1 ;
      QDate dd  = ui->dateEdit_5->date() ;

      dd.getDate(&year1 ,&month1, &day1);
      qDebug()  <<  day1 << month1 << year1 ;

}






void ShowingData::on_pushButton_clicked(){
    if(!ui->lineEdit_Patientname_5->isModified()||!ui->lineEdit_3_PhoeNum_5->isModified()||
            !ui->lineEdit_2_NationalId_5->isModified()|| !ui->lineEdit_Address->isModified())
    {
        QMessageBox::warning(this,"Result","Some Fields not Filled , Complete all Information");
        return ;
    }


    QString PatientName1 = ui->lineEdit_Patientname_5->text() ;
   //QString BirthDate = ui->lineEdit_2_Age->text() ;
    QString PhoneNum1 = ui->lineEdit_3_PhoeNum_5->text() ;
    QString NationalID = ui->lineEdit_2_NationalId_5->text() ;
    QString Address  =  ui->lineEdit_Address->text();
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Result", "Are you sure? Note: After Clicking Changes will be Saved in Database",
                                QMessageBox::Yes|QMessageBox::No);

   if(reply == QMessageBox::Yes){

       QSqlDatabase Databasee = QSqlDatabase::database();
       Databasee =   QSqlDatabase::addDatabase("QMYSQL" , "thirdConnection");
       Databasee.setHostName("localhost") ;
       Databasee.setUserName("root");
       Databasee.setPassword("root");
       Databasee.setDatabaseName("Clinic_Database");

        if(Databasee.open()){
          QMessageBox::about(this,"res","databaseopen") ;


        }else{
            QMessageBox::about(this,"res","database not open") ;
            qDebug() <<  Databasee.lastError();
        }



          QSqlQuery query(Databasee) ;
          QString Query = " INSERT INTO `PatientsInfo`(  `PatientsName`, `NationalNumber`, `PhoneNum`, `Age`, `PatientsAddress`, `Date_Time` ) VALUES (:PatientName1,:NationalID,:Address,:PhoneNum1,:Birthdate,NOW()) " ;
          query.prepare(Query);
          query.bindValue(":PatientName1",PatientName1);
          query.bindValue(":NationalID",NationalID);
          query.bindValue(":PhoneNum1",PhoneNum1);
          query.bindValue(":Birthdate",Birthdate);
          query.bindValue(":Address",Address);

        if(query.exec()){
           QMessageBox::information(this,"Result","Data Inserted Successfully") ;
        }

       else{

           QMessageBox::information(this,"Error", query.lastError().text()  ) ;
        //  QDebug() << query.lastError().text();

       }





     }
      else {
     qDebug() << "Yes was *not* clicked";
   }

}
