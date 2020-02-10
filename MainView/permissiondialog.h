#ifndef PERMISSIONDIALOG_H
#define PERMISSIONDIALOG_H
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
#include <QComboBox>
#include <QCheckBox>

class PermissionDialog : public QDialog
{
    Q_OBJECT
public:
    PermissionDialog(QSqlDatabase Mysqldb, QWidget *parent = nullptr);
    ~PermissionDialog();

    QSqlDatabase mydb;
    QPushButton *setPermission_PB;
    QLineEdit *nameID_Edit;
    QCheckBox *checkRead;
    QCheckBox *checkWrite;



private slots:

};

#endif // PERMISSIONDIALOG_H
