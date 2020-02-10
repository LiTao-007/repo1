#include "excleedit.h"

ExcleEdit::ExcleEdit()
{

}

/***********************************
 * 函数功能：设置一级标题
 * worksheet:当前工作表格
 * var：单元格范围
 * value：一级标题名称
************************************/
void ExcleEdit::SetTitle1(QAxObject *worksheet,const QVariant &var,const QVariant &value)
{
    QAxObject *range=worksheet->querySubObject("Range(const QString&)",var); //获取区域
    range->setProperty("MergeCells",true); //设置单元格可以合并
    range->setProperty("Value",value);     //设置单元格值
    delete range;
}

/***********************************
 * 函数功能：设置二级标题
 * worksheet:当前工作表格
 * var：单元格范围
 * value：二级标题名称
************************************/
void ExcleEdit::SetTitle2(QAxObject *worksheet,const QVariant &var,const QVariant &value)
{
    QAxObject *range=worksheet->querySubObject("Range(const QString&)",var); //获取区域
    range=worksheet->querySubObject("Range(const QString&)",var);
    range->setProperty("Value",value);
    delete range;
}

/***********************************
 * 函数功能：按颜色序号设置背景色
 * worksheet:当前工作表格
 * var：单元格范围 如：A1:A1
 * value：颜色序号
************************************/
void ExcleEdit::SetInteriorColor(QAxObject *worksheet,const QVariant &var,const QVariant &value)
{
    QAxObject *range=worksheet->querySubObject("Range(const QString&)",var); //获取区域

    QAxObject *interior=range->querySubObject("Interior");
    interior->setProperty("ColorIndex",value);      //按颜色序号进行颜色填充
    delete interior;
    delete range;
}

/***********************************
 * 函数功能：设置字体属性
 * worksheet:当前工作表格
 * var：单元格范围
 * value1：加粗true或者false
 * value2：颜色序号
 * size: 字体大小
************************************/
void ExcleEdit::SetFontProperty(QAxObject *worksheet,const QVariant &var,const QVariant &value1,const QVariant &value2,const QVariant &size){
    QAxObject *range=worksheet->querySubObject("Range(const QString&)",var); //获取区域

    QAxObject *font = range->querySubObject("Font");    //获取单元格字体
    font->setProperty("Name", QStringLiteral("微软雅黑"));//设置单元格字体
    font->setProperty("Bold",value1);   //设置字体加粗
    font->setProperty("ColorIndex",value2);   //设置字体颜色
    font->setProperty("Size",size);     //字体大小

    delete font;
    delete range;
}

/***********************************
 * 函数功能：设置单元格属性
 * worksheet:当前工作表格
 * var：单元格范围
 * value1：是否自动换行
 * value2：列宽
************************************/
void ExcleEdit::SetCellProperty(QAxObject *worksheet,const QVariant &var,const QVariant &value1,const QVariant &value2)
{
   QAxObject *range=worksheet->querySubObject("Range(const QString&)",var); //获取区域

   range->setProperty("WrapText",value1);       //设置自动换行
   range->setProperty("ColumnWidth",value2);    //列宽
   range->setProperty("HorizontalAlignment", -4108);//水平对齐：默认＝1,居中＝-4108,左＝-4131,右＝-4152
   range->setProperty("VerticalAlignment", -4108);  //垂直对齐：默认＝2,居中＝-4108,左＝-4160,右＝-4107

   delete range;
}

/***********************************
 * 函数功能：获取Excel表的行数
 * worksheet: 当前工作表格
 * 返回：int类型
************************************/
int ExcleEdit::GetRowNums(QAxObject *worksheet)
{
    int rownum;
    QAxObject * range = worksheet->querySubObject("UsedRange");
    QAxObject * rows = range->querySubObject("Rows");

    rownum = rows->property("Count").toInt();

    delete rows;
    delete range;
    return rownum;
}

/***********************************
 * 函数功能：获取Excel表的列数
 * worksheet: 当前工作表格
 * 返回：int类型
************************************/
int ExcleEdit::GetColumnNums(QAxObject *worksheet)
{
    int colnum;
    QAxObject * range = worksheet->querySubObject("UsedRange");
    QAxObject * columns = range->querySubObject("Columns");

    colnum = columns->property("Count").toInt();

    delete columns;
    delete range;
    return colnum;
}

/***********************************
 * 函数功能：将Excel数据读出指定区域
 * worksheet: 当前工作表格
 * var：单元格范围
 * 返回：QVariant类型
************************************/
QVariant ExcleEdit::ReadData(QAxObject *worksheet,const QVariant &var)
{
   QVariant ret;
   QAxObject *range=worksheet->querySubObject("Range(const QString&)",var); //获取区域

   ret = range->dynamicCall("Value()"); //获取值
   //ret = range->property("Value");
   delete range;
   return ret;
}

