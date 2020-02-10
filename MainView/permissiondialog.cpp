#include "permissiondialog.h"

PermissionDialog::PermissionDialog(QSqlDatabase Mysqldb,QWidget *parent)
    :QDialog(parent)
{
    setWindowTitle("权限设置"); //窗口名称
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
    resize(180,180);
    mydb = Mysqldb;
    QLabel *nameID = new QLabel("员工编号");
    nameID_Edit = new QLineEdit;
    setPermission_PB = new QPushButton("确认");
    QLabel *permissionDec = new QLabel("权限选择：");
    checkRead = new QCheckBox("只读");
    checkWrite = new QCheckBox("读写");
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(nameID,0,0);
    gridLayout->addWidget(nameID_Edit,0,1);
    gridLayout->addWidget(permissionDec,1,0);
    gridLayout->addWidget(checkRead,2,1);
    gridLayout->addWidget(checkWrite,3,1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(gridLayout);
    vLayout->addStretch();
    vLayout->addWidget(setPermission_PB);
    setLayout(vLayout);
}

PermissionDialog::~PermissionDialog(){}
