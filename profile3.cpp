#include "profile3.h"
#include "ui_profile3.h"

#include <QTreeWidgetItem>
#include <QScreen>
#include <QItemSelectionModel>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractSpinBox>
#include <QStandardItemModel>
#include <QObject>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextEdit>
#include <QPagedPaintDevice>

Profile3::Profile3(QWidget *parent ) :
    QWidget(parent),
    ui(new Ui::Profile3)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle );
    ui->tabWidget_2->tabBar()->setStyle(new CustomTabStyle );
    // QTreeWidgetItem *item = new QTreeWidgetItem;
    int column;

    connect(ui->treeWidget_Kitchen,
            &QTreeWidget::itemDoubleClicked,
            [&,this](QTreeWidgetItem *item){Kitchen_DoubleClicked (item, Kitchen);});
    connect(Kitchen.CancelButton_TreeWidget_2, &QPushButton::clicked, [&,this]{Cancel_TreeWidget_Kitchen( Kitchen);});


    connect(ui->treeWidget_Medicine,
            &QTreeWidget::itemDoubleClicked,
            [&,this](QTreeWidgetItem *item){Medicine_DoubleClicked (item, Medicine);});

    connect(Medicine.CancelButton_TreeWidget_6, &QPushButton::clicked, [&,this]{Cancel_TreeWidget_Medicine( Medicine);});


    connect(ui->treeWidget_Analysis,
            &QTreeWidget::itemDoubleClicked,
            [&,this](QTreeWidgetItem *item){Analysis_DoubleClicked (item, Analysis);});

    connect(Analysis.CancelButton_treeWidget_Analysis, &QPushButton::clicked, [&,this]{Cancel_TreeWidget_Analysis( Analysis);});

    ui->plainTextEdit_2->setReadOnly(true);

}

Profile3::~Profile3()
{
    delete ui;
}
bool Profile3::ViewProfile3(){

    QSqlDatabase   Databasee  =   QSqlDatabase::database();
    Databasee =   QSqlDatabase::addDatabase("QMYSQL");
    Databasee.setHostName("localhost") ;
    Databasee.setUserName("root");
    Databasee.setPassword("root");
    Databasee.setDatabaseName("Clinic_Database");

    if(Databasee.open()){

        QMessageBox::about(this,"res","databaseopen") ;


    }else {
        QMessageBox::about(this,"res","database not open") ;
        //qDebug() <<  Databasee.lastError();
    }

    QSqlQuery * querry = new QSqlQuery ( )  ;

    querry->prepare(" SELECT * FROM patientsinfo where patientsinfo.PatientsName = :Namedb or patientsinfo.PhoneNum = :Phonedb  ") ;
    querry->bindValue(":Namedb",Namedb) ;
    querry->bindValue(":Phonedb",Phonedb) ;
    /*
      PatientName;
      Age;
      BloodPrint;
      consultant;
      DiagnosisDisease;
      Analysing;
      TotalPriceAnalysis;
      Medicine;
      TotalPriceMedicine;
    */




    if(querry->exec())
    {


        if(querry->next())
        {

            ID = querry->value(0).toString();
            qDebug()<< ID <<"ID" ;
            PatientName = querry->value(1).toString();
            National_ID = querry->value(2).toString();
            PhoneNumber =querry->value(3).toString();
            PatientsAddress = querry->value(4).toString();
            Age =querry->value(5).toString();
            Date_Time = querry->value(6).toString();
            BloodPrint= querry->value(7).toString();
            consultant= querry->value(8).toString();
            DiagnosisDisease = querry->value(9).toString();
            MedicineDB =querry->value(11).toString();
            Analysing=querry->value(12).toString();
            TotalPriceAnalysis= querry->value(11).toString();
            TotalPriceMedicine = querry->value(13).toString();
            Radiation_xRays	= querry->value(14).toString();
            Radiation_xRays_TotalPrice= querry->value(15).toString();
            FoodNDrinks	= querry->value(16).toString();
            FoodNDrinksTotalPrice= querry->value(17).toString();

        }else{
            QMessageBox::about(this,"Result","Patient not correct") ;
            return false;
        }

    }else{

        QMessageBox::about(this,"Result","Patient not correct") ;
        return false;
    }






    ui->label_PatientID->setText(ID);
    ui->label_PatientName->setText(PatientName);
    ui->label_PatientPhone->setText(PhoneNumber);
    ui->label_PatientNationalID->setText(National_ID);
    ui->label_PatientAddress->setText(PatientsAddress);
    ui->label_TimeEntry->setText(Date_Time);
    ui->label_PatietDatebirth->setText(Age);
/*

   querry->prepare(" SELECT * FROM patients_medication where patients_medication.patient_id = :Phonedb  ") ;
   querry->bindValue(":Phonedb",Phonedb);

     auto model = new QStandardItemModel();

   if(querry->exec()){



       //   QModelIndex * model1 = new   QModelIndex();
       //  model->setStringList(list);
       ui->tableView->setModel(model);
       ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
       model->setHorizontalHeaderItem(0, new QStandardItem("Medicine_id"));
       model->setHorizontalHeaderItem(1, new QStandardItem("Medicine_Name"));
       model->setHorizontalHeaderItem(2, new QStandardItem("Medicine_Price"));
       model->setHorizontalHeaderItem(3, new QStandardItem("Medicine_Time_Added"));

   }else{

     qDebug() << querry->lastError() << "Lasterror in medicine data  " ;

   }


   while(querry->next()){

      QString Medicine_id= querry->value(1).toString();
      QString Medicine_Name= querry->value(2).toString();
      QString Medicine_Price= querry->value(3).toString();
      QString Medicine_Time_Added= querry->value(4).toString();
       QList<QStandardItem*> rowData;
       rowData << new QStandardItem(Medicine_id);
       rowData << new QStandardItem(Medicine_Name);
       rowData << new QStandardItem(Medicine_Price);
       rowData << new QStandardItem(Medicine_Time_Added);

       model->appendRow(rowData);

    }
*/


/*

    int Medicinenumber = MedicineDB.count(",") ;
    for(int i=0;i<=Medicinenumber;i++)
    {
        qDebug() << i << "i" ;

        QString section1 = MedicineDB.section('/', i, i);
        QString section = MedicineDB.section(',', i, i);



        qDebug() << section1 << "section1" ;
        QList<QStandardItem*> rowData;
        rowData << new QStandardItem(section);

        model->appendRow(rowData);




    }*/

    Retrieving_Patient_MedicineData();
    Retrieving_Patient_Analysis_Data();
    RetrievingMedicineData();
    Retrieving_Analysis_Data();
    Retrieving_Kitchen_Data();
    Retrieving_X_Rays_Data();


    /*
                 ui->label_19->setText(BloodPrint);
                ui->label_14->setText(consultant);
                ui->plainTextEdit->setPlainText(DiagnosisDisease);
                ui->label_13_TotalPriceAnalysis_8->setText(TotalPriceAnalysis);
                ui->label_10_TotalPriceMedicine_7->setText(TotalPriceMedicine);
                ui->label_7->setText(Radiation_xRays_TotalPrice);
                ui->label_16->setText(FoodNDrinksTotalPrice);
            */





};

