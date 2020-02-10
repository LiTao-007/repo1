#include "mainview.h"
#include <QApplication>

//超级用户 admin 密码 admin
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("windows"); //设置界面风格为window风格
    //QApplication::setStyle("WindowVista");
    MainView w;
    w.show();

    return a.exec();
}
