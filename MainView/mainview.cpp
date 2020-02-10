#include "mainview.h"
#include "ui_mainview.h"

MainView::MainView(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("台账管理系统");
#if 0
    QList<QScreen *> list_screen = QGuiApplication::screens();
    resize(list_screen.at(0)->geometry().size());
#endif
    MysqlConnect();
    CreatMenu();
    CreatTool();
    CreatToolBar();
    CreatStackWidget();

    QTimer *timer   = new QTimer(this);
    PermissionView  = new PermissionDialog(mydb,this);
    SupplierAddView = new SupplierDialog(this);
    InboundAddView  = new InboundDialog(this);
    OutboundAddView = new OutboundDialog(this);
    timer->start(3000);

    //槽函数
    //界面切换bind
    connect(mainSheet_action,&QAction::triggered,this,&MainView::on_SwitchPage);
    connect(user_action,&QAction::triggered,this,&MainView::on_SwitchPage);
    connect(supplier_action,&QAction::triggered,this,&MainView::on_SwitchPage);
    connect(inbound_action,&QAction::triggered,this,&MainView::on_SwitchPage);
    connect(outbound_action,&QAction::triggered,this,&MainView::on_SwitchPage);
    connect(device_action,&QAction::triggered,this,&MainView::on_SwitchPage);

    connect(timer,SIGNAL(timeout()),this,SLOT(on_TimeUpdateView()));                    //定时任务
    connect(Permission_pB,SIGNAL(clicked(bool)),this,SLOT(on_PermissionView()));        //用户权限
    connect(supplierAdd_pB,SIGNAL(clicked(bool)),this,SLOT(on_SupplierAddView()));      //供应商添加
    connect(inboundDevAdd_pB,SIGNAL(clicked(bool)),this,SLOT(on_InboundAddView()));     //入库添加
    connect(outboundDevAdd_pB,SIGNAL(clicked(bool)),this,SLOT(on_OutboundAddView()));   //出库添加

    //数据导出
    connect(outUser_PB,SIGNAL(clicked(bool)),this,SLOT(on_OutUserInfo()));          //用户信息导出
    connect(outSupplier_PB,SIGNAL(clicked(bool)),this,SLOT(on_OutSupplierInfo()));  //供应商信息导出
    connect(outDevice_PB,SIGNAL(clicked(bool)),this,SLOT(on_OutDeviceInfo()));      //设备信息导出
    connect(outInbound_PB,SIGNAL(clicked(bool)),this,SLOT(on_OutInboundInfo()));    //入库信息导出
    connect(outOutbound_PB,SIGNAL(clicked(bool)),this,SLOT(on_OutOutboundInfo()));  //出库信息导出

    //数据导入
    connect(batchInputUser_PB,SIGNAL(clicked(bool)),this,SLOT(on_BatchInputUserInfo()));
    connect(batchInputSupplier_PB,SIGNAL(clicked(bool)),this,SLOT(on_BatchInputSupplierInfo()));
    connect(batchInputInbound_PB,SIGNAL(clicked(bool)),this,SLOT(on_BatchInputInboundInfo()));
    connect(batchInputOutbound_PB,SIGNAL(clicked(bool)),this,SLOT(on_BatchInputOutboundInfo()));



}

MainView::~MainView()
{
    mydb.close();
}

//mainwindow 窗口菜单栏编辑
void MainView::CreatMenu(){
    QMenu *fileMenu = menuBar()->addMenu("文件"); //添加文件菜单项
    QMenu *editMenu = menuBar()->addMenu("编辑"); //添加编辑菜单项
    QMenu *checkMenu = menuBar()->addMenu("查看");//添加查看菜单项
    QMenu *helpMenu = menuBar()->addMenu("帮助"); //添加帮助菜单项
}

//mainwindow 窗口工具栏编辑
void MainView::CreatTool(){

    QToolBar *loginToolBar = addToolBar("登录");//添加登录工具条
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); //填充空白
    loginToolBar->addWidget(spacer);

    login_Action = new QAction("登录/注册", this);//新建登录动作
    loginToolBar->addAction(login_Action);
    loginToolBar->setMovable(false);// 设置工具栏不可移动

    LoginView = new LoginDialog(this);
    connect(login_Action,&QAction::triggered,LoginView,&QDialog::show);
}

//mainwindow 窗口导航栏栏操作
void MainView::CreatToolBar(){
  QToolBar *toolbar = new QToolBar("导航",this);
  addToolBar(Qt::LeftToolBarArea,toolbar);  //导航窗口在左边
  toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); //导航框中文字在图标下面

  /*使用空白的QWidget界面设置其随窗口变化而变化，来调整导航栏中图标随窗口变化而变化*/
  QWidget* spacer0 = new QWidget();
  spacer0->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QWidget* spacer1 = new QWidget();
  spacer1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QWidget* spacer2 = new QWidget();
  spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QWidget* spacer3 = new QWidget();
  spacer3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QWidget* spacer4 = new QWidget();
  spacer4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QWidget* spacer5 = new QWidget();
  spacer5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  const QIcon mainIcon = QIcon::fromTheme("user",QIcon(":/image/main.jpg"));
  mainSheet_action = new QAction(mainIcon,"主页",this);
  toolbar->addAction(mainSheet_action); //在导航栏中添加选项按钮

  toolbar->addWidget(spacer0);
  const QIcon userIcon = QIcon::fromTheme("user",QIcon(":/image/user.jpg"));
  user_action  =  new QAction(userIcon,"用户管理",this);
  toolbar->addAction(user_action); //在导航栏中添加选项按钮

  toolbar->addWidget(spacer1);
  const QIcon mfrs = QIcon::fromTheme("mfrs",QIcon(":/image/mfrs.jpg"));
  supplier_action  =  new QAction(mfrs,"供应商管理",this);
  toolbar->addAction(supplier_action);

  toolbar->addWidget(spacer2);
  const QIcon inbound = QIcon::fromTheme("inbound",QIcon(":/image/inbound.png"));
  inbound_action  =  new QAction(inbound,"入库管理",this);
  toolbar->addAction(inbound_action);

  toolbar->addWidget(spacer3);
  const QIcon outbound = QIcon::fromTheme("outbound",QIcon(":/image/outbound.png"));
  outbound_action  =  new QAction(outbound,"出库管理",this);
  toolbar->addAction(outbound_action);


  // toolBar is a pointer to an existing toolbar
  toolbar->addWidget(spacer4);
  const QIcon device = QIcon::fromTheme("device",QIcon(":/image/device.jpg"));
  device_action  =  new QAction(device,"设备管理",this);
  toolbar->addAction(device_action);

  toolbar->addWidget(spacer5);
  toolbar->setMovable(false);//导航窗口不能移动
}

//多界面切换控制器
void MainView::CreatStackWidget(){
    stackWidget = new QStackedWidget;
    QWidget *main_Sheet = Creat_MainView(); //主页界面
    QWidget *lable_user = Creat_UserManageView();//用户管理界面
    QWidget *lable_supplier = Creat_SupplierView();//供应商管理界面
    QWidget *lable_inbound = Creat_InboundView(); //入库管理界面
    QWidget *lable_outbound = Creat_OutboundView();//出库管理界面
    QWidget *lable_devic = Creat_DeviceView(); //设备信息界面

    stackWidget->addWidget(main_Sheet);
    stackWidget->addWidget(lable_user);
    stackWidget->addWidget(lable_supplier);
    stackWidget->addWidget(lable_inbound);
    stackWidget->addWidget(lable_outbound);
    stackWidget->addWidget(lable_devic);

    setCentralWidget(stackWidget);
}

//主页界面
QWidget* MainView::Creat_MainView(){
    QWidget *mainPage = new QWidget;

    QLabel *deviceName = new QLabel("设备数量");
    QString nameStyle="";
    nameStyle.append("min-width: 64px; max-width:64px");
    deviceName->setStyleSheet(nameStyle);
    deviceName->setAlignment(Qt::AlignCenter); //字体居中
    QFont qfont("Microsoft YaHei", 10, 75);
    deviceName->setFont(qfont);

    QLabel *deviceNum  = new QLabel();  //显示数量
    QString deviceStyle="";
    deviceStyle.append("min-width: 64px; min-height: 64px;");  //最小 宽度和高度
    deviceStyle.append("max-width:64px; max-height: 64px;");   //最大 宽度和高度
    deviceStyle.append("border-radius: 32px;  border:1px solid black;"); //定义边界半径  边框宽度
    deviceStyle.append("background:red");  //设置背景颜色
    deviceNum->setStyleSheet(deviceStyle);
    deviceNum->setAlignment(Qt::AlignCenter);
    deviceNum->setText("100");
    deviceNum->setFont(qfont);

    QVBoxLayout *layoutv1 = new QVBoxLayout();//垂直布局
    layoutv1->addWidget(deviceName);
    layoutv1->addWidget(deviceNum);
    layoutv1->addStretch();

    mainPage->setLayout(layoutv1);
    return mainPage;
}

