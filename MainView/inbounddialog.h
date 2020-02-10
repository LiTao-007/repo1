#ifndef INBOUNDDIALOG_H
#define INBOUNDDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
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

class InboundDialog : public QDialog
{
    Q_OBJECT
public:
    InboundDialog(QWidget *parent = nullptr);
    ~InboundDialog();

    QLineEdit *deviceID_Edit;
    QLineEdit *deviceName_Edit;
    QLineEdit *deviceModel_Edit;
    QLineEdit *deviceType_Edit;
    QTextEdit *deviceDec_Edit;
    QLineEdit *deviceMfrs_Edit;

    QPushButton *setInbound_PB;

};

#endif // INBOUNDDIALOG_H
