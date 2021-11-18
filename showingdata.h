#ifndef SHOWINGDATA_H
#define SHOWINGDATA_H

#include <QWidget>

#include <QtGui>
#include <QModelIndex>
#include <QObject>
#include <QPushButton>
#include <QDialog>
#include <QSignalMapper>
#include <QSqlTableModel>
#include <QTableView>
#include <QApplication>
#include <QtSql>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDebug>
#include <QAbstractItemView>
#include <QtCore>
#include <QtGui>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlDriver>
#include <QAbstractItemView>
 #include <iostream>
#include <QStandardItemModel>
#include <QComboBox>
#include <vector>
#include <string>
#include "profile3.h"
namespace Ui {
class ShowingData;
}

class ShowingData : public QWidget
{
    Q_OBJECT

public:
    explicit ShowingData(QWidget *parent = nullptr);
    ~ShowingData();

private slots:
    void on_pushButton_2_clicked();
    void getDate( );
//     void viewprofile2();




  void on_dateEdit_5_dateChanged(const QDate &date);

  void on_pushButton_clicked();

private:
    Ui::ShowingData *ui;
    Profile3 *profile3;
    QString Birthdate;

};

#endif // SHOWINGDATA_H