//用户管理界面
QWidget* MainView::Creat_UserManageView(){
    QWidget *userPage = new QWidget;
    QLabel *titleLabel = new QLabel("用户信息");
    QFont qfont("Microsoft YaHei", 10, 75);
    titleLabel->setFont(qfont);
    Permission_pB = new QPushButton("权限设置");
    Permission_pB->setEnabled(false);
    outUser_PB = new QPushButton("导出");
    outUser_PB->setEnabled(false);
    batchInputUser_PB = new QPushButton("批量导入");
    batchInputUser_PB->setEnabled(false);

    QHBoxLayout *layout1 = new QHBoxLayout();  //水平布局
    layout1->addWidget(titleLabel);
    layout1->addStretch();
    layout1->addWidget(Permission_pB);
    layout1->addWidget(batchInputUser_PB);
   // layout1->addStretch();
    layout1->addWidget(outUser_PB);

    QHBoxLayout *layout2 = new QHBoxLayout();
    QLabel * user_ID = new QLabel("员工编号");
    userID_Edit  = new QLineEdit();
    QLabel * user_Name = new QLabel("用户名");
    userName_Edit = new QLineEdit();
    layout2->addWidget(user_ID);
    layout2->addWidget(userID_Edit);
    layout2->addStretch();
    layout2->addWidget(user_Name);
    layout2->addWidget(userName_Edit);
    layout2->addStretch();
    layout2->addStretch();
    layout2->addStretch();

    QPushButton *userSearch_pB = new QPushButton("查询");
    connect(userSearch_pB,SIGNAL(clicked(bool)),this,SLOT(on_UserSearch()));

    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addStretch();
    layout3->addWidget(userSearch_pB);

    QVBoxLayout *layoutv1 = new QVBoxLayout();//垂直布局
    layoutv1->addLayout(layout2);
    layoutv1->addLayout(layout3);
    QFrame *qframe = new QFrame;
    qframe->setFrameStyle(QFrame::StyledPanel);
    qframe->setLayout(layoutv1);


    usertableModel = new QSqlTableModel(userPage,this->mydb);//绑定数据库
    usertableModel->setTable("v_user");
    usertableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    usertableModel->insertColumn(2);
    usertableModel->setHeaderData(0,Qt::Horizontal,"用户编号");
    usertableModel->setHeaderData(1,Qt::Horizontal,"用户名");
    //usertableModel->setHeaderData(2,Qt::Horizontal,"联系电话");
    usertableModel->setHeaderData(2,Qt::Horizontal,"用户权限");
    usertableModel->setHeaderData(3,Qt::Horizontal,"操作");
    usertableModel->select(); //选取整个表的所有行

    userTableView = new QTableView(this);
    userTableView->setModel(usertableModel);
    //userTableView->verticalHeader()->setVisible(false);//隐藏列表头
    //userTableView->horizontalHeader()->setHighlightSections(false); //取消表头的在选中单元格时的高亮状态
    userTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //表格不可编辑

    QVBoxLayout *layoutv= new QVBoxLayout;          //垂直布局
    layoutv->addLayout(layout1);
    layoutv->addWidget(qframe);
    layoutv->addWidget(userTableView);
    userPage->setLayout(layoutv);
    return userPage;
}

//供应商管理界面
QWidget* MainView::Creat_SupplierView(){
    QWidget *supplierPage = new QWidget;

    QLabel *titleLabel = new QLabel("供应商信息");
    QFont qfont("Microsoft YaHei", 10, 75);
    titleLabel->setFont(qfont);
    outSupplier_PB = new QPushButton("导出");
    outSupplier_PB->setEnabled(false);
    supplierAdd_pB = new QPushButton("添加");
    supplierAdd_pB->setEnabled(false);
    batchInputSupplier_PB = new QPushButton("批量导入");
    batchInputSupplier_PB->setEnabled(false);

    QHBoxLayout *layout1 = new QHBoxLayout();  //水平布局
    //layout1->addWidget(titleLabel,0,Qt::AlignTop);//顶部
    layout1->addWidget(titleLabel);
    layout1->addStretch();
    layout1->addWidget(supplierAdd_pB);
    layout1->addWidget(batchInputSupplier_PB);
    layout1->addWidget(outSupplier_PB);
    //layout1->addWidget(add_pB,0,Qt::AlignTop);

    QHBoxLayout *layout2 = new QHBoxLayout();
    QLabel *supplier_ID = new QLabel("供应商编号");
    supplierID_Edit  = new QLineEdit();
    QLabel *supplier_Name = new QLabel("供应商名称");
    supplierName_Edit = new QLineEdit();
    layout2->addWidget(supplier_ID);
    layout2->addWidget(supplierID_Edit);
    layout2->addStretch();
    layout2->addWidget(supplier_Name);
    layout2->addWidget(supplierName_Edit);
    layout2->addStretch();
    layout2->addStretch();
    layout2->addStretch();

    QPushButton *supplierSearch_pB = new QPushButton("查询");
    connect(supplierSearch_pB,SIGNAL(clicked(bool)),this,SLOT(on_SupplierSearch()));
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addStretch();
    layout3->addWidget(supplierSearch_pB);

    QVBoxLayout *layoutv1 = new QVBoxLayout();//垂直布局
    layoutv1->addLayout(layout2);
    layoutv1->addLayout(layout3);
    QFrame *qframe = new QFrame;
    qframe->setFrameStyle(QFrame::StyledPanel);
    qframe->setLayout(layoutv1);

    suppliertableModel = new QSqlTableModel(supplierPage,this->mydb);//绑定数据库
    suppliertableModel->setTable("tb_device_mfrs");
    suppliertableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    suppliertableModel->setHeaderData(0,Qt::Horizontal,"供应商ID");
    suppliertableModel->setHeaderData(1,Qt::Horizontal,"供应商名称");
    suppliertableModel->setHeaderData(2,Qt::Horizontal,"联系人");
    suppliertableModel->setHeaderData(3,Qt::Horizontal,"联系电话");
    suppliertableModel->select(); //选取整个表的所有行

    supplierTableView = new QTableView(this);
    supplierTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应窗口
    supplierTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    supplierTableView->setModel(suppliertableModel);
    supplierTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //表格不可编辑

    QVBoxLayout *layoutv= new QVBoxLayout;//垂直布局
    layoutv->addLayout(layout1);
    layoutv->addWidget(qframe);
    layoutv->addWidget(supplierTableView);

    supplierPage->setLayout(layoutv);
    return supplierPage;
}

//设备管理界面
QWidget* MainView::Creat_DeviceView(){
    QWidget *devicePage = new QWidget;
    QLabel *titleLabel = new QLabel("设备信息");
    QFont qfont("Microsoft YaHei", 10, 75);
    titleLabel->setFont(qfont);
    outDevice_PB = new QPushButton("导出");
    outDevice_PB->setEnabled(false);
    QHBoxLayout *layout1 = new QHBoxLayout();  //水平布局
    layout1->addWidget(titleLabel);
    layout1->addStretch();
    layout1->addWidget(outDevice_PB);

    QLabel *device_ID       = new QLabel("设备编号");
    deviceID_Edit           = new QLineEdit();
    QLabel *device_Name     = new QLabel("设备名称");
    deviceName_Edit         = new QLineEdit();
    QLabel *device_Model    = new QLabel("设备型号");
    deviceModel_Edit        = new QLineEdit();
    QLabel *device_Type     = new QLabel("设备类型");
    deviceType_Edit         = new QLineEdit();
    QLabel *device_MfrsName = new QLabel("设备厂商");
    deviceMfrsName_Edit     = new QLineEdit();

    QPushButton *search_PB  = new QPushButton("查询");
    connect(search_PB,SIGNAL(clicked(bool)),this,SLOT(on_DeviceSearch()));

    QHBoxLayout *layout2 = new QHBoxLayout();  //水平布局
    layout2->addWidget(device_ID);
    layout2->addWidget(deviceID_Edit);
    layout2->addStretch();
    layout2->addWidget(device_Name);
    layout2->addWidget(deviceName_Edit);
    layout2->addStretch();
    layout2->addWidget(device_Model);
    layout2->addWidget(deviceModel_Edit);
  //layout2->addStretch();
  //layout2->addWidget(device_Type);
  //layout2->addWidget(Type_Edit);

    QHBoxLayout *layout3 = new QHBoxLayout();  //水平布局
    layout3->addWidget(device_Type);
    layout3->addWidget(deviceType_Edit);
    layout3->addStretch();
    layout3->addWidget(device_MfrsName);
    layout3->addWidget(deviceMfrsName_Edit);
    layout3->addStretch();
    layout3->addStretch();
    layout3->addWidget(search_PB);

    QVBoxLayout *layoutv1 = new QVBoxLayout(); //垂直布局
    layoutv1->addLayout(layout2);
    layoutv1->addLayout(layout3);
    QFrame *qframe = new QFrame;
    qframe->setFrameStyle(QFrame::StyledPanel);
    qframe->setLayout(layoutv1);

    devicetableModel = new QSqlTableModel(devicePage,mydb);
    devicetableModel->setTable("v_device");
    devicetableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    devicetableModel->setHeaderData(0,Qt::Horizontal,"设备编号");
    devicetableModel->setHeaderData(1,Qt::Horizontal,"设备名称");
    devicetableModel->setHeaderData(2,Qt::Horizontal,"设备型号");
    devicetableModel->setHeaderData(3,Qt::Horizontal,"设备类型");
    devicetableModel->setHeaderData(4,Qt::Horizontal,"设备描述");
    devicetableModel->setHeaderData(5,Qt::Horizontal,"设备厂商");
    devicetableModel->select();

    deviceTableView = new QTableView(this);
    deviceTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    deviceTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    deviceTableView->setModel(devicetableModel);
    deviceTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //表格不可编辑

    QVBoxLayout *layoutv= new QVBoxLayout;//垂直布局
    layoutv->addLayout(layout1);
    layoutv->addWidget(qframe);
    layoutv->addWidget(deviceTableView);

    devicePage->setLayout(layoutv);
    return devicePage;
}