bool Profile3::Retrieving_Patient_MedicineData(){



    QSqlDatabase   Databasee  =   QSqlDatabase::database();
    Databasee =   QSqlDatabase::addDatabase("QMYSQL");
    Databasee.setHostName("localhost") ;
    Databasee.setUserName("root");
    Databasee.setPassword("root");
    Databasee.setDatabaseName("Clinic_Database");

    if(Databasee.open()){
        QMessageBox::about(0,"res","databaseopen") ;



    }else {
        QMessageBox::about(0,"res","database not open") ;
        //qDebug() <<  Databasee.lastError();
    }
     QSqlQuery * querry = new QSqlQuery ( )  ;

    querry->prepare(" SELECT * FROM patients_medication where patients_medication.patient_id = :Phonedb  ") ;
    querry->bindValue(":Phonedb",Phonedb);

      auto model = new QStandardItemModel();

    if(querry->exec()){



        //   QModelIndex * model1 = new   QModelIndex();
        //  model->setStringList(list);
        ui->tableView->setModel(model);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        model->setHorizontalHeaderItem(0, new QStandardItem("Medicine_id"));
        model->setHorizontalHeaderItem(1, new QStandardItem("Medicine_Name"));
        model->setHorizontalHeaderItem(2, new QStandardItem("Medicine_Price"));
        model->setHorizontalHeaderItem(3, new QStandardItem("Medicine_Type"));
        model->setHorizontalHeaderItem(4, new QStandardItem("Medicine_Time_Added"));

    }else{

      qDebug() << querry->lastError() << "Lasterror in medicine data  " ;

    }


    while(querry->next()){

       QString Medicine_id= querry->value(1).toString();
       QString Medicine_Name= querry->value(2).toString();
       QString Medicine_Price= querry->value(3).toString();
       QString Medicine_Type= querry->value(4).toString();
       QString Medicine_Time_Added= querry->value(5).toString();
        QList<QStandardItem*> rowData;
        rowData << new QStandardItem(Medicine_id);
        rowData << new QStandardItem(Medicine_Name);
        rowData << new QStandardItem(Medicine_Price);
        rowData << new QStandardItem(Medicine_Type);
        rowData << new QStandardItem(Medicine_Time_Added);

        model->appendRow(rowData);

     }




}


bool Profile3::Retrieving_Patient_Analysis_Data(){



    QSqlDatabase   Databasee  =   QSqlDatabase::database();
    Databasee =   QSqlDatabase::addDatabase("QMYSQL");
    Databasee.setHostName("localhost") ;
    Databasee.setUserName("root");
    Databasee.setPassword("root");
    Databasee.setDatabaseName("Clinic_Database");

    if(Databasee.open()){
        QMessageBox::about(0,"res","databaseopen") ;



    }else {
        QMessageBox::about(0,"res","database not open") ;
        //qDebug() <<  Databasee.lastError();
    }
     QSqlQuery * querry = new QSqlQuery ( )  ;

    querry->prepare(" SELECT * FROM patients_analysis where patients_analysis.patient_id = :Phonedb  ") ;
    querry->bindValue(":Phonedb",Phonedb);

      auto model = new QStandardItemModel();

    if(querry->exec()){



        //   QModelIndex * model1 = new   QModelIndex();
        //  model->setStringList(list);
        ui->tableView_2->setModel(model);
        ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        model->setHorizontalHeaderItem(0, new QStandardItem("Analysis_id"));
        model->setHorizontalHeaderItem(1, new QStandardItem("Analysis_Name"));
        model->setHorizontalHeaderItem(2, new QStandardItem("Analysis_Price"));
        model->setHorizontalHeaderItem(3, new QStandardItem("Analysis_Type"));
        model->setHorizontalHeaderItem(4, new QStandardItem("Analysis_Time_Added"));

    }else{

      qDebug() << querry->lastError() << "Lasterror in medicine data  " ;

    }


    while(querry->next()){

       QString Analysis_id= querry->value(1).toString();
       QString Analysis_Name= querry->value(2).toString();
       QString Analysis_Price= querry->value(3).toString();
       QString Analysis_Type= querry->value(4).toString();
       QString Analysis_Time_Added= querry->value(5).toString();
        QList<QStandardItem*> rowData;
        rowData << new QStandardItem(Analysis_id);
        rowData << new QStandardItem(Analysis_Name);
        rowData << new QStandardItem(Analysis_Price);
        rowData << new QStandardItem(Analysis_Type);
        rowData << new QStandardItem(Analysis_Time_Added);

        model->appendRow(rowData);

     }




}
// Cancel TreeWidget Section



void Profile3::Cancel_TreeWidget_Kitchen(Kitchen_Data &Kitchen){


    QList<QTreeWidgetItem*> itemList1;
    Kitchen.itemm_CancelButton_From_Kitchen = ui->treeWidget_ShowKitchen->currentItem();

    itemList1 = ui->treeWidget_ShowKitchen->selectedItems();

    int index = ui->treeWidget_ShowKitchen->indexOfTopLevelItem(Kitchen.itemm_CancelButton_From_Kitchen) ;
    if(index==-1){
        QMessageBox::warning(this,"Note","Note:Select Vaild Item");
        return ;

    }

    QString MealPrice;


    foreach(Kitchen.itemm_CancelButton_From_Kitchen, itemList1)
    {


        Kitchen.MealPrice = Kitchen.itemm_CancelButton_From_Kitchen->text(2);

        Kitchen.MealPrice1 -= Kitchen.MealPrice.toInt();
        QString price = QString::number(Kitchen.MealPrice1);
        ui->label_11->setText(price);

    }
    ui->treeWidget_ShowKitchen->takeTopLevelItem(index);

    //   QVector <QString> KitechenItemPrice;
    //    QVector <QString> KitechenItemName;


    qDebug() << "index of canceling kitechen " << index ;

    Kitchen.itemm_CancelButton_From_Kitchen->takeChild(0);
    Kitchen.itemm_CancelButton_From_Kitchen->takeChild(1);
    Kitchen.itemm_CancelButton_From_Kitchen->takeChild(2);
    Kitchen.itemm_CancelButton_From_Kitchen->takeChild(3);



    qDebug() << "Done cancel " ;
}



