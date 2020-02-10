#include "inbounddialog.h"

InboundDialog::InboundDialog(QWidget *parent)
    :QDialog(parent)
{
    setWindowTitle("入库设备信息"); //窗口名称
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
    resize(250,400);

    QLabel *deviceID    = new QLabel("设备编号");
    QLabel *deviceName  = new QLabel("设备名称");
    QLabel *deviceModel = new QLabel("设备型号");
    QLabel *deviceType  = new QLabel("设备类型");
    QLabel *deviceDec   = new QLabel("设备描述");
    QLabel *deviceMfrs  = new QLabel("供应商名称");

    deviceID_Edit   = new QLineEdit;
    deviceName_Edit = new QLineEdit;
    deviceModel_Edit = new QLineEdit;
    deviceType_Edit = new QLineEdit;
    deviceMfrs_Edit = new QLineEdit;
    deviceDec_Edit  = new QTextEdit;
    setInbound_PB   = new QPushButton("确认");

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(deviceID,0,0);
    gridLayout->addWidget(deviceID_Edit,0,1);

    gridLayout->addWidget(deviceName,1,0);
    gridLayout->addWidget(deviceName_Edit,1,1);

    gridLayout->addWidget(deviceModel,2,0);
    gridLayout->addWidget(deviceModel_Edit,2,1);

    gridLayout->addWidget(deviceType,3,0);
    gridLayout->addWidget(deviceType_Edit,3,1);

    gridLayout->addWidget(deviceMfrs,4,0);
    gridLayout->addWidget(deviceMfrs_Edit,4,1);

    gridLayout->addWidget(deviceDec,5,0);
    gridLayout->addWidget(deviceDec_Edit,5,1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(gridLayout);
    vLayout->addStretch();
    vLayout->addWidget(setInbound_PB);
    setLayout(vLayout);
}

InboundDialog::~InboundDialog(){

}
