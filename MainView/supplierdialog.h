#ifndef SUPPLIERDIALOG_H
#define SUPPLIERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class SupplierDialog : public QDialog
{
    Q_OBJECT
public:
    SupplierDialog(QWidget *parent = nullptr);
    ~SupplierDialog();

    QPushButton *setSupplier_PB;
    QLineEdit *supplierID_Edit; //id
    QLineEdit *supplierName_Edit; //name
    QLineEdit *supplierPerson_Edit; // person
    QLineEdit *supplierTel_Edit; //tel

};

#endif // SUPPLIERDIALOG_H