void Profile3::Cancel_TreeWidget_Medicine(pharmacy &Medicine){



    // this function about canceling and removing the Medicine that user added from treeWidget_ShowMedicine and printing the updated price

    QList<QTreeWidgetItem*> itemList1;
    Medicine.itemm_CancelButton_From_TreeWidet_Medicine = ui->treeWidget_ShowMedicine->currentItem();

    itemList1 = ui->treeWidget_ShowMedicine->selectedItems();

    QString title;
    QString Price5;
    int index = ui->treeWidget_ShowMedicine->indexOfTopLevelItem(Medicine.itemm_CancelButton_From_TreeWidet_Medicine) ;
    if(index==-1){
        QMessageBox::warning(this,"Note","Note:Select Vaild Item");
        return ;

    }
    QString MedicinePrice ;


    foreach( Medicine.itemm_CancelButton_From_TreeWidet_Medicine, itemList1)
    {

        MedicinePrice = Medicine.itemm_CancelButton_From_TreeWidet_Medicine->text(2);

        Medicine.DeductTotalPrice(MedicinePrice.toInt());

        ui->label_9->setText(Medicine.TotalPriceString());
    }

    ui->treeWidget_ShowMedicine->takeTopLevelItem(index);


    Medicine.itemm_CancelButton_From_TreeWidet_Medicine->takeChild(0);
    Medicine.itemm_CancelButton_From_TreeWidet_Medicine->takeChild(1);
    Medicine.itemm_CancelButton_From_TreeWidet_Medicine->takeChild(2);
    Medicine.itemm_CancelButton_From_TreeWidet_Medicine->takeChild(3);
    Medicine.itemm_CancelButton_From_TreeWidet_Medicine->takeChild(4);
    Medicine.itemm_CancelButton_From_TreeWidet_Medicine->takeChild(5);


    qDebug() << "Done cancel ";

}


void Profile3::Cancel_TreeWidget_Analysis(Analysis_Data &Analysis)
{



    // this function about canceling and removing the Analysis childs that user added from treeWidget_AnalysisMedicine and printing the updated price


    qDebug() << "Hello from cancel ";
    QList<QTreeWidgetItem*> itemList1;
    Analysis.itemm_CancelButton_From_Analysis = ui->treeWidget_ShowAnalysis->currentItem();

    itemList1 = ui->treeWidget_ShowAnalysis->selectedItems();


    QString AnalysisPrice;


    int index = ui->treeWidget_ShowAnalysis->indexOfTopLevelItem(Analysis.itemm_CancelButton_From_Analysis) ;
    if(index==-1){
        QMessageBox::warning(this,"Note","Note:Select Vaild Item");
        return ;

    }

    foreach(Analysis.itemm_CancelButton_From_Analysis, itemList1)
    {


        AnalysisPrice = Analysis.itemm_CancelButton_From_Analysis->text(2);
        Analysis.TotalPriceAnalysis -= AnalysisPrice.toInt() ;
        QString price = QString::number(Analysis.TotalPriceAnalysis);
        ui->label_13->setText(price);

    }
    ui->treeWidget_ShowAnalysis->takeTopLevelItem(index);


    qDebug() << "index of canceling kitechen " << index ;

    Analysis.itemm_CancelButton_From_Analysis->takeChild(0);
    Analysis.itemm_CancelButton_From_Analysis->takeChild(1);
    Analysis.itemm_CancelButton_From_Analysis->takeChild(2);
    Analysis.itemm_CancelButton_From_Analysis->takeChild(3);
    Analysis.itemm_CancelButton_From_Analysis->takeChild(4);





    qDebug() << "Done cancel " ;



}

bool Profile3::RetrievingMedicineData(){


    QSqlDatabase   Databasee  =   QSqlDatabase::database();
    Databasee =   QSqlDatabase::addDatabase("QMYSQL");
    Databasee.setHostName("localhost") ;
    Databasee.setUserName("root");
    Databasee.setPassword("root");
    Databasee.setDatabaseName("Clinic_Database");

    if(Databasee.open()){
        QMessageBox::about(0,"res","databaseopen") ;



    }else {
        QMessageBox::about(0,"res","database not open") ;
        //qDebug() <<  Databasee.lastError();
    }

    QSqlQuery * querry = new QSqlQuery (Databasee)  ;
    pharmacy Medicine ;
    querry->prepare(" SELECT * FROM pharmacy ") ;
    querry->bindValue(":Medicine.MedicineCode", Medicine.MedicineCode);
    querry->bindValue(":Medicine.MedicineName", Medicine.MedicineName);
    querry->bindValue(":Medicine.MedicineName", Medicine.MedicineName);
    querry->bindValue(":Medicine.MedicineName", Medicine.MedicineName);

    if(querry->exec())
    {
        while(querry->next())
        {

            Medicine.MedicineCode = querry->value(0).toString();
            Medicine.MedicineName = querry->value(1).toString();
            Medicine.MedicinePrice = querry->value(2).toString();
            Medicine.MedicineType = querry->value(3).toString();
            Medicine.MedicineAmount = querry->value(4).toString();
            Medicine.MedicineTimeEntry = querry->value(5).toString();

            QTreeWidgetItem * Item = new QTreeWidgetItem() ;
            Item->setText(0, Medicine.MedicineCode );
            Item->setText(1, Medicine.MedicineName );
            Item->setText(2, Medicine.MedicinePrice );
            Item->setText(3, Medicine.MedicineType );
            Item->setText(4, Medicine.MedicineAmount );
            Item->setText(5, Medicine.MedicineTimeEntry );

            ui->treeWidget_Medicine->addTopLevelItem(Item);


        }

    }else{

        QMessageBox::about(this,"Result","Patient not correct222") ;
        return false;
    }

    ui->treeWidget_Medicine->sortItems(1,Qt::AscendingOrder	);

    return true ;



}

