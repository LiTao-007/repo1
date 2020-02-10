#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTableView>
#include <QFrame>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QHeaderView>
#include <QDateEdit>
#include <QDesktopWidget>
#include <QtCore>
#include <QGuiApplication>
#include <QRect>
#include <QScreen>
#include <QFileDialog>
#include <QList>
#include <QVariant>
#include <QTableWidget>
#include <QStyle>

#include "logindialog.h"
#include "permissiondialog.h"
#include "supplierdialog.h"
#include "inbounddialog.h"
#include "outbounddialog.h"
#include "excleedit.h"

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

    QStackedWidget *stackWidget; //堆栈窗体管理，多界面切换

    //导航栏
    QAction *mainSheet_action;
    QAction *user_action;
    QAction *supplier_action;
    QAction *inbound_action;
    QAction *outbound_action;
    QAction *device_action;

    //工具栏
    QAction *login_Action;

    //用户界面控件
    QTableView *userTableView;  //用户显示界面
    QPushButton *Permission_pB; //权限设置
    QLineEdit *userName_Edit;   //用户名
    QLineEdit *userID_Edit;     //员工编号
    QPushButton *outUser_PB;    //用户数据导出
    QPushButton *batchInputUser_PB; //用户信息批量导入

    //供应商界面控件
    QTableView *supplierTableView; //供应商显示界面
    QPushButton *supplierAdd_pB;
    QLineEdit *supplierID_Edit;
    QLineEdit *supplierName_Edit;
    QPushButton *outSupplier_PB;  //供应商数据导出
    QPushButton *batchInputSupplier_PB;

    //设备信息界面控件
    QTableView *deviceTableView;  //设备显示界面
    QLineEdit *deviceID_Edit;
    QLineEdit *deviceName_Edit;
    QLineEdit *deviceModel_Edit;
    QLineEdit *deviceType_Edit;
    QLineEdit *deviceMfrsName_Edit;
    QPushButton *outDevice_PB;  //供应商数据导出

    //入库信息界面控件
    QTableView *inboundTableView;  //入库显示界面
    QPushButton *inboundDevAdd_pB;
    QLineEdit *inboundDevID_Edit;
    QLineEdit *inboundDevName_Edit;
    QLineEdit *inboundUserName_Edit;
    QLineEdit *inboundDevMfrsName_Edit;
    QDateEdit *inboundStartDate_Edit;
    QDateEdit *inboundEndDate_Edit;
    QPushButton *outInbound_PB;  //供应商数据导出
    QPushButton *batchInputInbound_PB;

    //出库信息界面控件
    QTableView *outboundTableView;  //出库显示界面
    QPushButton *outboundDevAdd_pB;
    QLineEdit *outboundDevID_Edit;
    QLineEdit *outboundDevName_Edit;
    QLineEdit *outboundUserName_Edit;
    QLineEdit *outboundDevMfrsName_Edit;
    QDateEdit *outboundStartDate_Edit;
    QDateEdit *outboundEndDate_Edit;
    QPushButton *outOutbound_PB;  //供应商数据导出
    QPushButton *batchInputOutbound_PB;

private:
    QSqlTableModel* suppliertableModel;
    QSqlTableModel* usertableModel;
    QSqlTableModel* devicetableModel;
    QSqlTableModel* inboundtableModel;
    QSqlTableModel* outboundtableModel;

    //登录、权限设置和添加界面对象
    LoginDialog         *LoginView;         //登录
    PermissionDialog    *PermissionView;    //权限设置
    SupplierDialog      *SupplierAddView;   //供应商
    InboundDialog       *InboundAddView;    //入库添加
    OutboundDialog      *OutboundAddView;   //出库添加

    QSqlDatabase mydb;

    void CreatMenu();           //菜单栏操作
    void CreatTool();           //工具栏操作
    void CreatToolBar();        //导航栏操作
    void CreatStackWidget();    //多界面切换控制器
    void MysqlConnect();        //数据库连接

    QWidget* Creat_MainView();          //主页界面
    QWidget* Creat_SupplierView();      //供应商界面
    QWidget* Creat_UserManageView();    //用户界面
    QWidget* Creat_DeviceView();        //设备界面
    QWidget* Creat_InboundView();       //入库界面
    QWidget* Creat_OutboundView();      //出库界面

private slots:
    void on_SwitchPage();               //功能界面切换
    void on_TimeUpdateView();           //定时更新界面信息

    void on_PermissionView();           //用户权限设置
    void on_InsertPermissionToDb();     //权限设置插入数据库
    void on_OutUserInfo();              //用户信息导出
    void on_UserSearch();               //用户查询
    void on_BatchInputUserInfo();       //用户信息批量导入

    void on_SupplierSearch();           //供应商查询
    void on_SupplierAddView();          //供应商添加界面
    void on_InsertSupplierToDb();       //供应商信息插入数据库
    void on_OutSupplierInfo();          //供应商信息导出
    void on_BatchInputSupplierInfo();   //供应商信息批量导入

    void on_DeviceSearch();             //设备信息查询
    void on_OutDeviceInfo();            //设备信息导出

    void on_InboundSearch();            //入库信息查询
    void on_InboundAddView();           //入库设备添加界面
    void on_InsertInboundDevToDb();     //入库信息插入数据库
    void on_OutInboundInfo();           //入库信息导出
    void on_BatchInputInboundInfo();    //入库信息批量导入

    void on_OutboundSearch();           //出库信息查询
    void on_OutboundAddView();          //出库设备添加界面
    void on_InsertOutboundDevToDb();    //出库信息插入数据库
    void on_OutOutboundInfo();          //出库信息导出
    void on_BatchInputOutboundInfo();   //出库信息批量导入
};

#endif // MAINVIEW_H