//入库管理界面
QWidget* MainView::Creat_InboundView(){
    QWidget* inboundPage = new QWidget;

    QLabel* titleLabel = new QLabel("入库信息");
    QFont qfont("Microsoft YaHei", 10, 75);
    titleLabel->setFont(qfont);
    outInbound_PB = new QPushButton("导出");
    outInbound_PB->setEnabled(false);
    inboundDevAdd_pB = new QPushButton("添加");
    inboundDevAdd_pB->setEnabled(false);
    batchInputInbound_PB = new QPushButton("批量导入");
    batchInputInbound_PB->setEnabled(false);

    QHBoxLayout *layout1 = new QHBoxLayout();//水平
    layout1->addWidget(titleLabel);
    layout1->addStretch();
    layout1->addWidget(inboundDevAdd_pB);
    layout1->addWidget(batchInputInbound_PB);
    layout1->addWidget(outInbound_PB);

    QLabel *device_ID       = new QLabel("设备编号");
    inboundDevID_Edit       = new QLineEdit();
    QLabel *device_Name     = new QLabel("设备名称");
    inboundDevName_Edit     = new QLineEdit();
    QLabel *User_Name       = new QLabel("操作员工");
    inboundUserName_Edit    = new QLineEdit();
    QLabel *device_MfrsName = new QLabel("设备厂商");
    inboundDevMfrsName_Edit = new QLineEdit();
    QLabel *inbound_Time    = new QLabel("入库时间");
    inboundStartDate_Edit   = new QDateEdit();
    QLabel *To   = new QLabel("至");
    inboundEndDate_Edit     = new QDateEdit(QDate::currentDate()); //日历 并显示当前时间
    inboundStartDate_Edit->setCalendarPopup(true);
    inboundEndDate_Edit->setCalendarPopup(true);
    QPushButton *search_PB  = new QPushButton("查询");
    connect(search_PB,SIGNAL(clicked(bool)),this,SLOT(on_InboundSearch()));

    QHBoxLayout *layout2    = new QHBoxLayout();//水平
    layout2->addWidget(device_ID);
    layout2->addWidget(inboundDevID_Edit);
    layout2->addStretch();
    layout2->addWidget(device_Name);
    layout2->addWidget(inboundDevName_Edit);
    layout2->addStretch();
    layout2->addWidget(User_Name);
    layout2->addWidget(inboundUserName_Edit);

    QHBoxLayout *layout3    = new QHBoxLayout();//水平
    layout3->addWidget(device_MfrsName);
    layout3->addWidget(inboundDevMfrsName_Edit);
    layout3->addStretch();
    layout3->addWidget(inbound_Time);
    layout3->addWidget(inboundStartDate_Edit);
    layout3->addWidget(To);
    layout3->addWidget(inboundEndDate_Edit);
    layout3->addStretch();
    layout3->addStretch();
    layout3->addWidget(search_PB);

    QVBoxLayout *layoutv1 = new QVBoxLayout(); //垂直布局
    layoutv1->addLayout(layout2);
    layoutv1->addLayout(layout3);
    QFrame *qframe = new QFrame;
    qframe->setFrameStyle(QFrame::StyledPanel);
    qframe->setLayout(layoutv1);

    inboundtableModel = new QSqlTableModel(inboundPage,mydb);
    inboundtableModel->setTable("v_inbound");
    inboundtableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    inboundtableModel->setHeaderData(0,Qt::Horizontal,"设备编号");
    inboundtableModel->setHeaderData(1,Qt::Horizontal,"设备名称");
    inboundtableModel->setHeaderData(2,Qt::Horizontal,"操作员工");
    inboundtableModel->setHeaderData(3,Qt::Horizontal,"设备厂商");
    inboundtableModel->setHeaderData(4,Qt::Horizontal,"时间");
    inboundtableModel->select();

    inboundTableView = new QTableView(this);
    inboundTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自动适应窗口大小
    inboundTableView->setSelectionBehavior(QAbstractItemView::SelectRows); //选择整行
    inboundTableView->setModel(inboundtableModel);
    inboundTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //表格不可编辑

    QVBoxLayout *layoutv= new QVBoxLayout;//垂直布局
    layoutv->addLayout(layout1);
    layoutv->addWidget(qframe);
    layoutv->addWidget(inboundTableView);

    inboundPage->setLayout(layoutv);
    return inboundPage;
}

//出库管理界面
QWidget* MainView::Creat_OutboundView(){
    QWidget* outboundPage = new QWidget;

    QLabel* titleLabel = new QLabel("出库信息");
    QFont qfont("Microsoft YaHei", 10, 75);
    titleLabel->setFont(qfont);
    outOutbound_PB = new QPushButton("导出");
    outOutbound_PB->setEnabled(false);
    outboundDevAdd_pB = new QPushButton("添加");
    outboundDevAdd_pB->setEnabled(false);
    batchInputOutbound_PB = new QPushButton("批量导入");
    batchInputOutbound_PB->setEnabled(false);

    QHBoxLayout *layout1 = new QHBoxLayout();//水平
    layout1->addWidget(titleLabel);
    layout1->addStretch();
    layout1->addWidget(outboundDevAdd_pB);
    layout1->addWidget(batchInputOutbound_PB);
    layout1->addWidget(outOutbound_PB);

    QLabel *device_ID       = new QLabel("设备编号");
    outboundDevID_Edit      = new QLineEdit();
    QLabel *device_Name     = new QLabel("设备名称");
    outboundDevName_Edit    = new QLineEdit();
    QLabel *User_Name       = new QLabel("操作员工");
    outboundUserName_Edit    = new QLineEdit();
    QLabel *device_MfrsName = new QLabel("设备厂商");
    outboundDevMfrsName_Edit = new QLineEdit();
    QLabel *outbound_Time    = new QLabel("出库时间");
    outboundStartDate_Edit   = new QDateEdit();
    QLabel *To   = new QLabel("至");
    outboundEndDate_Edit     = new QDateEdit(QDate::currentDate()); //日历 并显示当前时间
    outboundStartDate_Edit->setCalendarPopup(true);
    outboundEndDate_Edit->setCalendarPopup(true);
    QPushButton *search_PB  = new QPushButton("查询");
    connect(search_PB,SIGNAL(clicked(bool)),this,SLOT(on_OutboundSearch()));

    QHBoxLayout *layout2    = new QHBoxLayout();//水平
    layout2->addWidget(device_ID);
    layout2->addWidget(outboundDevID_Edit);
    layout2->addStretch();
    layout2->addWidget(device_Name);
    layout2->addWidget(outboundDevName_Edit);
    layout2->addStretch();
    layout2->addWidget(User_Name);
    layout2->addWidget(outboundUserName_Edit);

    QHBoxLayout *layout3    = new QHBoxLayout();//水平
    layout3->addWidget(device_MfrsName);
    layout3->addWidget(outboundDevMfrsName_Edit);
    layout3->addStretch();
    layout3->addWidget(outbound_Time);
    layout3->addWidget(outboundStartDate_Edit);
    layout3->addWidget(To);
    layout3->addWidget(outboundEndDate_Edit);
    layout3->addStretch();
    layout3->addStretch();
    layout3->addWidget(search_PB);

    QVBoxLayout *layoutv1 = new QVBoxLayout(); //垂直布局
    layoutv1->addLayout(layout2);
    layoutv1->addLayout(layout3);
    QFrame *qframe = new QFrame;
    qframe->setFrameStyle(QFrame::StyledPanel);
    qframe->setLayout(layoutv1);

    outboundtableModel = new QSqlTableModel(outboundPage,mydb);
    outboundtableModel->setTable("v_outbound");
    outboundtableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    outboundtableModel->setHeaderData(0,Qt::Horizontal,"设备编号");
    outboundtableModel->setHeaderData(1,Qt::Horizontal,"设备名称");
    outboundtableModel->setHeaderData(2,Qt::Horizontal,"操作员工");
    outboundtableModel->setHeaderData(3,Qt::Horizontal,"出库原因");
    outboundtableModel->setHeaderData(4,Qt::Horizontal,"设备厂商");
    outboundtableModel->setHeaderData(5,Qt::Horizontal,"时间");
    outboundtableModel->select();

    outboundTableView = new QTableView(this);
    outboundTableView->setModel(outboundtableModel);
    outboundTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自动适应窗口大小
   //tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //列宽自适应内容
    outboundTableView->setSelectionBehavior(QAbstractItemView::SelectRows); //选择整行

    outboundTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //表格不可编辑

    QVBoxLayout *layoutv= new QVBoxLayout;//垂直布局
    layoutv->addLayout(layout1);
    layoutv->addWidget(qframe);
    layoutv->addWidget(outboundTableView);

    outboundPage->setLayout(layoutv);
    return outboundPage;
}

//槽函数
//功能界面切换
void MainView::on_SwitchPage(){
    QAction *action = qobject_cast<QAction *>(sender());//获取发送者对象
    if(action->text()=="主页")
        stackWidget->setCurrentIndex(0);
    if(action->text()=="用户管理")
        stackWidget->setCurrentIndex(1);
    if(action->text()=="供应商管理")
        stackWidget->setCurrentIndex(2);
    if(action->text()=="入库管理")
        stackWidget->setCurrentIndex(3);
    if(action->text()=="出库管理")
        stackWidget->setCurrentIndex(4);
    if(action->text()=="设备管理")
        stackWidget->setCurrentIndex(5);
}