bool Profile3::Retrieving_Analysis_Data(){


    QSqlDatabase   Databasee  =   QSqlDatabase::database();
    Databasee =   QSqlDatabase::addDatabase("QMYSQL");
    Databasee.setHostName("localhost") ;
    Databasee.setUserName("root");
    Databasee.setPassword("root");
    Databasee.setDatabaseName("Clinic_Database");

    if(Databasee.open()){
        QMessageBox::about(0,"res","databaseopen") ;



    }else {
        QMessageBox::about(0,"res","database not open") ;
        //qDebug() <<  Databasee.lastError();
    }

    QSqlQuery * querry = new QSqlQuery (Databasee)  ;
    Analysis_Data Analysis ;
    querry->prepare(" SELECT * FROM analysis_data ") ;
    querry->bindValue(":Analysis.AnalysisCode", Analysis.AnalysisCode);
    querry->bindValue(":Analysis.AnalysisName", Analysis.AnalysisName);
    querry->bindValue(":Analysis.AnalysisName", Analysis.AnalysisPrice);
    querry->bindValue(":Analysis.AnalysisName", Analysis.AnalysisType);
    /*
    QString AnalysisCode;
    QString AnalysisName;
    QString AnalysisPrice;
    QString AnalysisType;



*/
    if(querry->exec())
    {
        while(querry->next())
        {

            Analysis.AnalysisCode = querry->value(0).toString();
            Analysis.AnalysisName = querry->value(1).toString();
            Analysis.AnalysisPrice = querry->value(2).toString();
            Analysis.AnalysisType = querry->value(3).toString();
            Analysis.AnalysisTimeEntry = querry->value(4).toString();

            QTreeWidgetItem * Item = new QTreeWidgetItem() ;
            Item->setText(0, Analysis.AnalysisCode );
            Item->setText(1, Analysis.AnalysisName );
            Item->setText(2, Analysis.AnalysisPrice );
            Item->setText(3, Analysis.AnalysisType );
            Item->setText(4, Analysis.AnalysisTimeEntry );

            ui->treeWidget_Analysis->addTopLevelItem(Item);

        }

    }else{

        QMessageBox::about(this,"Result","Patient not correct222") ;
        return false;
    }

    ui->treeWidget_Analysis->sortItems(1,Qt::AscendingOrder	);




    return true ;

}

bool Profile3::Retrieving_Kitchen_Data(){


    QSqlDatabase   Databasee  =   QSqlDatabase::database();
    Databasee =   QSqlDatabase::addDatabase("QMYSQL");
    Databasee.setHostName("localhost") ;
    Databasee.setUserName("root");
    Databasee.setPassword("root");
    Databasee.setDatabaseName("Clinic_Database");

    if(Databasee.open()){
        QMessageBox::about(0,"res","databaseopen") ;



    }else {
        QMessageBox::about(0,"res","database not open") ;
        //qDebug() <<  Databasee.lastError();
    }

    QSqlQuery * querry = new QSqlQuery ()  ;
    Kitchen_Data Kitchen ;
    querry->prepare(" SELECT * FROM kitchen ") ;
    querry->bindValue(":Kitchen.MealCode", Kitchen.MealCode);
    querry->bindValue(":Kitchen.MealName", Kitchen.MealName );
    querry->bindValue(":Kitchen.MealPrice", Kitchen.MealPrice);
    querry->bindValue(":Kitchen.MealType", Kitchen.MealType);

    if(querry->exec())
    {
        while(querry->next())
        {

            Kitchen.MealCode =  querry->value(0).toString();
            Kitchen.MealName =  querry->value(1).toString();
            Kitchen.MealPrice = querry->value(2).toString();
            Kitchen.MealType =  querry->value(3).toString();


            QTreeWidgetItem * Item = new QTreeWidgetItem() ;
            Item->setText(0, Kitchen.MealCode  );
            Item->setText(1, Kitchen.MealName  );
            Item->setText(2, Kitchen.MealPrice  );
            Item->setText(3, Kitchen.MealType );

            ui->treeWidget_Kitchen->addTopLevelItem(Item);


        }

    }else{

        QMessageBox::about(this,"Result","Patient not correct222") ;
        return false;
    }

    ui->treeWidget_Kitchen->sortItems(1,Qt::AscendingOrder	);

    return true ;



}

bool Profile3::Retrieving_X_Rays_Data(){


    QSqlDatabase   Databasee  =   QSqlDatabase::database();
    Databasee =   QSqlDatabase::addDatabase("QMYSQL");
    Databasee.setHostName("localhost") ;
    Databasee.setUserName("root");
    Databasee.setPassword("root");
    Databasee.setDatabaseName("Clinic_Database");

    if(Databasee.open()){
        QMessageBox::about(0,"res","databaseopen") ;



    }else {
        QMessageBox::about(0,"res","database not open") ;
        //qDebug() <<  Databasee.lastError();
    }

    QSqlQuery * querry = new QSqlQuery ()  ;
    X_Ray X_ray ;
    querry->prepare(" SELECT * FROM X_Rays ") ;
    querry->bindValue(":X_ray.X_RaysCode", X_ray.X_RaysCode);
    querry->bindValue(":X_ray.X_RaysName", X_ray.X_RaysName );
    querry->bindValue(":X_ray.X_RaysType", X_ray.X_RaysType);
    querry->bindValue(":X_ray.X_RaysPrice",X_ray.X_RaysPrice);

    if(querry->exec())
    {
        while(querry->next())
        {

            X_ray.X_RaysCode =  querry->value(0).toString();
            X_ray.X_RaysName =  querry->value(1).toString();
            X_ray.X_RaysType = querry->value(2).toString();
            X_ray.X_RaysPrice =  querry->value(3).toString();


            QTreeWidgetItem * Item = new QTreeWidgetItem() ;
            Item->setText(0,  X_ray.X_RaysCode   );
            Item->setText(1, X_ray.X_RaysName  );
            Item->setText(2, X_ray.X_RaysType );
            Item->setText(3, X_ray.X_RaysPrice );

            ui->treeWidget_XRays->addTopLevelItem(Item);


        }

    }else{

        QMessageBox::about(this,"Result","Patient not correct222") ;
        return false;
    }

    ui->treeWidget_XRays->sortItems(1,Qt::AscendingOrder	);

    return true ;



}
/*{

void Profile3::on_pushButton_clicked()
{

        QList<QCheckBox *> allButtons =  ui->Medicine->findChildren<QCheckBox *>();
        qDebug() <<allButtons.size();
        for(int i = 0; i < allButtons.size(); ++i)
        {
            allButtons.at(i)->setEnabled(true);
          //  if(allButtons.at(i)->isCheck ed())
            //   qDebug() << "Use" << allButtons.at(i)->text()<< i;//or what you need
        }
}*/

