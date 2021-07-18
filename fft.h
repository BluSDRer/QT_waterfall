#ifndef FFT_H
#define FFT_H
#include <QVector>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <QDebug>
#define N 1024
typedef struct{       //定义一个结构体表示复数的类型
    double real;
    double imag;
}complex;
typedef struct{       //定义一个结构体表示复数的类型
    double amplitude;
    double phase;
}ap;



class fft_trans
{
public:
     fft_trans();
    ~fft_trans();
     ap fft_calculate(QVector<double> data);
     void  change();
     void  transform();
     void  fft();
     void add(complex a,complex b,complex *c);

     void sub(complex a,complex b,complex *c);

     void mul(complex a,complex b,complex *c);
public:

     QVector<double> fft_data;
     ap amp_ph;
     complex x[N], *W;   //定义输入序列和旋转因子
     double l[N]={0};
     int size=N;   //定义数据长度
     double PI=3.14151926; //定义π 因为tan(π/4)=1 所以arctan（1）*4=π，增加π的精度
};

#endif // FFT_H
