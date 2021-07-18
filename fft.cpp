#include "fft.h"

fft_trans::~fft_trans()
{

}
fft_trans::fft_trans()
{

}

void fft_trans::change()
{
    complex temp;
    unsigned short i=0,j=0,k=0;
    double t;
    for(i=0;i<size;i++)
    {
        k=i;
        j=0;
        t=(log(size)/log(2));
        while( (t--)>0 )
        {
            j=j<<1;
            j|=(k & 1);
            k=k>>1;
        }
        if(j>i)
        {
            temp=x[i];
            x[i]=x[j];
            x[j]=temp;
        }
    }
}
void fft_trans::transform()
{
    int i;
    W=(complex *)malloc(sizeof(complex) * size);
    for(i=0;i<size;i++)
    {
        W[i].real=cos(2*PI/size*i);
        W[i].imag=-1*sin(2*PI/size*i);
    }
}
void fft_trans::add(complex a,complex b,complex *c)
{
    c->real=a.real+b.real;
    c->imag=a.imag+b.imag;
}
void fft_trans::sub(complex a,complex b,complex *c)
{
    c->real=a.real-b.real;
    c->imag=a.imag-b.imag;
}
void fft_trans::mul(complex a,complex b,complex *c)
{
    c->real=a.real*b.real - a.imag*b.imag;
    c->imag=a.real*b.imag + a.imag*b.real;
}
void fft_trans::fft()
{
    int i=0,j=0,k=0,m=0;
    complex q,y,z;
    change();
    for(i=0;i<log(size)/log(2) ;i++)
    {
        m=1<<i;
        for(j=0;j<size;j+=2*m)
        {
            for(k=0;k<m;k++)
            {
                mul(x[k+j+m],W[size*k/2/m],&q);
                add(x[j+k],q,&y);
                sub(x[j+k],q,&z);
                x[j+k]=y;
                x[j+k+m]=z;
            }
        }
    }
}
ap fft_trans::fft_calculate(QVector<double> data)
{
    int i;
    for(i=0;i<N;i++)
    {
        x[i].real = data.at(i);
        x[i].imag = 0;
    }
    transform();//变换序列顺序
    fft();//蝶形运算
    double max = 0;
   for(i=0;i<size;i++)  //计算变换结果的模长
    {
        l[i]=sqrt(x[i].imag*x[i].imag+x[i].real*x[i].real);
        if(l[i] > max)
        {
            max = l[i];
        }

    }
   for(i=0;i<size;i++)  //计算变换结果的模长
    {
        fft_data<<(l[i]/max)*160;
    }
    free(W);

    return amp_ph;
}