void  Profile3::Analysis_DoubleClicked(QTreeWidgetItem *item,Analysis_Data &Analysis){


    QList<QTreeWidgetItem*> itemList_Analysis;

    itemList_Analysis = ui->treeWidget_Analysis->selectedItems();

    QString AnalysisCode ;
    QString AnalysisName ;
    QString AnalysisPrice ;
    QString AnalysisType;
    QString AnalysisTimeAdded ;
    QString TotalPrice;
    foreach( item, itemList_Analysis){

        AnalysisCode = item->text(0);
        AnalysisName = item->text(1);
        AnalysisPrice = item->text(2);
        AnalysisType = item->text(3);
        AnalysisTimeAdded = item->text(4);

        Analysis.TotalPriceAnalysis += AnalysisPrice.toInt();

        TotalPrice = QString::number(Analysis.TotalPriceAnalysis);

        ui->label_13->setText(TotalPrice);


        //QString TotalPriceAnalysisItems = QString::number(TotalPriceMedicene);


    }



    qDebug() << "Done " ;

    QTreeWidget * tree = ui->treeWidget_ShowAnalysis;
    Analysis.itemm_CancelButton_From_Analysis = new QTreeWidgetItem();

    Analysis.CancelButton_treeWidget_Analysis = new QPushButton("Cancel");

    Analysis.itemm_CancelButton_From_Analysis->setText(0,AnalysisCode);
    Analysis.itemm_CancelButton_From_Analysis->setText(1,AnalysisName);
    Analysis.itemm_CancelButton_From_Analysis->setText(2,AnalysisPrice);
    Analysis.itemm_CancelButton_From_Analysis->setText(3,AnalysisType);
    Analysis.itemm_CancelButton_From_Analysis->setText(4,AnalysisTimeAdded);
    tree->addTopLevelItem(Analysis.itemm_CancelButton_From_Analysis);
    tree->setItemWidget(Analysis.itemm_CancelButton_From_Analysis, 4, Analysis.CancelButton_treeWidget_Analysis);

    connect(Analysis.CancelButton_treeWidget_Analysis, &QPushButton::clicked, [&,this]{Cancel_TreeWidget_Analysis(Analysis);});





}

