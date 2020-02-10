#ifndef EXCLEEDIT_H
#define EXCLEEDIT_H

#include <QVariant>
#include <ActiveQt/QAxObject>//Excel
#include <QDebug>//debug输出
#include <QDir>//保存路径
#include <QTableView>

class ExcleEdit
{
public:
    ExcleEdit();
    //设置标题
    void SetTitle1(QAxObject *worksheet,const QVariant &var,const QVariant &value); //一级标题可以合并单元格
    void SetTitle2(QAxObject *worksheet,const QVariant &var,const QVariant &value); //二级标题
    //设置单元格填充颜色
    void SetInteriorColor(QAxObject *worksheet,const QVariant &var,const QVariant &value);
    //设置字体
    void SetFontProperty(QAxObject *worksheet,const QVariant &var,const QVariant &value1,const QVariant &value2,const QVariant &size);
    //设置单元格属性
    void SetCellProperty(QAxObject *worksheet,const QVariant &var,const QVariant &value1,const QVariant &value2);

    //获取行 列数
    int GetRowNums(QAxObject *worksheet); //行数
    int GetColumnNums(QAxObject *worksheet);//列数

    //读数据
    QVariant ReadData(QAxObject *worksheet,const QVariant &var);        //指定区域返回 QVariant
    QVariant ReadAllData(QAxObject *worksheet);                         //全部数据返回 QVariant
    void ReadAllData(QAxObject *worksheet,QList<QList<QVariant>> &data);//全部数据返回 存放data

    //写入数据
    void WriteData(QAxObject *worksheet,const QVariant &var,const QVariant &value);
    void BatchWriteData(const QTableView *tableView,QAxObject *worksheet,int colNum);

    //转换函数
    QVariant ListListQVariantToQVariant(const QList<QList<QVariant>> &data);
    void QVariantToListListQVariant(const QVariant &var,QList<QList<QVariant>> &data);
    void ListQVariantToListQString(const QList<QVariant> &var, QList<QString> &data);

    //获取大写字母1->A  26->Z
    QString Get26AlphabeticCapital(int colNum);
};

#endif // EXCLEEDIT_H
