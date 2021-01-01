#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    setWindowTitle(tr("风力发电气动平衡检测系统"));
    //设置图窗口的最小大小
    setMinimumSize(500, 400);
    //私有数据初始化
    sourcedata.clear();
    begintime = 0;
    endtime = 100;
    begindis = 0;
    enddis = 0;
    beginDraw = false;

    //显示图像
    createChart(); //创建图表
    prepareData(); //生成数据
    updataFromChart(); //从图表中获得属性值并刷新到界面显示
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createChart(){ //创建图表的各个部件
    //创建图表
    QChart * chart = new QChart();
    chart->setTitle("源数据曲线");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    //创建折线图
    QLineSeries * series = new QLineSeries();
    series->setName("源数据曲线");
    curseries = series; //当前序列

    //折线序列的线条设置
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    series->setPen(pen);

    chart->addSeries(series);

    //创建坐标轴
    QValueAxis * axisX = new QValueAxis; //x轴
    curAxis = axisX; //当前坐标轴
    axisX->setRange(0, 10); //设置坐标轴范围
    axisX->setLabelFormat("%d"); //标签格式
    axisX->setTickCount(11); //主分隔个数
    axisX->setMinorTickCount(4); //最少主分隔个数
    axisX->setTitleText("时间(秒)"); //x轴标题

    QValueAxis * axisY = new QValueAxis; //y轴
    axisY->setRange(-2, 2);
    axisY->setTitleText("源数据");
    axisY->setLabelFormat("%.3f");
    axisY->setTickCount(5);
    axisY->setMinorTickCount(4);

    //为序列设置坐标值
    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);
}

void MainWindow::prepareData() { //序列添加数值
    QLineSeries * series = (QLineSeries *)ui->chartView->chart()->series().at();
    series->clear(); //清除历史数据
    qsrand(Qtime::currentTime().second()); //随机数初始化
    qreal t = 0, y, intv = 0.1, rd;
    int cnt = 100;
    for (int i = 0; i < cnt; ++i) {
        rd = (qrand() % 10) - 5; //随机数：-5~5
        y = qSin(t) + rd / 50;
        series->append(t, y);
        t += intv;
    }
}

void MainWindow::updataFromChart() { //从图表上获取数据更新界面显示
    QChart * achart = ui->charView->chart(); //获取chart
    ui->editTitle->setText (achart->title()); //图表标题
    QMargins mg = achart->margins(); //边距
    ui->spinMarginLeft->setValue(mg.left());
    ui->spinMarginRight->setValue(mg.right());
    ui->spinMarginTop->setValue(mg.top());
    ui->spinMarginBottom->setValue(mg.bottom());
}