void Profile3::Kitchen_DoubleClicked(QTreeWidgetItem * item,Kitchen_Data &Kitchen){



    qDebug() << "Hi Kitchen";


    Kitchen.itemList_Kitechen = ui->treeWidget_Kitchen->selectedItems();



    foreach( item, Kitchen.itemList_Kitechen){

        Kitchen.MealCode = item->text(0);
        Kitchen.MealName = item->text(1);
        Kitchen.MealPrice = item->text(2);
        Kitchen.MealType = item->text(3);

        qDebug() << "Hi Kitchen";

        qDebug() <<Kitchen.MealName ;
        Kitchen.MealPrice1 += Kitchen.MealPrice.toInt();
        Kitchen.KitchenTotalPrice  = QString::number( Kitchen.MealPrice1);

        ui->label_11->setText(Kitchen.KitchenTotalPrice);


    }



    qDebug() << "Done " ;

    QTreeWidget * tree = ui->treeWidget_ShowKitchen;
    Kitchen.itemm_CancelButton_From_Kitchen = new QTreeWidgetItem();

    Kitchen.CancelButton_TreeWidget_2 = new QPushButton("Cancel");

    Kitchen.itemm_CancelButton_From_Kitchen->setText(0,Kitchen.MealCode);
    Kitchen.itemm_CancelButton_From_Kitchen->setText(1,Kitchen.MealName);
    Kitchen.itemm_CancelButton_From_Kitchen->setText(2,Kitchen.MealPrice);
    Kitchen.itemm_CancelButton_From_Kitchen->setText(3,Kitchen.MealType);

    tree->addTopLevelItem(Kitchen.itemm_CancelButton_From_Kitchen);
    tree->setItemWidget(Kitchen.itemm_CancelButton_From_Kitchen, 4, Kitchen.CancelButton_TreeWidget_2);
    connect(Kitchen.CancelButton_TreeWidget_2, &QPushButton::clicked, [&,this]{Cancel_TreeWidget_Kitchen(Kitchen);});



}
void Profile3::on_pushButton_SavePatientMedicineItems_clicked(){


    if(ui->treeWidget_ShowMedicine->topLevelItemCount()==0)
    {
        QMessageBox::warning(this,"Result","There are no Items to Save");
        return ;
    }
    //    qDebug() << PatrientName_Delgate_MainProcess << PhoneNumber_Delgate_MainProcess  << "hey";

    QSqlDatabase Databas  = QSqlDatabase::database();
    Databas =   QSqlDatabase::addDatabase("QMYSQL", "SecConnection");
    Databas.setHostName("localhost") ;
    Databas.setUserName("root");
    Databas.setPassword("root");
    Databas.setDatabaseName("Clinic_Database");

    if(Databas.open()){
        qDebug() << "Database connected" ;
    }
    else{
        qDebug() << "Database not connected" ;

    }


    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Result", "Are you sure? Note: After Clicking Changes will be Saved in Database?",
                                  QMessageBox::Yes|QMessageBox::No);

    //  QString Namedb ;
    //  QString Phonedb ;
    if (reply == QMessageBox::Yes) {

        QSqlQuery * MedicineQuery = new QSqlQuery(Databas) ;
        QTreeWidgetItem *item = new QTreeWidgetItem();
        QStringList List ;


        QList <QTreeWidgetItem*> itemList1_Medicine;
        itemList1_Medicine = ui->treeWidget_ShowMedicine->selectedItems();
        pharmacy Medicine ;
        QString MedicineCode ;
        QString MedicineName ;
        QString MedicinePrice ;
        QString MedicineTimeAdded ;
        QString getMedicne_DB ;
        int getMedicnePrice_DB    ;




        qDebug() << itemList1_Medicine <<  " Total Iteems";


        for(int i=0;i<ui->treeWidget_ShowMedicine->topLevelItemCount();i++){


            item = ui->treeWidget_ShowMedicine->topLevelItem(i);

            MedicineCode = item->text(0);
            MedicineName = item->text(1);
            MedicinePrice = item->text(2);
            MedicineTimeAdded = item->text(5);
            QDateTime now = QDateTime::currentDateTime();
            QString NOW = now.toString() ;

            All_Added_ItemOfMedicine += MedicineCode +"---" +NOW +",";

            qDebug() << All_Added_ItemOfMedicine << " Total Items1 " << endl ;


        }
        MedicineQuery->prepare(" INSERT INTO `patients_medication`(`patient_id`, `medicine_id`, `medicine_name`, `Price`, `patients_medication_time`) VALUES (:Phonedb,:MedicineCode,:MedicineName,:MedicinePrice,:MedicineTimeAdded)    ");
       // MedicineQuery->prepare(" SELECT `Medicine`, `TotalPriceMedicine`  FROM `PatientsInfo` WHERE  PatientsInfo.PhoneNum = :Phonedb  ");
        MedicineQuery->bindValue(":Phonedb",Phonedb);
        MedicineQuery->bindValue(":MedicineCode",MedicineCode);
        MedicineQuery->bindValue(":MedicineName",MedicineName);
        MedicineQuery->bindValue(":MedicinePrice",MedicinePrice);
        MedicineQuery->bindValue(":MedicineTimeAdded",MedicineTimeAdded);
        qDebug() << Phonedb << "Phone";
        if(MedicineQuery->exec()){

            /*if(MedicineQuery->next()){

                getMedicne_DB =   MedicineQuery->value(0).toString();
                getMedicnePrice_DB =   MedicineQuery->value(1).toInt();
                qDebug() << getMedicne_DB;

            }
            */


            /*
            All_Added_ItemOfMedicine += getMedicne_DB ;
            TotalMedicinePrice_Int += getMedicnePrice_DB ;
            MedicineQuery->prepare("UPDATE patientsinfo SET Medicine=CONCAT(ifnull(Medicine, '')  , '', :All_Added_ItemOfMedicine)   TotalPriceMedicine=CONCAT(ifnull(TotalPriceMedicine, '')  , '', :TotalMedicinePrice_Int) WHERE patientsinfo.PhoneNum=:Phonedb ") ;
            MedicineQuery->bindValue(":All_Added_ItemOfMedicine",All_Added_ItemOfMedicine);
            MedicineQuery->bindValue(":TotalMedicinePrice_Int",TotalMedicinePrice_Int);
            MedicineQuery->bindValue(":Phonedb",Phonedb);

            if(MedicineQuery->exec()){
                QMessageBox::about(this,"Result","Medicine's Data Inserted Successfully");
            }
            else{
                QMessageBox::about(this,"Error","Error in Inserting Data to medicine");
                qDebug() << MedicineQuery->lastError();

            }*/
        }

        else{
            qDebug() << MedicineQuery->lastError();
        }

        qDebug() << getMedicne_DB <<getMedicnePrice_DB << "old value";



    }

    else{
        qDebug() << "Yes was *not* clicked";
    }




    qDebug() <<  TotalMedicinePrice_Int << " Total price";

    All_Added_ItemOfMedicine = QString();
    MedicineTotalPrice = QString();
    TotalMedicinePrice_Int = 0;
}




void Profile3::Medicine_DoubleClicked(QTreeWidgetItem *item, pharmacy &Medicine) {


    QList <QTreeWidgetItem*> itemList1_Medicine;
    itemList1_Medicine = ui->treeWidget_Medicine->selectedItems();


    QString  MedicineCode ;
    QString MedicineName;
    QString  MedicinePrice;
    QString  MedicineDrugType;
    QString  MedicineAmount;
    QString  MedicineTimeAdded;



    foreach( item, itemList1_Medicine){


        MedicineCode= item->text(0);
        MedicineName = item->text(1);
        MedicinePrice = item->text(2);
        MedicineDrugType= item->text(3);
        MedicineAmount= item->text(4);
        MedicineTimeAdded= item->text(5);






        Medicine.TotalPriceMedicine += MedicinePrice.toInt();

        qDebug() <<MedicinePrice  <<  Medicine.TotalPriceMedicine <<  "PRIce " ;

        Medicine.setTotalPrice(Medicine.TotalPriceMedicine);

        int temp = Medicine.setTotalPrice(Medicine.TotalPriceMedicine);

        qDebug() <<temp << "sec price" ;

        //QString  TotalPriceMedicine1 = QString::number(TotalPriceMedicene);
        ui->label_9->setText(Medicine.TotalPriceString());


    }




    qDebug() << "Done " ;

    QTreeWidget *  tree = ui->treeWidget_ShowMedicine;
    Medicine.itemm_CancelButton_From_TreeWidet_Medicine = new QTreeWidgetItem();
    Medicine.CancelButton_TreeWidget_6 = new QPushButton("Cancel");

    Medicine.itemm_CancelButton_From_TreeWidet_Medicine->setText(0,MedicineCode);
    Medicine.itemm_CancelButton_From_TreeWidet_Medicine->setText(1,MedicineName);
    Medicine.itemm_CancelButton_From_TreeWidet_Medicine->setText(2,MedicinePrice);
    Medicine.itemm_CancelButton_From_TreeWidet_Medicine->setText(3,MedicineDrugType);
    Medicine.itemm_CancelButton_From_TreeWidet_Medicine->setText(4,MedicineAmount);
    Medicine.itemm_CancelButton_From_TreeWidet_Medicine->setText(5,MedicineTimeAdded);


    tree->addTopLevelItem(Medicine.itemm_CancelButton_From_TreeWidet_Medicine);
    tree->setItemWidget(Medicine.itemm_CancelButton_From_TreeWidet_Medicine,6, Medicine.CancelButton_TreeWidget_6);
    connect(Medicine.CancelButton_TreeWidget_6, &QPushButton::clicked, [&,this]{Cancel_TreeWidget_Medicine(Medicine);});




}


