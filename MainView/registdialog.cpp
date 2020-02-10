#include "registdialog.h"

RegistDialog::RegistDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("注册"); //窗口名称
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
    resize(180,180);

    ID_Label =  new QLabel("员工编号");
    nameLabel = new QLabel("用户名");
    passwordLabel_1 = new QLabel("密码");
    passwordLabel_2 = new QLabel("确认密码");
    nameID_Edit = new QLineEdit;
    name_Edit = new QLineEdit;
    password_Edit_1 = new QLineEdit;
    password_Edit_2 = new QLineEdit;
    regist_PB = new QPushButton("注册");

    regist_PB->resize(160,23);
    password_Edit_1->setEchoMode(QLineEdit::Password);//密码显示星号
    password_Edit_2->setEchoMode(QLineEdit::Password);//密码显示星号

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(ID_Label,0,0);
    gridLayout->addWidget(nameID_Edit,0,1);
    gridLayout->addWidget(nameLabel,1,0);
    gridLayout->addWidget(name_Edit,1,1);
    gridLayout->addWidget(passwordLabel_1,2,0);
    gridLayout->addWidget(password_Edit_1,2,1);
    gridLayout->addWidget(passwordLabel_2,3,0);
    gridLayout->addWidget(password_Edit_2,3,1);

    //QHBoxLayout *hLayout = new QHBoxLayout;
    //hLayout->addWidget(regist_PB);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(gridLayout);
    vLayout->addWidget(regist_PB);

    connect(regist_PB,SIGNAL(clicked(bool)),this,SLOT(on_Register()));

    setLayout(vLayout);
}

RegistDialog::~RegistDialog()
{
    regist_db.close();
}


void RegistDialog::on_Register(){
    if(nameID_Edit->text().isEmpty()||name_Edit->text().isEmpty()
         ||password_Edit_1->text().isEmpty()||password_Edit_2->text().isEmpty())
    {
        QMessageBox::warning(this,"warning","请将所有信息填完整！！");
        return;
    }

    if(password_Edit_1->text()!=password_Edit_2->text())
    {
        QMessageBox::warning(this,"warning","密码输入不一致！！");
        return;
    }

    //构建数据库插入新用户语句
    QString user_sql = "insert into tb_user value('";
    user_sql += nameID_Edit->text()+"','";
    user_sql += name_Edit->text()+"','";
    user_sql += password_Edit_1->text()+"')";
    qDebug() << "注册用户插入语句："<< user_sql;

    //用户授权插入语句
    QString permision_sql = "insert into tb_user_permission value('";
    permision_sql += nameID_Edit->text()+"',2)"; //默认权限只读r
    //执行sql
    QSqlQuery query(regist_db);
    query.exec("START TRANSACTION");//开启事务
    bool ok1 = query.exec(user_sql);
    bool ok2 = query.exec(permision_sql);
    if(ok1&&ok2)
    {
        query.exec("COMMIT");  // 提交事务
        QMessageBox::information(this,"通知","注册成功");
    }else{
        QMessageBox::warning(this,"warning","注册失败，重新注册");
        query.exec("ROLLBACK"); //事务回滚
    }
    this->close();
}

/*数据库连接*/
void RegistDialog::MysqlConnect(){
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        regist_db = QSqlDatabase::database("qt_sql_default_connection");
    }else{
        regist_db = QSqlDatabase::addDatabase("QMYSQL");
    }

    regist_db.setHostName("192.168.8.153");
    regist_db.setDatabaseName("test");
    regist_db.setPassword("lonsin");
    regist_db.setUserName("root");

    if(!regist_db.open())
    {
        QMessageBox::warning(this,"错误",regist_db.lastError().text());
        //退出登录界面
        this->close(); //关闭登录窗口
    }else{
        qDebug()<<"mysql connect success!!";
    }
}