//定时任务
void MainView::on_TimeUpdateView(){
    if(LoginView->flag)
    {
        LoginView->flag = false;
        login_Action->setText(LoginView->User.name);//显示用户名
#if 1
        if(LoginView->User.permissionID == "0")
        {
            Permission_pB->setEnabled(true);
            supplierAdd_pB->setEnabled(true);
            inboundDevAdd_pB->setEnabled(true);
            outboundDevAdd_pB->setEnabled(true);
            //导出
            outUser_PB->setEnabled(true);
            outSupplier_PB->setEnabled(true);
            outDevice_PB->setEnabled(true);
            outInbound_PB->setEnabled(true);
            outOutbound_PB->setEnabled(true);
            //导入
            batchInputUser_PB->setEnabled(true);
            batchInputSupplier_PB->setEnabled(true);
            batchInputInbound_PB->setEnabled(true);
            batchInputOutbound_PB->setEnabled(true);
        }

        if(LoginView->User.permissionID == "2"){
            Permission_pB->setEnabled(false);
            supplierAdd_pB->setEnabled(false);
            inboundDevAdd_pB->setEnabled(false);
            outboundDevAdd_pB->setEnabled(false);
            //导出
            outUser_PB->setEnabled(false);
            outSupplier_PB->setEnabled(false);
            outDevice_PB->setEnabled(false);
            outInbound_PB->setEnabled(false);
            outOutbound_PB->setEnabled(false);
            //导入
            batchInputUser_PB->setEnabled(false);
            batchInputSupplier_PB->setEnabled(false);
            batchInputInbound_PB->setEnabled(false);
            batchInputOutbound_PB->setEnabled(false);

        }else if(LoginView->User.permissionID == "1"){
            Permission_pB->setEnabled(false);
            supplierAdd_pB->setEnabled(true);
            inboundDevAdd_pB->setEnabled(true);
            outboundDevAdd_pB->setEnabled(true);
            //导出
            outUser_PB->setEnabled(true);
            outSupplier_PB->setEnabled(true);
            outDevice_PB->setEnabled(true);
            outInbound_PB->setEnabled(true);
            outOutbound_PB->setEnabled(true);
            //导入
            batchInputUser_PB->setEnabled(true);
            batchInputSupplier_PB->setEnabled(true);
            batchInputInbound_PB->setEnabled(true);
            batchInputOutbound_PB->setEnabled(true);
        }
    }
#endif

}

//用户权限设置界面
void MainView::on_PermissionView(){
    PermissionView->show();
    connect(PermissionView->setPermission_PB,SIGNAL(clicked(bool)),this,SLOT(on_InsertPermissionToDb()));
}
//用户权限插入数据库
void MainView::on_InsertPermissionToDb(){
    if(LoginView->User.nameID == PermissionView->nameID_Edit->text())
    {
        QMessageBox::warning(this,"错误","不能设置本人权限");
        return;
    }

    if(PermissionView->nameID_Edit->text().isEmpty())
    {
        QMessageBox::warning(this,"错误","员工编号不能为空");
        return;
    }

    QString Permission_ID;
    if( PermissionView->checkRead->isChecked()==true)
    {
        Permission_ID = "2";
    }
    if( PermissionView->checkWrite->isChecked()==true)
    {
        Permission_ID = "1";
    }

    QSqlQuery query(mydb);
    //更新数据库用户权限标识
    QString sql = "UPDATE tb_user_permission SET Permission_ID = ";
    sql += Permission_ID+" WHERE EmployeeID = '";
    sql += PermissionView->nameID_Edit->text()+"'";
    qDebug() <<sql;
    if(!query.exec(sql))
    {
        QMessageBox::warning(this,"错误",query.lastError().text());
        return;
    }
    QMessageBox::information(this,"提示","权限设置成功");
    PermissionView->close();
    usertableModel->submitAll();
}
//用户查询
void MainView::on_UserSearch(){
    QString userID =  QString("EmployeeID like '%%1%'").arg(userID_Edit->text());
    QString userName =  QString("Name like '%%1%'").arg(userName_Edit->text());
    QString filterStr = "";

    if(!userID_Edit->text().isEmpty())
        filterStr.append(userID);
    if(!userName_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(userName);
    }
    usertableModel->setFilter(filterStr); //数据库模型查询 过滤器
    usertableModel->select();
}
//用户信息导出
void MainView::on_OutUserInfo(){
    ExcleEdit *excelEdit = new ExcleEdit;
    QString UserInfoPath = QFileDialog::getSaveFileName(this,"保存文件",".","Exel file(*.xlsx *.xls)");
    if(UserInfoPath.isNull())
    {
        QMessageBox::warning(this,"错误","选择正确的路径!!");
        return ;
    }

    QAxObject *excel = new QAxObject("Excel.Application"); //创建excle
    if (!excel)
    {
       qDebug()<<"创建Excel失败！";
    }

    excel->dynamicCall("SetVisible(bool Visible)", false);         //是否可视化excel
    excel->dynamicCall("SetUserControl(bool UserControl)",false);  //是否用户可操作
    excel->setProperty("DisplayAlerts", false);                   //是否弹出警告窗口

    QAxObject *workbooks = excel->querySubObject("WorkBooks");     //获取工作簿集合
    workbooks->dynamicCall("Add");                                 //新建一个工作簿
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook"); //获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");         //获取工作表格集合
    QAxObject *worksheet  = worksheets->querySubObject("Item(int)", 1); //获取当前工作表格1，即sheet1
    worksheet->setProperty("Name","用户数据");                           //修改sheet名称

    //设置一级标题列名
    excelEdit->SetTitle1(worksheet,"A1:A1","序号");
    excelEdit->SetTitle1(worksheet,"B1:B1","用户编号");
    excelEdit->SetTitle1(worksheet,"C1:C1","用户名");
    excelEdit->SetTitle1(worksheet,"D1:D1","用户权限");
    //设置单元格和字体属性
    excelEdit->SetFontProperty(worksheet,"A1:D1",true,1,10); //设置字体属性
    excelEdit->SetCellProperty(worksheet,"A1:A1",false,6);   //设置单元格属性
    excelEdit->SetCellProperty(worksheet,"B1:C1",false,10);
    excelEdit->SetCellProperty(worksheet,"D1:D1",false,15);
#if 1
    excelEdit->BatchWriteData(userTableView,worksheet,3);  //数据写入
    //qDebug()<< __FUNCTION__<< "读数据："<<excelEdit->ReadData(worksheet,"A1:A1").toString();
#endif
    //文件保存
    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(UserInfoPath));
    workbook->dynamicCall("Close()");   //关闭文件
    excel->dynamicCall("Quit()");       //关闭excel

    delete worksheet;
    delete worksheets;
    delete workbook;
    delete workbooks;
    delete excel;
}
//用户信息批量导入
void MainView::on_BatchInputUserInfo(){
    ExcleEdit *excelEdit = new ExcleEdit;
    QString filepath = QFileDialog::getOpenFileName(this,"打开文件",".","Exel file(*.xlsx *.xls)");
    if(filepath.isNull())
    {
        QMessageBox::warning(this,"错误","选择正确的路径!!");
        return ;
    }
    QAxObject *excel = new QAxObject("Excel.Application"); //创建excle
    if (!excel)
    {
       qDebug()<<"创建Excel失败！";
    }
    excel->dynamicCall("SetVisible(bool Visible)", false);         //是否可视化excel
    excel->dynamicCall("SetUserControl(bool UserControl)",false);  //是否用户可操作
    excel->setProperty("DisplayAlerts", false);                   //是否弹出警告窗口

    QAxObject *workbooks = excel->querySubObject("WorkBooks");     //获取工作簿集
    workbooks->dynamicCall("Open(const QString&)", QDir::toNativeSeparators(filepath));//打开工作簿
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook"); //获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");         //获取工作表格集合
    QAxObject *worksheet  = worksheets->querySubObject("Item(int)", 1); //获取当前工作表格1，即sheet1

     //校验excel文件是否符合格式要求
    if(excelEdit->ReadData(worksheet,"A1:A1")!="序号"||excelEdit->ReadData(worksheet,"B1:B1")!="用户编号"
        ||excelEdit->ReadData(worksheet,"C1:C1")!="用户名"||excelEdit->ReadData(worksheet,"D1:D1")!="用户权限")
    {
        QMessageBox::warning(this,"错误","文件输入格式不对，请调整！！");
        return;
    }
    int rows = excelEdit->GetRowNums(worksheet);
    int cols = excelEdit->GetColumnNums(worksheet);
    qDebug()<<"row:" <<rows<<"column:"<<cols;

    QString row ="B2:"+excelEdit->Get26AlphabeticCapital(cols)+QString::number(rows);//获取excel区域
     //获取excle内容 构造sql语句
    QVariant var = excelEdit->ReadData(worksheet,row);

    //再次判断格式是否正确
    QVariantList varRows = var.toList();
    QStringList varData;
    excelEdit->ListQVariantToListQString(varRows[rows-2].toList(),varData);
    if(varData.contains(""))
    {
        QMessageBox::warning(this,"错误","文件输入格式不对，请调整！！");
        return;
    }

     //获取excle内容 构造sql语句
    QList<QList<QVariant>> datas;
    excelEdit->QVariantToListListQVariant(var,datas);
    int sizeRow = datas.size();
    int sizeCol = datas[0].size();
    QString user_batchSql = "INSERT INTO tb_user VALUES('";
    QString permision_batchSql= "INSERT INTO tb_user_permission VALUES('";
    int i=0;
    while(1)
    {
        int j=0;
        permision_batchSql.append(datas[i][j].toString());
        permision_batchSql.append("',2)");
        while(1){
            user_batchSql.append(datas[i][j].toString());
            j++;
            if(j>=sizeCol){
                break;
            }
            user_batchSql.append("','");
        }
        i++;
        if(i>=sizeRow){
            user_batchSql.append("')");
            break;
        }
        permision_batchSql.append(",('");
        user_batchSql.append("'),('");
    }
    qDebug()<<__FUNCTION__<<"用户批量导入sql："<<user_batchSql<<endl;
    qDebug()<<__FUNCTION__<<"用户权限批量导入sql："<<permision_batchSql<<endl;

    //数据插入相应数据库
    QSqlQuery query(mydb);
    query.exec("START TRANSACTION"); //开启事物
    bool ok1 = query.exec(user_batchSql);
    bool ok2 = query.exec(permision_batchSql);
    if(ok1&&ok2)
    {
        query.exec("COMMIT");  // 提交事物
        QMessageBox::information(this,"通知","导入成功");
    }else{
        QMessageBox::warning(this,"warning",query.lastError().text());
        query.exec("ROLLBACK"); //事物回滚
    }

    workbook->dynamicCall("Close()");   //关闭文件
    excel->dynamicCall("Quit()");       //关闭excel

    delete worksheet;
    delete worksheets;
    delete workbook;
    delete workbooks;
    delete excel;

}