/***********************************
 * 函数功能：将Excel数据全部读出
 * worksheet: 当前工作表格
 * 返回：QVariant类型
************************************/
QVariant ExcleEdit::ReadAllData(QAxObject *worksheet)
{
    QVariant var;
    QAxObject *range=worksheet->querySubObject("UsedRange"); //获取全部区域

    var = range->dynamicCall("Value()"); //获取值
    delete range;
    return var;
}

/***********************************
 * 函数功能：将Excel数据全部读出
 * worksheet: 当前工作表格
 * data:存放读出的数据 QList<QList<QVariant>>
************************************/
void ExcleEdit::ReadAllData(QAxObject *worksheet,QList<QList<QVariant>> &data)
{
    QVariantToListListQVariant(ReadAllData(worksheet),data);
}

/***********************************
 * 函数功能：将数据写入EXCEL
 * worksheet: 当前工作表格
 * var：单元格范围
 * value：数据值
 * 备注：主要是单个单元格写入
************************************/
void ExcleEdit::WriteData(QAxObject *worksheet,const QVariant &var,const QVariant &value)
{
    QAxObject *range=worksheet->querySubObject("Range(const QString&)",var); //获取区域
    range->setProperty("Value",value);
    delete range;
}

/***********************************
 * 函数功能：将tableView数据批量写入EXCEL BatchWriteData
 * tableView: QTableView对象
 * worksheet: 当前工作表格
 * colNum: tableView表格列数
************************************/
void ExcleEdit::BatchWriteData(const QTableView *tableView,QAxObject *worksheet,int colNum)
{
    QAbstractItemModel *model = tableView->model();
    int rowNum=0; //统计数据行数
    QList<QList<QVariant> > datas; //存放tableView的数据

    // 数据写入QList
    while(!model->data(model->index(rowNum,colNum-1)).isNull())
    {
       QList<QVariant> rows;
       rows.append(rowNum+1); //序号
       for(int j=0;j<colNum;j++)
       {
           rows.append(model->data(model->index(rowNum,j)));
       }
       datas.append(rows);
       rowNum++;
    }

    //把QList<QList<QVariant> > 转为QVariant,用于快速写入的
    QVariant var = ListListQVariantToQVariant(datas);

    QString row = Get26AlphabeticCapital(colNum+1)+QString::number(rowNum+1); //写入单元格区域的最后一个单元格
    QAxObject *user_range = worksheet->querySubObject("Range(const QString&)","A2:"+row);
    user_range->setProperty("WrapText", false);
    user_range->setProperty("HorizontalAlignment", -4108);//水平对齐：默认＝1,居中＝-4108,左＝-4131,右＝-4152
    user_range->setProperty("VerticalAlignment", -4108);//垂直对齐：默认＝2,居中＝-4108,左＝-4160,右＝-4107

    user_range->setProperty("Value", var); //数据写入
    delete user_range;
}

/***********************************
 * 函数功能：把QList<QList<QVariant> > 转为QVariant
 * data:待转换数据
************************************/
QVariant ExcleEdit::ListListQVariantToQVariant(const QList<QList<QVariant>> &data)
{
    QVariantList vars;
    const int rows = data.size();
    for(int i=0;i<rows;++i)
    {
        vars.append(QVariant(data[i]));
    }
   return QVariant(vars);
}

/***********************************
 * 函数功能：把QVariant 转为 QList<QList<QVariant> >
 * var:待转换数据
 * data:存放转换后的数据
************************************/
void ExcleEdit::QVariantToListListQVariant(const QVariant &var, QList<QList<QVariant>> &data)
{
    QVariantList varRows = var.toList();
    if(varRows.isEmpty())
    {
        return;
    }
    const int rowCount = varRows.size();
    QVariantList rowData;
    for(int i=0;i<rowCount;++i)
    {
        rowData = varRows[i].toList();
        data.push_back(rowData);
    }
}
/***********************************
 * 函数功能：获取QList<QVariant>中数据转 QList<QString>
 * var:待转换数据
 * data:存放转换后的数据
************************************/
void ExcleEdit::ListQVariantToListQString(const QList<QVariant> &var, QList<QString> &data){
    int RowNum = var.size();
    QString rowData;
    for(int i=0;i<RowNum;i++){
        rowData=var.at(i).toString();
        data.push_back(rowData);
    }
}
/***********************************
 * 函数功能：获取大写字母1->A  26->Z
 * colNum:待转换数据
************************************/
QString ExcleEdit::Get26AlphabeticCapital(int colNum)
{
    QChar ch = colNum + 0x40;//A对应0x41
    return QString(ch);
}
