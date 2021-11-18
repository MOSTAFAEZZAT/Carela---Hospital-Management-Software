

#ifndef PROFILE3_H
#define PROFILE3_H
#include "mysqldatabase.h"

#include <QWidget>
#include <QWidget>
#include <QApplication>
#include <QtSql>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSignalMapper>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QSqlDriver>
#include <QVector>
#include <QString>
#include <QCheckBox>
#include <QStackedWidget>
#include <QtDesigner>
#include <QDesignerContainerExtension>
#include <QModelIndex>
#include <QProxyStyle>

namespace Ui {
class Profile3;
};

class Kitchen_Data{

public:

    QString MealCode;
    QString MealName;
    QString MealPrice="";
    int MealPrice1 =0;
    QString MealType;
    QTreeWidgetItem * itemm_CancelButton_From_Kitchen ;
    QVector <QString> KitechenItemPrice;
    QVector <QString> KitechenItemName;

    QString All_Added_ItemOfKitechen;
    QString KitchenTotalPrice="";
    QList<QTreeWidgetItem*> itemList_Kitechen;
    QPushButton * CancelButton_TreeWidget_2 =new QPushButton ;


};
class pharmacy{

private:

    int TotalPrice=0;
public:

    QString MedicineCode;
    QString MedicineName;
    QString MedicinePrice;
    int TotalPriceMedicine =0;
    QString MedicineType;
    QString MedicineAmount;
    QString MedicineTimeEntry;
    QString TotalPriceMedicine1 ;
    QTreeWidgetItem * itemm_CancelButton_From_TreeWidet_Medicine;
    QPushButton * CancelButton_TreeWidget_6 = new QPushButton("Cancel");

    int setTotalPrice(int globalTotalPrice){

        TotalPrice += globalTotalPrice ;
        return TotalPrice ;


    }
    int DeductTotalPrice(int globalTotalPrice){

        TotalPrice -= globalTotalPrice ;
        return TotalPrice;

    }

      int getTotalPrice(){

        return TotalPrice;
    }
    QString TotalPriceString(){

        QString Label_TotalPrice = QString::number(TotalPrice) ;
        return Label_TotalPrice;
    }

};

class Analysis_Data{

public:

    QString AnalysisCode;
    QString AnalysisName;
    QString AnalysisPrice;
    QString AnalysisType;
    QString AnalysisTimeEntry;
    QTreeWidgetItem * itemm_CancelButton_From_Analysis;
    QPushButton * CancelButton_treeWidget_Analysis = new QPushButton("Cancel");

    int TotalPriceAnalysis=0;


    QString All_Analysis_Added ;
    int Total_Analysis_Price;




};
class X_Ray{

public:

    QString X_RaysCode;
    QString X_RaysName;
    QString X_RaysType;
    QString X_RaysPrice;

};
class Profile3 : public QWidget
{
    Q_OBJECT

public:


    explicit Profile3(QWidget *parent = nullptr );

    Kitchen_Data Kitchen;
    pharmacy Medicine;
    Analysis_Data Analysis;

    QString Namedb ;
    QString Phonedb ;

    bool ViewProfile3();


    bool RetrievingMedicineData();
    bool Retrieving_Analysis_Data();
    bool Retrieving_Kitchen_Data();
    bool Retrieving_X_Rays_Data();



    bool Retrieving_Patient_MedicineData();
    bool Retrieving_Patient_Analysis_Data();
    bool Retrieving_Patient_Retrieving_Kitchen_Data();
    bool Retrieving_Patient__Rays_Data();

    QStringList visitTree(QTreeWidget * tree);
    void visitTree(QStringList list,QTreeWidgetItem * tree);

    ~Profile3();

private slots:

    void on_lineEdit_textChanged(const QString &arg1);

    void  Kitchen_DoubleClicked(QTreeWidgetItem *item,Kitchen_Data &Kitchen);
    void  Analysis_DoubleClicked(QTreeWidgetItem *item,Analysis_Data &Analysis);
    void  Medicine_DoubleClicked(QTreeWidgetItem *item,pharmacy &Medicine);

    //

    void on_pushButton_EnteringMedicine_clicked(bool checked);
    void on_lineEdit_destroyed();
    void on_lineEdit_selectionChanged();
    // Cancel Section