void Profile3::on_lineEdit_textChanged(const QString &arg1)
{
    ui->treeWidget_Medicine->selectionModel()->clear();
    ui->treeWidget_Medicine->DoSearch(arg1) ;

}




void Profile3::on_pushButton_EnteringMedicine_clicked(bool checked)
{


    if(ui->medicineCodeLineEdit->text().isEmpty()||ui->nameLineEdit->text().isEmpty() ||ui->priceLineEdit->text().isEmpty() ||
            ui->availableLineEdit->text().isEmpty()){

        QString Price1 =   ui->nameLineEdit->text();
        qDebug() <<  Price1;

        QMessageBox::warning(this,"Reult","Inputs are Empty");
        return ;



    }else {;
    }

    QString MedicineCode = ui->medicineCodeLineEdit->text();
    QString MedicineName =   ui->nameLineEdit->text();
    QString MedicinePrice =   ui->priceLineEdit->text();
    QString MedicineType = ui->drugTypeComboBox->currentText() ;
    QString MedicineAvailableAmount =   ui->availableLineEdit->text();
    double MedicineCode1 = MedicineCode.toDouble();
    int MedicinePrice1 = MedicinePrice.toInt();
    int MedicineAvailableAmount1 = MedicineAvailableAmount.toInt();


    QSqlDatabase  Databasee  =   QSqlDatabase::database();
    Databasee =   QSqlDatabase::addDatabase("QMYSQL");
    Databasee.setHostName("localhost") ;
    Databasee.setUserName("root");
    Databasee.setPassword("root");
    Databasee.setDatabaseName("Clinic_Database");

    if(Databasee.open()){
        QMessageBox::about(this,"res","databaseopen") ;



    }else {
        QMessageBox::about(this,"res","database not open") ;
        //qDebug() <<  Databasee.lastError();
    }
    QSqlQuery * querry = new QSqlQuery (Databasee)   ;
    querry->prepare("INSERT INTO `pharmacy`(`MedicineCode`, `MedicineName`, `MedicinePrice`, `DrugType`, `Medicine_Available_Amount`, `TimeAdded`) VALUES (:MedicineCode1,:MedicineName,:MedicinePrice1,:MedicineType,:MedicineAvailableAmount1,NOW())") ;


    querry->bindValue(":MedicineCode1",MedicineCode1) ;
    querry->bindValue(":MedicineName",MedicineName) ;
    querry->bindValue(":MedicinePrice1",MedicinePrice1) ;
    querry->bindValue(":MedicineType",MedicineType) ;
    querry->bindValue(":MedicineAvailableAmount1",MedicineAvailableAmount1) ;

    if(querry->exec()){
        QMessageBox::information(this,"Result","Data Inserted Successfully") ;
    }

    else{

        QMessageBox::information(this,"Error", querry->lastError().text()  ) ;
        //  QDebug() << query.lastError().text();

    }

    checked = true;





}



void Profile3::on_lineEdit_destroyed()
{
    ui->treeWidget_Medicine->selectionModel()->clear();

}


void Profile3::on_lineEdit_selectionChanged()
{
    ui->treeWidget_Medicine->selectionModel()->clear();

}


void Profile3::pushButton( Kitchen_Data  &Kitchen)
{

    qDebug()<< "  PushButon Save";

    qDebug()<<   Kitchen.KitechenItemName[0];
    qDebug()<< Kitchen.KitechenItemPrice[0];

}

void Profile3::on_pushButton_SavePatientKitchenItems_clicked()
{
    if(ui->treeWidget_ShowKitchen->topLevelItemCount()==0)
    {
        QMessageBox::warning(this,"Result","There are no Items to Save");
        return ;
    }
    //    qDebug() << PatrientName_Delgate_MainProcess << PhoneNumber_Delgate_MainProcess  << "hey";

    QSqlDatabase Databas  = QSqlDatabase::database();
    Databas =   QSqlDatabase::addDatabase("QMYSQL", "SecConnection");
    Databas.setHostName("localhost") ;
    Databas.setUserName("root");
    Databas.setPassword("root");
    Databas.setDatabaseName("Clinic_Database");

    if(Databas.open()){
        qDebug() << "Database connected" ;
    }
    else{
        qDebug() << "Database not connected" ;

    }


    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Result", "Are you sure? Note: After Clicking Changes will be Saved in Database?",
                                  QMessageBox::Yes|QMessageBox::No);

    //  QString Namedb ;
    //  QString Phonedb ;
    if (reply == QMessageBox::Yes) {

        QSqlQuery * KitchenQuery = new QSqlQuery(Databas) ;
        QTreeWidgetItem *item = new QTreeWidgetItem();
        QStringList List ;


        QList <QTreeWidgetItem*> itemList1_Kitchen;
        itemList1_Kitchen = ui->treeWidget_ShowKitchen->selectedItems();

        QString MealCode ;
        QString MealName;
        QString MealPrice;
        QString MealType;




        qDebug() << itemList1_Kitchen <<  " Total Iteems";


        for(int i=0;i<ui->treeWidget_ShowKitchen->topLevelItemCount();i++){


            item = ui->treeWidget_ShowKitchen->topLevelItem(i);

            MealCode  = item->text(0);
            MealName = item->text(1);
            MealPrice = item->text(2);
            MealType = item->text(3);



        }

            KitchenQuery->prepare("INSERT INTO `patients_kitchen`(`patient_id`, `meal_code`, `meal_name`, `meal_price`, `meal_type`, `meal_time_added`) "
                                                       "    VALUES (:Phonedb,:MealCode,:MealName,:MealPrice,:MealType,NOW())") ;

            KitchenQuery->bindValue(":Phonedb",Phonedb);
            KitchenQuery->bindValue(":MealCode",MealCode);
            KitchenQuery->bindValue(":MealName",MealName);
            KitchenQuery->bindValue(":MealPrice",MealPrice);
            KitchenQuery->bindValue(":MealType",MealType);



            if(KitchenQuery->exec()){
                QMessageBox::about(this,"Result","Analysis's Data Inserted Successfully");
              }
            else{
                QMessageBox::about(this,"Error","Error in Inserting Data to Analysis");
                qDebug() << KitchenQuery->lastError();

                }




   } else{
        qDebug() << "Yes was *not* clicked";
    }





}


