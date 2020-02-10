#ifndef OUTBOUNDDIALOG_H
#define OUTBOUNDDIALOG_H

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

class OutboundDialog : public QDialog
{
    Q_OBJECT
public:
    OutboundDialog(QWidget *parent = nullptr);
    ~OutboundDialog();

    QLineEdit *deviceID_Edit;
    QLineEdit *deviceName_Edit;
    QTextEdit *OutboundDec_Edit;

    QPushButton *setOutbound_PB;

};

#endif // OUTBOUNDDIALOG_H