//供应商查询
void MainView::on_SupplierSearch(){
    QString supplierID =  QString("Mfrs_ID like '%%1%'").arg(supplierID_Edit->text());
    QString supplierName =  QString("Mfrs_Name like '%%1%'").arg(supplierName_Edit->text());
    QString filterStr = "";

    if(!supplierID_Edit->text().isEmpty())
        filterStr.append(supplierID);
    if(!supplierName_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(supplierName);
    }
    suppliertableModel->setFilter(filterStr); //数据库模型查询 过滤器
    suppliertableModel->select();
}
//供应商添加界面
void MainView::on_SupplierAddView(){
    SupplierAddView->show();
    connect(SupplierAddView->setSupplier_PB,SIGNAL(clicked(bool)),this,SLOT(on_InsertSupplierToDb()));

}
//供应商信息插入数据库
void MainView::on_InsertSupplierToDb(){
    if(SupplierAddView->supplierID_Edit->text().isEmpty()||SupplierAddView->supplierName_Edit->text().isEmpty()
       ||SupplierAddView->supplierPerson_Edit->text().isEmpty()||SupplierAddView->supplierTel_Edit->text().isEmpty())
    {
        QMessageBox::warning(this,"错误","请填写完整信息!");
        return;
    }

    QSqlQuery query(mydb);
    QString sql = "INSERT INTO tb_device_mfrs VALUE('";
    sql += SupplierAddView->supplierID_Edit->text()+"','";
    sql += SupplierAddView->supplierName_Edit->text()+"','";
    sql += SupplierAddView->supplierPerson_Edit->text()+"','";
    sql += SupplierAddView->supplierTel_Edit->text()+"')";

    qDebug()<<__FUNCTION__<<"供应商插入语句："<<sql;

    if(!query.exec(sql))
    {
        QMessageBox::warning(this,"错误",query.lastError().text());
        return;
    }

    QMessageBox::information(this,"通知","供应商添加成功");
    SupplierAddView->close();
    suppliertableModel->submitAll();

}
//供应商信息导出
void MainView::on_OutSupplierInfo(){
    ExcleEdit *excelEdit = new ExcleEdit;
    QString SupplierInfoPath = QFileDialog::getSaveFileName(this,"保存文件",".","Exel file(*.xlsx *.xls)");
    if(SupplierInfoPath.isNull())
    {
        QMessageBox::warning(this,"错误","选择正确的路径!!");
        return ;
    }

    QAxObject *excel = new QAxObject("Excel.Application"); //创建excle
    if (!excel)
    {
       qDebug()<<"创建Excel失败！";
    }

    excel->dynamicCall("SetVisible(bool Visible)", false);         //是否可视化excel
    excel->dynamicCall("SetUserControl(bool UserControl)",false);  //是否用户可操作
    excel->setProperty("DisplayAlerts", false);                   //是否弹出警告窗口

    QAxObject *workbooks = excel->querySubObject("WorkBooks");     //获取工作簿集合
    workbooks->dynamicCall("Add");                                 //新建一个工作簿
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook"); //获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");         //获取工作表格集合
    QAxObject *worksheet  = worksheets->querySubObject("Item(int)", 1); //获取当前工作表格1，即sheet1
    worksheet->setProperty("Name","供应商数据");                           //修改sheet名称

    //设置一级标题列名
    excelEdit->SetTitle1(worksheet,"A1:A1","序号");
    excelEdit->SetTitle1(worksheet,"B1:B1","供应商ID");
    excelEdit->SetTitle1(worksheet,"C1:C1","供应商名称");
    excelEdit->SetTitle1(worksheet,"D1:D1","联系人");
    excelEdit->SetTitle1(worksheet,"E1:E1","联系电话");
    //设置单元格和字体属性
    excelEdit->SetFontProperty(worksheet,"A1:E1",true,1,10); //设置字体属性

    excelEdit->SetCellProperty(worksheet,"A1:A1",false,6);   //设置单元格属性
    excelEdit->SetCellProperty(worksheet,"B1:D1",false,10);
    excelEdit->SetCellProperty(worksheet,"E1:E1",false,15);
#if 1
    excelEdit->BatchWriteData(supplierTableView,worksheet,4);  //数据写入
    //qDebug()<< __FUNCTION__<< "读数据："<<excelEdit->ReadData(worksheet,"A1:A1").toString();
#endif
    //文件保存
    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(SupplierInfoPath));
    workbook->dynamicCall("Close()");   //关闭文件
    excel->dynamicCall("Quit()");       //关闭excel

    delete worksheet;
    delete worksheets;
    delete workbook;
    delete workbooks;
    delete excel;}
//供应商信息批量导入
void MainView::on_BatchInputSupplierInfo(){
    ExcleEdit *excelEdit = new ExcleEdit;
    QString filepath = QFileDialog::getOpenFileName(this,"打开文件",".","Exel file(*.xlsx *.xls)");
    if(filepath.isNull())
    {
        QMessageBox::warning(this,"错误","选择正确的路径!!");
        return ;
    }
    QAxObject *excel = new QAxObject("Excel.Application");  //创建excle
    if (!excel)
    {
       qDebug()<<"创建Excel失败！";
    }
    excel->dynamicCall("SetVisible(bool Visible)", false);          //是否可视化excel
    excel->dynamicCall("SetUserControl(bool UserControl)",false);   //是否用户可操作
    excel->setProperty("DisplayAlerts", false);                     //是否弹出警告窗口

    QAxObject *workbooks = excel->querySubObject("WorkBooks");      //获取工作簿集
    workbooks->dynamicCall("Open(const QString&)", QDir::toNativeSeparators(filepath));//打开工作簿
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook");      //获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");         //获取工作表格集合
    QAxObject *worksheet  = worksheets->querySubObject("Item(int)", 1); //获取当前工作表格1，即sheet1

    //校验excel文件是否符合格式要求
    if(excelEdit->ReadData(worksheet,"A1:A1")!="序号"||excelEdit->ReadData(worksheet,"B1:B1")!="供应商ID"
        ||excelEdit->ReadData(worksheet,"C1:C1")!="供应商名称"||excelEdit->ReadData(worksheet,"D1:D1")!="联系人"
        ||excelEdit->ReadData(worksheet,"E1:E1")!="联系电话")
    {
       QMessageBox::warning(this,"错误","文件输入格式不对，请调整！！");
       return;
    }
    int rows = excelEdit->GetRowNums(worksheet);
    int cols = excelEdit->GetColumnNums(worksheet);
    qDebug()<<"row:" <<rows<<"column:"<<cols;
    qDebug()<<__FUNCTION__<<"row:" <<rows<<"column:"<<cols<<endl;

    //获取excle内容 构造sql语句
    QString row ="B2:"+excelEdit->Get26AlphabeticCapital(cols)+QString::number(rows); //excel区域
    QVariant var = excelEdit->ReadData(worksheet,row);

    //再次判断格式是否正确
    QVariantList varRows = var.toList();
    QStringList varData;
    excelEdit->ListQVariantToListQString(varRows[rows-2].toList(),varData);
    if(varData.contains(""))
    {
        QMessageBox::warning(this,"错误","文件输入格式不对，请调整！！");
        return;
    }
    //获取excle内容 构造sql语句
    QList<QList<QVariant>> datas; 
    excelEdit->QVariantToListListQVariant(var,datas);
    int sizeRow = datas.size();
    int sizeCol = datas[0].size();
    QString supplier_batchSql = "INSERT INTO tb_device_mfrs VALUE('";
    int i=0;
    while(1)
    {
        int j=0;
        while(1){
            supplier_batchSql.append(datas[i][j].toString());
            j++;
            if(j>=sizeCol){
                break;
            }
            supplier_batchSql.append("','");
        }
        i++;
        if(i>=sizeRow){
            supplier_batchSql.append("')");
            break;
        }
        supplier_batchSql.append("'),('");
    }
    qDebug()<<__FUNCTION__<<"供应商批量导入sql："<<supplier_batchSql<<endl;
#if 0
    //数据插入相应数据库
    QSqlQuery query(mydb);
    if(query.exec(supplier_batchSql)){
        QMessageBox::information(this,"通知","导入成功");
    }else{
        QMessageBox::warning(this,"warning",query.lastError().text());
    }
#endif
    workbook->dynamicCall("Close()");   //关闭文件
    excel->dynamicCall("Quit()");       //关闭excel

    delete worksheet;
    delete worksheets;
    delete workbook;
    delete workbooks;
    delete excel;

}

