#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QtCharts>

//宏定义使用QChart命名空间
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

//主窗口类
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createChart(); //创建图表的基本组件
    void prepareData(); //更新数据
    void updataFromChart(); //从图表更新到界面：读取图表的属性并更新到界面
private:
    Ui::MainWindow * ui;

    QMap<long long, double> sourcedata; //主成图源数据：时间戳+对应的距离数据
    long long begintime, endtime; //时间显示区间[begintime, endtime]
    double begindis, enddis; //距离显示区间[begindis, enddis]
    bool beginDraw; //是否开始绘图或者更新绘图

    QLineSeries * curseries; //当前操作的序列
    QValueAxis * curaxis; //当前操作的坐标轴

};

#endif // MAINWINDOW_H
