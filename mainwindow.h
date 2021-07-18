#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QTime>
#include <QTimer>
#include <QSound>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <fft.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Graph_Show(QCustomPlot *CustomPlot);
    void F_domain_init();
    void F_show(QVector<double> data);
    void Bars_domain_init();
    void Bars_show(QVector<double> fossilData);
    void T_domain_init();
    void T_Show(QVector<double> data);
    int fileread();
    QCustomPlot * fp3;
    QCPColorMap * m_pColorMap;
    QCPBars *fossil;
    QCustomPlot *CustomPlot;
    fft_trans fft;
private:
    Ui::MainWindow *ui;

private slots:
    void update();
};

#endif // MAINWINDOW_H