//设备信息查询
void MainView::on_DeviceSearch(){
    QString deviceID    =  QString("Device_ID like '%%1%'").arg(deviceID_Edit->text());
    QString deviceName  =  QString("Device_Name like '%%1%'").arg(deviceName_Edit->text());
    QString deviceModel =  QString("Device_Model like '%%1%'").arg(deviceModel_Edit->text());
    QString deviceType  =  QString("Device_Type like '%%1%'").arg(deviceType_Edit->text());
    QString deviceMfrsName  =  QString("Mfrs_Name like '%%1%'").arg(deviceMfrsName_Edit->text());
    QString filterStr = "";

    if(!deviceID_Edit->text().isEmpty())
        filterStr.append(deviceID);
    if(!deviceName_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(deviceName);
    }

    if(!deviceModel_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(deviceModel);
    }

    if(!deviceType_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(deviceType);
    }

    if(!deviceMfrsName_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(deviceMfrsName);
    }

    devicetableModel->setFilter(filterStr); //数据库模型查询 过滤器
    devicetableModel->select();

}
//设备信息导出
void MainView::on_OutDeviceInfo(){
    ExcleEdit *excelEdit = new ExcleEdit;
    QString DeviceInfoPath = QFileDialog::getSaveFileName(this,"保存文件",".","Exel file(*.xlsx *.xls)");
    if(DeviceInfoPath.isNull())
    {
        QMessageBox::warning(this,"错误","选择正确的路径!!");
        return ;
    }

    QAxObject *excel = new QAxObject("Excel.Application"); //创建excle
    if (!excel)
    {
       qDebug()<<"创建Excel失败！";
    }

    excel->dynamicCall("SetVisible(bool Visible)", false);         //是否可视化excel
    excel->dynamicCall("SetUserControl(bool UserControl)",false);  //是否用户可操作
    excel->setProperty("DisplayAlerts", false);                   //是否弹出警告窗口

    QAxObject *workbooks = excel->querySubObject("WorkBooks");     //获取工作簿集合
    workbooks->dynamicCall("Add");                                 //新建一个工作簿
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook"); //获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");         //获取工作表格集合
    QAxObject *worksheet  = worksheets->querySubObject("Item(int)", 1); //获取当前工作表格1，即sheet1
    worksheet->setProperty("Name","设备数据");                           //修改sheet名称

    //设置一级标题列名
    excelEdit->SetTitle1(worksheet,"A1:A1","序号");
    excelEdit->SetTitle1(worksheet,"B1:B1","设备编号");
    excelEdit->SetTitle1(worksheet,"C1:C1","设备名称");
    excelEdit->SetTitle1(worksheet,"D1:D1","设备型号");
    excelEdit->SetTitle1(worksheet,"E1:E1","设备类型");
    excelEdit->SetTitle1(worksheet,"F1:F1","设备描述");
    excelEdit->SetTitle1(worksheet,"G1:G1","设备厂商");
    //设置单元格和字体属性
    excelEdit->SetFontProperty(worksheet,"A1:G1",true,1,10); //设置字体属性

    excelEdit->SetCellProperty(worksheet,"A1:A1",false,6);   //设置单元格属性
    excelEdit->SetCellProperty(worksheet,"B1:E1",false,10);
    excelEdit->SetCellProperty(worksheet,"F1:F1",true,25);
    excelEdit->SetCellProperty(worksheet,"G1:G1",false,15);
#if 1
    excelEdit->BatchWriteData(deviceTableView,worksheet,6);  //数据写入
    //qDebug()<< __FUNCTION__<< "读数据："<<excelEdit->ReadData(worksheet,"A1:A1").toString();
#endif
    //文件保存
    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(DeviceInfoPath));
    workbook->dynamicCall("Close()");   //关闭文件
    excel->dynamicCall("Quit()");       //关闭excel

    delete worksheet;
    delete worksheets;
    delete workbook;
    delete workbooks;
    delete excel;
}


//入库信息查询
void MainView::on_InboundSearch(){
    QString inboundDevID    =  QString("Device_ID like '%%1%'").arg(inboundDevID_Edit->text());
    QString inboundDevName  =  QString("Device_Name like '%%1%'").arg(inboundDevName_Edit->text());
    QString inboundUserName =  QString("User_Name like '%%1%'").arg(inboundUserName_Edit->text());
    QString inboundDevMfrsName  =  QString("Mfrs_Name like '%%1%'").arg(inboundDevMfrsName_Edit->text());
    QString inboundStartDate = QString("UNIX_TIMESTAMP(`time`) > %1").arg(inboundStartDate_Edit->dateTime().toTime_t());
    QString inboundEndDate = QString("UNIX_TIMESTAMP(`time`) < %1").arg((inboundEndDate_Edit->dateTime().toTime_t()+86399));
    QString filterStr = "";

    if(!inboundDevID_Edit->text().isEmpty())
        filterStr.append(inboundDevID);
    if(!inboundDevName_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(inboundDevName);
    }
    if(!inboundUserName_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(inboundUserName);
    }
    if(!deviceMfrsName_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(inboundDevMfrsName);
    }
    if(!inboundStartDate_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(inboundStartDate);
    }
    if(!inboundEndDate_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(inboundEndDate);
    }

    inboundtableModel->setFilter(filterStr);
    inboundtableModel->select();
}
//入库添加界面
void MainView::on_InboundAddView(){
    InboundAddView->show();
    connect(InboundAddView->setInbound_PB,SIGNAL(clicked(bool)),this,SLOT(on_InsertInboundDevToDb()));

}
//入库信息插入数据库
void MainView::on_InsertInboundDevToDb(){
    if(InboundAddView->deviceID_Edit->text().isEmpty()||InboundAddView->deviceName_Edit->text().isEmpty()
       ||InboundAddView->deviceModel_Edit->text().isEmpty()||InboundAddView->deviceType_Edit->text().isEmpty()
       ||InboundAddView->deviceMfrs_Edit->text().isEmpty()||InboundAddView->deviceDec_Edit->toPlainText().isEmpty())
    {
        QMessageBox::warning(this,"错误","请填写完整信息!");
        return;
    }
    //相关数据插入对应数据表中
    QSqlQuery query(mydb);

    //获取供应商标识
    QString MfrsID;
    QString getMfrsIDSql = "SELECT Mfrs_ID FROM tb_device_mfrs WHERE Mfrs_Name LIKE '";
    getMfrsIDSql += InboundAddView->deviceMfrs_Edit->text()+"'";

    if(!query.exec(getMfrsIDSql)){
        QMessageBox::warning(this,"错误",query.lastError().text());
        return;
    }
    if(!query.next()){
        QMessageBox::warning(this,"错误","无该供应商，请先添加");
        return;
    }
    MfrsID = query.value(0).toString(); //供应商标识

    //数据插入入库表 tb_device_inbound
    QString inboundSql = "INSERT INTO tb_device_inbound VALUE('";
    inboundSql += InboundAddView->deviceID_Edit->text()+"','"+InboundAddView->deviceName_Edit->text()+"','";
    inboundSql += MfrsID+"','"+LoginView->User.nameID+"',";
    inboundSql += QString::number(QDateTime::currentDateTime().toTime_t())+")";
    qDebug() <<__FUNCTION__<<"入库插入Sql："<<inboundSql<<endl;

    //数据插入设备表 tb_device
    QString deviceSql = "INSERT INTO tb_device VALUE('";
    deviceSql += InboundAddView->deviceID_Edit->text()+"','"+InboundAddView->deviceName_Edit->text()+"','";
    deviceSql += InboundAddView->deviceModel_Edit->text()+"','"+InboundAddView->deviceType_Edit->text()+"','";
    deviceSql += InboundAddView->deviceDec_Edit->toPlainText()+"','"+MfrsID+"')";
    qDebug() <<__FUNCTION__<<"设备插入Sql："<<deviceSql<<endl;

    //执行sql语句
    query.exec("START TRANSACTION"); //开启事物
    bool ok1 = query.exec(inboundSql);
    bool ok2 = query.exec(deviceSql);
    if(ok1&&ok2)
    {
        query.exec("COMMIT");  // 提交事物
    }else{
        QMessageBox::warning(this,"warning",query.lastError().text());
        query.exec("ROLLBACK"); //事物回滚
        return;
    }

    InboundAddView->close();
    inboundtableModel->submitAll();
    devicetableModel->submitAll();
}
//入库信息导出
void MainView::on_OutInboundInfo(){
    ExcleEdit *excelEdit = new ExcleEdit;
    QString InboundInfoPath = QFileDialog::getSaveFileName(this,"保存文件",".","Exel file(*.xlsx *.xls)");
    if(InboundInfoPath.isNull())
    {
        QMessageBox::warning(this,"错误","选择正确的路径!!");
        return ;
    }

    QAxObject *excel = new QAxObject("Excel.Application"); //创建excle
    if (!excel)
    {
       qDebug()<<"创建Excel失败！";
    }

    excel->dynamicCall("SetVisible(bool Visible)", false);         //是否可视化excel
    excel->dynamicCall("SetUserControl(bool UserControl)",false);  //是否用户可操作
    excel->setProperty("DisplayAlerts", false);                   //是否弹出警告窗口

    QAxObject *workbooks = excel->querySubObject("WorkBooks");     //获取工作簿集合
    workbooks->dynamicCall("Add");                                 //新建一个工作簿
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook"); //获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");         //获取工作表格集合
    QAxObject *worksheet  = worksheets->querySubObject("Item(int)", 1); //获取当前工作表格1，即sheet1
    worksheet->setProperty("Name","入库数据");                           //修改sheet名称

    //设置一级标题列名
    excelEdit->SetTitle1(worksheet,"A1:A1","序号");
    excelEdit->SetTitle1(worksheet,"B1:B1","设备编号");
    excelEdit->SetTitle1(worksheet,"C1:C1","设备名称");
    excelEdit->SetTitle1(worksheet,"D1:D1","操作员工");
    excelEdit->SetTitle1(worksheet,"E1:E1","设备厂商");
    excelEdit->SetTitle1(worksheet,"F1:F1","时间");
    //设置单元格和字体属性
    excelEdit->SetFontProperty(worksheet,"A1:F1",true,1,10); //设置字体属性

    excelEdit->SetCellProperty(worksheet,"A1:A1",false,6);   //设置单元格属性
    excelEdit->SetCellProperty(worksheet,"B1:E1",false,10);
    excelEdit->SetCellProperty(worksheet,"F1:F1",false,20);