    void  Cancel_TreeWidget_Analysis(Analysis_Data &Analysis);
    void  Cancel_TreeWidget_Kitchen(Kitchen_Data &Kitchen );


    void Cancel_TreeWidget_Medicine (pharmacy &Medicine);


    void pushButton( Kitchen_Data &Kitchen);
    void on_pushButton_SavePatientMedicineItems_clicked();

    void on_pushButton_SavePatientKitchenItems_clicked();


    void on_Save_PatientAnalysisItems_clicked();




    void on_toolButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:


    Ui::Profile3 *ui;
    MySqlDatabase  connectDB1 ;
    QSqlTableModel * model;
    QTableView * view ;
    QSqlDatabase  mydb ;
    QVector <QString> AnalysisData;
    QCheckBox * Analysingcheckbox ;
    QCheckBox * Medicinecheckbox ;
    QCheckBox * Radiation_xRayscheckbox ;
    QCheckBox *FoodNDrinkscheckbox ;
    QString ID;
    QString PatientName;
    QString National_ID;
    QString PatientsAddress;
    QString Date_Time;
    QString PhoneNumber;
    QString Age;
    QString BloodPrint;
    QString consultant;
    QString DiagnosisDisease;
    QString Analysing;
    QString TotalPriceAnalysis;

    QString TotalPriceMedicine;
    QString Radiation_xRays	;
    QString Radiation_xRays_TotalPrice;
    QString FoodNDrinks	;
    QString FoodNDrinksTotalPrice;
    double TotalPrice =0;
    double TotalPriceAnalysis1 = 0 ;
    double TotalPriceKitchen  = 0 ;
    double TotalPriceRadiation = 0 ;

    QVector <QString> Analysis_ItemPrice;
    QVector <QString> Analysis_ItemName;
    QString All_Added_ItemOfAnalysis;
    QString AnalysisTotalPrice;


    QString MedicineDB;
    QVector <QString> Medicine_Prices_Vector;
    QVector <QString> Medicine_Name_Types_Vector;
    QString All_Added_ItemOfMedicine;
    QString MedicineTotalPrice;

    QVector <QString> X_Rays_Radiation_Prices_Vector;
    QVector <QString> X_Rays_Radiation_Types_Vector;
    QString All_Added_ItemOf_X_Rays_Radiation;
    QString X_Rays_Radiation_TotalPrice;
    int TotalMedicinePrice_Int=0;
    int TotalAnalysisPrice_Int=0;
    int TotalKitchenPrice_Int=0;
    int Total_X_Rays_Radiation_Price_Int=0;
    QTreeWidgetItem * item1_AddingItemstoTreeWidget ;

    QTreeWidgetItem * item1_AddingItemstoTreeWidget_3 ;
    QTreeWidgetItem * itemm_CancelButton_From_TreeWidet_5;
    QTreeWidgetItem * item1_AddingItemstoTreeWidget_5;

    QTreeWidgetItem * item1_AddingItemstoTreeWidget_7;
    QTreeWidgetItem * itemm_CancelButton_From_TreeWidet_8;

    QList<QTreeWidgetItem*> itemList_Analysis;
    QVector <QString> KitechenItemName;


};



class CustomTabStyle : public QProxyStyle  {
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption* option,
                           const QSize& size, const QWidget* widget) const {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
        }
        return s;
    }



    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const {
        if (element
                == CE_TabBarTabLabel) {
            if (const QStyleOptionTab* tab = qstyleoption_cast<const QStyleOptionTab*>(option)) {
                QStyleOptionTab opt(*tab);
                opt.shape = QTabBar::RoundedNorth;
                QProxyStyle::drawControl(element, &opt, painter, widget);
                return;
            }
        }
        QProxyStyle::drawControl(element, option, painter, widget);
    }
};



class MyTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit MyTreeWidget(QWidget *parent = nullptr) : QTreeWidget(parent)
    {

    }

    void DoSearch(QString term) {


        QList<QTreeWidgetItem *> clist = findItems(term,Qt::MatchContains | Qt::MatchRecursive, 1);

        auto sel = selectionModel();
        for (QTreeWidgetItem *item : clist) {
            QModelIndex index = indexFromItem(item, 1);
            sel->setCurrentIndex(index,  QItemSelectionModel::Select) ;
        }

    }

};


#endif // PROFILE3_H
