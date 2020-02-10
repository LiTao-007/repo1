#ifndef REGISTDIALOG_H
#define REGISTDIALOG_H

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

class RegistDialog : public QDialog
{
    Q_OBJECT
public:
    RegistDialog(QWidget* parent = nullptr);
    ~RegistDialog();

    QLabel *ID_Label;
    QLabel *nameLabel;
    QLabel *passwordLabel_1;
    QLabel *passwordLabel_2;
    QLineEdit *name_Edit;
    QLineEdit *nameID_Edit;
    QLineEdit *password_Edit_1;
    QLineEdit *password_Edit_2;
    QPushButton *regist_PB;

private:
    void MysqlConnect();
    QSqlDatabase regist_db;

private slots:
    void on_Register();


};

#endif // REGISTDIALOG_H