#if 1
    excelEdit->BatchWriteData(inboundTableView,worksheet,5);  //数据写入

    //设置单元格日期时间格式
    int rows = excelEdit->GetRowNums(worksheet);
    int cols = excelEdit->GetColumnNums(worksheet);
    QString TimeVar = "F2:"+excelEdit->Get26AlphabeticCapital(cols)+QString::number(rows); //区域设置
    QAxObject *range=worksheet->querySubObject("Range(const QString&)",TimeVar); //获取设置时间区域
    range->setProperty("NumberFormatLocal","yyyy/mm/dd hh:mm:ss"); //设置时间显示格式

    //qDebug()<< __FUNCTION__<< "读数据："<<excelEdit->ReadData(worksheet,"A1:A1").toString();
#endif
    //文件保存
    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(InboundInfoPath));
    workbook->dynamicCall("Close()");   //关闭文件
    excel->dynamicCall("Quit()");       //关闭excel

    delete range;
    delete worksheet;
    delete worksheets;
    delete workbook;
    delete workbooks;
    delete excel;}
//入库批量导入
void MainView::on_BatchInputInboundInfo(){
    ExcleEdit *excelEdit = new ExcleEdit;
    QString filepath = QFileDialog::getOpenFileName(this,"打开文件",".","Exel file(*.xlsx *.xls)");
    if(filepath.isNull())
    {
        QMessageBox::warning(this,"错误","选择正确的路径!!");
        return ;
    }
    QAxObject *excel = new QAxObject("Excel.Application");  //创建excle
    if (!excel)
    {
       qDebug()<<"创建Excel失败！";
    }
    excel->dynamicCall("SetVisible(bool Visible)", false);          //是否可视化excel
    excel->dynamicCall("SetUserControl(bool UserControl)",false);   //是否用户可操作
    excel->setProperty("DisplayAlerts", false);                     //是否弹出警告窗口

    QAxObject *workbooks = excel->querySubObject("WorkBooks");      //获取工作簿集
    workbooks->dynamicCall("Open(const QString&)", QDir::toNativeSeparators(filepath));//打开工作簿
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook");      //获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");         //获取工作表格集合
    QAxObject *worksheet  = worksheets->querySubObject("Item(int)", 1); //获取当前工作表格1，即sheet1

    //校验excel文件是否符合格式要求
    if(excelEdit->ReadData(worksheet,"A1:A1")!="序号"||excelEdit->ReadData(worksheet,"B1:B1")!="设备编号"
        ||excelEdit->ReadData(worksheet,"C1:C1")!="设备名称"||excelEdit->ReadData(worksheet,"D1:D1")!="设备型号"
        ||excelEdit->ReadData(worksheet,"E1:E1")!="设备类型"||excelEdit->ReadData(worksheet,"F1:F1")!="设备描述"
        ||excelEdit->ReadData(worksheet,"G1:G1")!="供应商标识")
    {
       QMessageBox::warning(this,"错误","文件输入格式不对，请调整！！");
       return;
    }
    int rows = excelEdit->GetRowNums(worksheet);
    int cols = excelEdit->GetColumnNums(worksheet);
    qDebug()<<__FUNCTION__<<"row:" <<rows<<"column:"<<cols<<endl;

    //获取excle内容 构造sql语句
    QString row ="B2:"+excelEdit->Get26AlphabeticCapital(cols)+QString::number(rows); //excel区域
    qDebug()<<__FUNCTION__<<"area:" <<row<<endl;
    QVariant var = excelEdit->ReadData(worksheet,row);

    //再次判断格式是否正确
    QVariantList varRows = var.toList();
    QStringList varData;
    excelEdit->ListQVariantToListQString(varRows[rows-2].toList(),varData);
    if(varData.contains(""))
    {
        QMessageBox::warning(this,"错误","文件输入格式不对，请调整！！");
        return;
    }

     //获取excle内容 构造sql语句
    QList<QList<QVariant>> datas;
    excelEdit->QVariantToListListQVariant(var,datas);
    int sizeRow = datas.size();
    int sizeCol = datas[0].size();

    QString inbound_batchSql = "INSERT INTO tb_device_inbound VALUE('";
    QString device_batchSql = "INSERT INTO tb_device VALUE('";
    int i=0;
    while(1)
    {
        int j=0;
        while(1){
            device_batchSql.append(datas[i][j].toString());
            if(j==0||j==1){
                inbound_batchSql.append(datas[i][j].toString());
                inbound_batchSql.append("','");
            }
            if(j==5){
               inbound_batchSql.append(datas[i][j].toString());
               inbound_batchSql.append("','");
               inbound_batchSql.append(LoginView->User.nameID);//用户标识
               inbound_batchSql.append("',");
               inbound_batchSql.append(QString::number(QDateTime::currentDateTime().toTime_t())); //时间
            }
            j++;
            if(j>=sizeCol){ //一行结束
                break;
            }
            device_batchSql.append("','");
        }
        i++;
        if(i>=sizeRow){   //整个表结束
            device_batchSql.append("')");
            inbound_batchSql.append(")");
            break;
        }
        device_batchSql.append("'),('");
        inbound_batchSql.append("),('");
    }
    qDebug()<<__FUNCTION__<<"设备批量导入sql："<<device_batchSql<<endl;
    qDebug()<<__FUNCTION__<<"入库批量导入sql："<<inbound_batchSql<<endl;
#if 1
    //数据插入相应数据库
    QSqlQuery query(mydb);
    query.exec("START TRANSACTION"); //开启事物
    bool ok1 = query.exec(device_batchSql);
    bool ok2 = query.exec(inbound_batchSql);
    if(ok1&&ok2)
    {
        query.exec("COMMIT");  // 提交事物
        QMessageBox::information(this,"通知","导入成功");
    }else{
        QMessageBox::warning(this,"warning",query.lastError().text());
        query.exec("ROLLBACK"); //事物回滚
    }
#endif
    workbook->dynamicCall("Close()");   //关闭文件
    excel->dynamicCall("Quit()");       //关闭excel

    delete worksheet;
    delete worksheets;
    delete workbook;
    delete workbooks;
    delete excel;
}

