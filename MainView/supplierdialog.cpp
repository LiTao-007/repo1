#include "supplierdialog.h"

SupplierDialog::SupplierDialog(QWidget *parent)
    :QDialog(parent)
{ 
    setWindowTitle("供应商添加"); //窗口名称
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
    resize(180,180);

    setSupplier_PB = new QPushButton("确认");
    QLabel *supplierID = new QLabel("供应商编号");
    supplierID_Edit = new QLineEdit;
    QLabel *supplierName = new QLabel("供应商名称");
    supplierName_Edit = new QLineEdit;
    QLabel *supplierPerson = new QLabel("联系人");
    supplierPerson_Edit = new QLineEdit;
    QLabel *supplierTel = new QLabel("电话");
    supplierTel_Edit = new QLineEdit;

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(supplierID,0,0);
    gridLayout->addWidget(supplierID_Edit,0,1);
    gridLayout->addWidget(supplierName,1,0);
    gridLayout->addWidget(supplierName_Edit,1,1);
    gridLayout->addWidget(supplierPerson,2,0);
    gridLayout->addWidget(supplierPerson_Edit,2,1);
    gridLayout->addWidget(supplierTel,3,0);
    gridLayout->addWidget(supplierTel_Edit,3,1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(gridLayout);
    vLayout->addStretch();
    vLayout->addWidget(setSupplier_PB);
    setLayout(vLayout);
}

SupplierDialog::~SupplierDialog()
{

}
