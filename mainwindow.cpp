#include "mainwindow.h"
#include "ui_mainwindow.h"
#define xlength  1024
QList<QVector<double> > value_lofar;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    CustomPlot = ui->widget_2;
    //将定时器的计时信号与updateGL()绑定
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(50);

     F_domain_init();
     Bars_domain_init();
     T_domain_init();
     //fileread();

}
int MainWindow::fileread()
{


    char mp3file[256] = {0};
    qint64 sum = 0;

    QFile file("/home/jialf/qt_project/myplot/myplot/music.wma");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Unbuffered))
    {
        qDebug() << "Open file failed.";
        return -1;
    } else {

        QFile file2("/home/jialf/qt_project/myplot/myplot/music111.wma");
        if (!file2.open(QIODevice::WriteOnly))
        {
            qDebug() << "Open file failed.";
            return -1;
        } else {
            while (!file.atEnd())
            {
                sum++;
                file.read(mp3file, 256);
                file2.write(mp3file, 256);
                qDebug() << mp3file;
            }
        }
        qDebug() << sum;
        file.close();
        file2.close();
    }
    return 0;
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update()
{
    QVector<double> data;
     static double f = qrand()%100;
    f = f +2;
    for(int i=0;i<xlength;i++)
    {
        data << 50+50*sin(2*3.14159*f*i/128);
    }
    fft.fft_data.clear();
    fft.fft_calculate(data);
    F_show(fft.fft_data);
    Bars_show(fft.fft_data);
    T_Show(data);

}

void MainWindow::F_domain_init()
{
    fp3 = ui->widget; //创建一个画图指针
    fp3->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);//可拖拽+可滚轮缩放
    m_pColorMap = new QCPColorMap(fp3->xAxis,fp3->yAxis);
    m_pColorMap->data()->setSize(xlength+1,51);//设置整个图（x,y）点数
    m_pColorMap->data()->setRange(QCPRange(0,xlength),QCPRange(0,100));//setRange是设置X轴以及Y轴的范围
    m_pColorMap->setGradient(QCPColorGradient::gpJet);//设置默认渐进色变化（可在QCPColorGradient中查看）
    m_pColorMap->rescaleDataRange(true);
   // 立即刷新图像
    fp3->rescaleAxes();//自适应大小
   // ui->widget->replot();
}
void MainWindow::F_show(QVector<double> data)   //显示lofar瀑布图
{
    if(value_lofar.size()>49)
    {
        value_lofar.removeLast();  //当lofar累积到了50个，删除最后面的数据，防止绘图溢出绘图区域
    }
    value_lofar.prepend(data);//新来的数据一直往前面累加
    for (int i=0;i<value_lofar.size();i++)
    {
        for(int j=0;j<xlength;j++)
        {
            m_pColorMap->data()->setCell(j,i,value_lofar[i][j]);
        }
    }
    m_pColorMap->rescaleDataRange(true);
    fp3->rescaleAxes();//自适应大小
    ui->widget->replot();
}
void MainWindow::Bars_domain_init()
{
    QCPAxis *keyAxis = ui->widget_QCPBars->xAxis;
    QCPAxis *valueAxis = ui->widget_QCPBars->yAxis;
    fossil = new QCPBars(keyAxis, valueAxis);  // 使用xAxis作为柱状图的key轴，yAxis作为value轴

    fossil->setAntialiased(false); // 为了更好的边框效果，关闭抗齿锯
    fossil->setName("Fossil fuels"); // 设置柱状图的名字，可在图例中显示
    fossil->setPen(QPen(QColor(0, 168, 140).lighter(130))); // 设置柱状图的边框颜色
    fossil->setBrush(QColor(0, 168, 140));  // 设置柱状图的画刷颜色


    keyAxis->setRange(0, xlength);               // 设置范围
    keyAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    valueAxis->setRange(0, 100);
}
void MainWindow::Bars_show(QVector<double> fossilData)
{
    QVector<double> ticks;
    for(int i=1;i<=xlength;i++)
    {
        ticks <<  i;
    }
    fossil->setData(ticks,fossilData);
    ui->widget_QCPBars->replot();
}

void MainWindow::T_domain_init()
{
    CustomPlot->addGraph();
    CustomPlot->graph(0)->setPen(QPen(Qt::red));

    //CustomPlot->xAxis->setLabel("t");
    //CustomPlot->yAxis->setLabel("mV");

    CustomPlot->xAxis->setRange(0,xlength);
    CustomPlot->yAxis->setRange(0,100);
    CustomPlot->replot();
}
void MainWindow::T_Show(QVector<double> data)
{
    QVector<double> xx;
    for(int i=0;i<xlength;i++)
    {
        xx <<i;
    }
    CustomPlot->graph(0)->setData(xx,data);
    CustomPlot->replot();
}