//出库信息查询
void MainView::on_OutboundSearch(){
    QString outboundDevID    =  QString("Device_ID like '%%1%'").arg(outboundDevID_Edit->text());
    QString outboundDevName  =  QString("Device_Name like '%%1%'").arg(outboundDevName_Edit->text());
    QString outboundUserName =  QString("User_Name like '%%1%'").arg(outboundUserName_Edit->text());
    QString outboundDevMfrsName  =  QString("Mfrs_Name like '%%1%'").arg(outboundDevMfrsName_Edit->text());
    QString outboundStartDate = QString("UNIX_TIMESTAMP(`time`) > %1").arg(outboundStartDate_Edit->dateTime().toTime_t());
    QString outboundEndDate = QString("UNIX_TIMESTAMP(`time`) < %1").arg((outboundEndDate_Edit->dateTime().toTime_t()+86399));
    QString filterStr = "";

    if(!outboundDevID_Edit->text().isEmpty())
        filterStr.append(outboundDevID);
    if(!outboundDevName_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(outboundDevName);
    }
    if(!outboundUserName_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(outboundUserName);
    }
    if(!outboundDevMfrsName_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(outboundDevMfrsName);
    }
    if(!outboundStartDate_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(outboundStartDate);
    }
    if(!outboundEndDate_Edit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(outboundEndDate);
    }

    outboundtableModel->setFilter(filterStr);
    outboundtableModel->select();
}
//出库添加界面
void MainView::on_OutboundAddView(){
    OutboundAddView->show();
    connect(OutboundAddView->setOutbound_PB,SIGNAL(clicked(bool)),this,SLOT(on_InsertOutboundDevToDb()));
}
//出库信息插入数据库
void MainView::on_InsertOutboundDevToDb(){
    if(OutboundAddView->deviceID_Edit->text().isEmpty()||OutboundAddView->deviceName_Edit->text().isEmpty()
       ||OutboundAddView->OutboundDec_Edit->toPlainText().isEmpty())
    {
        QMessageBox::warning(this,"错误","请填写完整信息!");
        return;
    }
    QSqlQuery query(mydb);
    //根据设备编号 获取设备供应商标识信息
    QString sql1 = "SELECT Mfrs_ID FROM tb_device WHERE Device_ID Like '";
    sql1 += OutboundAddView->deviceID_Edit->text()+"'";

    QString MfrsID;
    if(!query.exec(sql1)){
        QMessageBox::warning(this,"错误",query.lastError().text());
        return;
    }
    if(!query.next()){
        QMessageBox::warning(this,"错误","无该供应商,请确认");
        return;
    }
    MfrsID = query.value(0).toString(); //供应商标识

    //数据插入出库表 tb_device_outbound
     QString sql2 = "INSERT INTO tb_device_outbound VALUE('";
     sql2 += OutboundAddView->deviceID_Edit->text()+"','"+ OutboundAddView->deviceName_Edit->text()+"','";
     sql2 += MfrsID+"','"+LoginView->User.nameID+"','"+OutboundAddView->OutboundDec_Edit->toPlainText()+"',";
     sql2 += QString::number(QDateTime::currentDateTime().toTime_t())+")";
     if(!query.exec(sql2)){
         QMessageBox::warning(this,"错误",query.lastError().text());
         return;
     }

    //删除设备表中数据 tb_device
    QString sql3 = "DELETE FROM tb_device WHERE Device_ID LIKE '";
    sql3 += OutboundAddView->deviceID_Edit->text()+"'";
    qDebug() << sql3;
    if(!query.exec(sql3)){
        QMessageBox::warning(this,"错误",query.lastError().text());
        return;
    }
    OutboundAddView->close();
    outboundtableModel->submitAll();
    devicetableModel->submitAll();
}
//出库信息导出
void MainView::on_OutOutboundInfo(){
    ExcleEdit *excelEdit = new ExcleEdit;
    QString OutboundInfoPath = QFileDialog::getSaveFileName(this,"保存文件",".","Exel file(*.xlsx *.xls)");
    if(OutboundInfoPath.isNull())
    {
        QMessageBox::warning(this,"错误","选择正确的路径!!");
        return ;
    }

    QAxObject *excel = new QAxObject("Excel.Application"); //创建excle
    if (!excel)
    {
       qDebug()<<"创建Excel失败！";
    }

    excel->dynamicCall("SetVisible(bool Visible)", false);         //是否可视化excel
    excel->dynamicCall("SetUserControl(bool UserControl)",false);  //是否用户可操作
    excel->setProperty("DisplayAlerts", false);                   //是否弹出警告窗口

    QAxObject *workbooks = excel->querySubObject("WorkBooks");     //获取工作簿集合
    workbooks->dynamicCall("Add");                                 //新建一个工作簿
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook"); //获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");         //获取工作表格集合
    QAxObject *worksheet  = worksheets->querySubObject("Item(int)", 1); //获取当前工作表格1，即sheet1
    worksheet->setProperty("Name","出库数据");                           //修改sheet名称

    //设置一级标题列名
    excelEdit->SetTitle1(worksheet,"A1:A1","序号");
    excelEdit->SetTitle1(worksheet,"B1:B1","设备编号");
    excelEdit->SetTitle1(worksheet,"C1:C1","设备名称");
    excelEdit->SetTitle1(worksheet,"D1:D1","操作员工");
    excelEdit->SetTitle1(worksheet,"E1:E1","出库原因");
    excelEdit->SetTitle1(worksheet,"F1:F1","设备厂商");
    excelEdit->SetTitle1(worksheet,"G1:G1","时间");
    //设置单元格和字体属性
    excelEdit->SetFontProperty(worksheet,"A1:G1",true,1,10); //设置字体属性

    excelEdit->SetCellProperty(worksheet,"A1:A1",false,6);   //设置单元格属性
    excelEdit->SetCellProperty(worksheet,"B1:D1",false,10);
    excelEdit->SetCellProperty(worksheet,"E1:E1",true,20);
    excelEdit->SetCellProperty(worksheet,"F1:F1",false,10);
    excelEdit->SetCellProperty(worksheet,"G1:G1",false,20);
#if 1
    excelEdit->BatchWriteData(outboundTableView,worksheet,6);  //数据写入

    //设置单元格日期时间格式
    int rows = excelEdit->GetRowNums(worksheet);
    int cols = excelEdit->GetColumnNums(worksheet);
    QString TimeVar = "G2:"+excelEdit->Get26AlphabeticCapital(cols)+QString::number(rows);
    qDebug() <<TimeVar;
    QAxObject *range=worksheet->querySubObject("Range(const QString&)",TimeVar); //获取设置时间区域
    range->setProperty("NumberFormatLocal","yyyy/mm/dd hh:mm:ss"); //设置时间显示格式

    //qDebug()<< __FUNCTION__<< "读数据："<<excelEdit->ReadData(worksheet,"A1:A1").toString();
#endif
    //文件保存
    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(OutboundInfoPath));
    workbook->dynamicCall("Close()");   //关闭文件
    excel->dynamicCall("Quit()");       //关闭excel

    delete range;
    delete worksheet;
    delete worksheets;
    delete workbook;
    delete workbooks;
    delete excel;
}
//出库批量导入
void MainView::on_BatchInputOutboundInfo(){
    ExcleEdit *excelEdit = new ExcleEdit;
    QString filepath = QFileDialog::getOpenFileName(this,"打开文件",".","Exel file(*.xlsx *.xls)");
    if(filepath.isNull())
    {
        QMessageBox::warning(this,"错误","选择正确的路径!!");
        return ;
    }
    QAxObject *excel = new QAxObject("Excel.Application");  //创建excle
    if (!excel)
    {
       qDebug()<<"创建Excel失败！";
    }
    excel->dynamicCall("SetVisible(bool Visible)", false);          //是否可视化excel
    excel->dynamicCall("SetUserControl(bool UserControl)",false);   //是否用户可操作
    excel->setProperty("DisplayAlerts", false);                     //是否弹出警告窗口

    QAxObject *workbooks = excel->querySubObject("WorkBooks");      //获取工作簿集
    workbooks->dynamicCall("Open(const QString&)", QDir::toNativeSeparators(filepath));//打开工作簿
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook");      //获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");         //获取工作表格集合
    QAxObject *worksheet  = worksheets->querySubObject("Item(int)", 1); //获取当前工作表格1，即sheet1

    //校验excel文件是否符合格式要求
    if(excelEdit->ReadData(worksheet,"A1:A1")!="序号"||excelEdit->ReadData(worksheet,"B1:B1")!="设备编号"
        ||excelEdit->ReadData(worksheet,"C1:C1")!="设备名称"||excelEdit->ReadData(worksheet,"D1:D1")!="供应商标识"
        ||excelEdit->ReadData(worksheet,"E1:E1")!="出库说明")
    {
       QMessageBox::warning(this,"错误","文件输入格式不对，请调整！！");
       return;
    }
    int rows = excelEdit->GetRowNums(worksheet);
    int cols = excelEdit->GetColumnNums(worksheet);
    qDebug()<<__FUNCTION__<<"row:" <<rows<<"column:"<<cols<<endl;

    //获取excle内容 构造sql语句
    QString row ="B2:"+excelEdit->Get26AlphabeticCapital(cols)+QString::number(rows); //excel区域
    qDebug()<<__FUNCTION__<<"area:" <<row<<endl;
    QVariant var = excelEdit->ReadData(worksheet,row);

    //再次判断格式是否正确
    QVariantList varRows = var.toList();
    QStringList varData;
    excelEdit->ListQVariantToListQString(varRows[rows-2].toList(),varData);
    if(varData.contains(""))
    {
        QMessageBox::warning(this,"错误","文件输入格式不对，请调整！！");
        return;
    }

     //获取excle内容 构造sql语句
    QList<QList<QVariant>> datas;
    excelEdit->QVariantToListListQVariant(var,datas);
    int sizeRow = datas.size();
    int sizeCol = datas[0].size();

    QString outbound_batchSql = "INSERT INTO tb_device_outbound VALUE('";
    int i=0;
    while(1)
    {
        int j=0;
        while(1){
            if(j==0||j==1){
                outbound_batchSql.append(datas[i][j].toString());
            }
            if(j==2){
               outbound_batchSql.append(datas[i][j].toString());
               outbound_batchSql.append("','");
               outbound_batchSql.append(LoginView->User.nameID);//用户标识
            }
            if(j==3)
            {
               outbound_batchSql.append(datas[i][j].toString());
               outbound_batchSql.append("',");
               outbound_batchSql.append(QString::number(QDateTime::currentDateTime().toTime_t())); //时间
            }
            j++;
            if(j>=sizeCol){ //一行结束
                break;
            }
            outbound_batchSql.append("','");
        }
        i++;
        if(i>=sizeRow){   //整个表结束
            outbound_batchSql.append(")");
            break;
        }
        outbound_batchSql.append("),('");
    }
    QString device_delSql = "DELETE tb_device FROM tb_device INNER JOIN tb_device_outbound ON tb_device.Device_ID=tb_device_outbound.Device_ID";
    qDebug()<<__FUNCTION__<<"设备批量删除sql："<<device_delSql<<endl;
    qDebug()<<__FUNCTION__<<"出库库批量导入sql："<<outbound_batchSql<<endl;
#if 1
    //数据插入相应数据库
    QSqlQuery query(mydb);
    query.exec("START TRANSACTION"); //开启事物
    bool ok1 = query.exec(outbound_batchSql);
    bool ok2 = query.exec(device_delSql);
    if(ok1&&ok2)
    {
        query.exec("COMMIT");  // 提交事物
        QMessageBox::information(this,"通知","导入成功");
    }else{
        QMessageBox::warning(this,"warning",query.lastError().text());
        query.exec("ROLLBACK"); //事物回滚
    }
#endif
    workbook->dynamicCall("Close()");   //关闭文件
    excel->dynamicCall("Quit()");       //关闭excel

    delete worksheet;
    delete worksheets;
    delete workbook;
    delete workbooks;
    delete excel;
}
/*数据库连接*/
void MainView::MysqlConnect(){
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        mydb = QSqlDatabase::database("qt_sql_default_connection");
    }else{
        mydb = QSqlDatabase::addDatabase("QMYSQL");
    }
    mydb.setHostName("192.168.8.153");
    mydb.setDatabaseName("test");
    mydb.setPassword("lonsin");
    mydb.setUserName("root");

    if(!mydb.open())
    {
        QMessageBox::warning(this,"错误",mydb.lastError().text());
    }
    return;
}