void Profile3::on_Save_PatientAnalysisItems_clicked(){

    Analysis_Data SaveDataAnalysis;
    if(ui->treeWidget_ShowAnalysis->topLevelItemCount()==0)
    {
        QMessageBox::warning(this,"Result","There are no Items to Save");
        return ;
    }
    //    qDebug() << PatrientName_Delgate_MainProcess << PhoneNumber_Delgate_MainProcess  << "hey";

    QSqlDatabase Databas  = QSqlDatabase::database();
    Databas =   QSqlDatabase::addDatabase("QMYSQL", "SecConnection");
    Databas.setHostName("localhost") ;
    Databas.setUserName("root");
    Databas.setPassword("root");
    Databas.setDatabaseName("Clinic_Database");

    if(Databas.open()){
        qDebug() << "Database connected" ;
    }
    else{
        qDebug() << "Database not connected" ;

    }


    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Result", "Are you sure? Note: After Clicking Changes will be Saved in Database?",
                                  QMessageBox::Yes|QMessageBox::No);

    //  QString Namedb ;
    //  QString Phonedb ;
    if (reply == QMessageBox::Yes) {

        QSqlQuery * AnalysisQuery = new QSqlQuery(Databas) ;
        QTreeWidgetItem *item = new QTreeWidgetItem();
        QStringList List ;


        QList <QTreeWidgetItem*> itemList1_Analysis;
        itemList1_Analysis = ui->treeWidget_ShowAnalysis->selectedItems();

        QString AnalysisCode ;
        QString AnalysisName;
        QString AnalysisPrice;
        QString AnalysisType;

          QString NOW ;

        QString AnalysisTimeAdded ;
        QString getAnalysis_DB ;
        int getAnalysisPrice_DB    ;
        QString All_Added_ItemOfAnalysis;



        qDebug() << itemList1_Analysis <<  " Total Iteems";


        for(int i=0;i<ui->treeWidget_ShowAnalysis->topLevelItemCount();i++){


            item = ui->treeWidget_ShowAnalysis->topLevelItem(i);

            AnalysisCode  = item->text(0);
            AnalysisName = item->text(1);
            AnalysisPrice = item->text(2);
            AnalysisType = item->text(3);

            QDateTime now = QDateTime::currentDateTime();
              NOW = now.toString() ;






        }

            AnalysisQuery->prepare("INSERT INTO `patients_analysis`(`patient_id`, `analysis_id`, `analysis_name`, `analysis_price`, `analysis_type`, `analysis_time_added`)"
                                                       "    VALUES (:Phonedb,:AnalysisCode,:AnalysisName,:AnalysisPrice,:AnalysisType,NOW())") ;

            AnalysisQuery->bindValue(":Phonedb",Phonedb);
            AnalysisQuery->bindValue(":AnalysisCode",AnalysisCode);
            AnalysisQuery->bindValue(":AnalysisName",AnalysisName);
            AnalysisQuery->bindValue(":AnalysisPrice",AnalysisPrice);
            AnalysisQuery->bindValue(":AnalysisType",AnalysisType);



            if(AnalysisQuery->exec()){
                QMessageBox::about(this,"Result","Analysis's Data Inserted Successfully");
              }
            else{
                QMessageBox::about(this,"Error","Error in Inserting Data to Analysis");
                qDebug() << AnalysisQuery->lastError();

                }




   } else{
        qDebug() << "Yes was *not* clicked";
    }



}

void Profile3::on_toolButton_clicked()
{
    QPrinter printer;
    QTextEdit *editor = new QTextEdit();

    QPrintDialog *dialog = new QPrintDialog(&printer, this);

       dialog->setWindowTitle(tr("Print Document"));
       if (editor->textCursor().hasSelection())
           dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
       if (dialog->exec() != QDialog::Accepted)
           return;
}

void Profile3::on_pushButton_3_clicked()
{

    if(  ui->plainTextEdit_2->isReadOnly()==true){

        ui->plainTextEdit_2->setReadOnly(false);


    }else{


            ui->plainTextEdit_2->setReadOnly(true);
    }
}

void Profile3::on_pushButton_clicked(){

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("D:/outputt.pdf");
    ui->plainTextEdit_2->print(&printer);

}

void Profile3::on_pushButton_2_clicked()
{
      QDialog w;

    QPrinter printer(QPrinter::HighResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setOutputFileName("D:/output.pdf");
           printer.setPageMargins(12, 16, 12, 20, QPrinter::Millimeter);
           printer.setFullPage(true);

           QPainter painter(&printer);

           double xscale = printer.pageRect().width() / double(w.width());
           double yscale = printer.pageRect().height() / double(w.height());
           double scale = qMin(xscale, yscale);
           painter.translate(printer.paperRect().center());
           painter.scale(scale, scale);
           painter.translate(-w.width()/ 2, -w.height()/ 2);
           w.render(&painter);
}

void Profile3::on_pushButton_4_clicked()
{
    QSqlDatabase Databas  = QSqlDatabase::database();
    Databas =   QSqlDatabase::addDatabase("QMYSQL", "SecConnection");
    Databas.setHostName("localhost") ;
    Databas.setUserName("root");
    Databas.setPassword("root");
    Databas.setDatabaseName("Clinic_Database");

    if(Databas.open()){
        qDebug() << "Database connected" ;
    }
    else{
        qDebug() << "Database not connected" ;

    }

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Result", "Are you sure? Note: After Clicking Changes will be Saved in Database?",
                                  QMessageBox::Yes|QMessageBox::No);

    if(reply==QMessageBox::Yes){
          QString text = ui->plainTextEdit_2->toPlainText();
          QSqlQuery *Diagonsis =  new QSqlQuery(Databas);
          Diagonsis->prepare(" UPDATE `patientsinfo` SET  DiagnosisDisease=CONCAT(ifnull(DiagnosisDisease, '')  , '', :text)   where  patientsinfo.PhoneNum = :Phonedb   ");
          Diagonsis->bindValue(":Phonedb",Phonedb);
              Diagonsis->bindValue(":text",text);
          if(!Diagonsis->exec()) {

               qDebug() <<Diagonsis->lastError() << text  ;

          }else {
                  qDebug() << text  ;

          }



    }else{

        qDebug() << "Error " ;
    }




}
