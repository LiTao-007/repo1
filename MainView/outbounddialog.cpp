#include "outbounddialog.h"

OutboundDialog::OutboundDialog(QWidget *parent)
    :QDialog(parent)
{
    setWindowTitle("出库设备信息"); //窗口名称
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
    resize(250,350);

    QLabel *deviceID    = new QLabel("设备编号");
    QLabel *deviceName  = new QLabel("设备名称");
    QLabel *OutboundDec   = new QLabel("出库描述");

    deviceID_Edit   = new QLineEdit;
    deviceName_Edit = new QLineEdit;
    OutboundDec_Edit  = new QTextEdit;
    setOutbound_PB   = new QPushButton("确认");

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(deviceID,0,0);
    gridLayout->addWidget(deviceID_Edit,0,1);

    gridLayout->addWidget(deviceName,1,0);
    gridLayout->addWidget(deviceName_Edit,1,1);

    gridLayout->addWidget(OutboundDec,2,0);
    gridLayout->addWidget(OutboundDec_Edit,2,1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(gridLayout);
    vLayout->addStretch();
    vLayout->addWidget(setOutbound_PB);
    vLayout->addStretch();
    setLayout(vLayout);
}

OutboundDialog::~OutboundDialog(){

}
