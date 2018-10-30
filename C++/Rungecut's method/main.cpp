#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

using namespace std;

const int N = 2;

class point
{    
double data[N];
public:
    point()
    {
        memset(data, 0, N * sizeof(double));
    };

    double & operator[](unsigned int index)
    {
        if (index >= N)
            throw out_of_range("index out of range");
        return data[index];
    }

    point operator + (point v1)
    {
        point res;
        for(int i = 0; i < N; i++)
            res[i] = (*this)[i] + v1[i];
        return res;
    }

    point operator - (point v1)
    {
        point res;
        for(int i = 0; i < N; i++)
            res[i] = (*this)[i] - v1[i];
        return res;
    }

    point operator * (double v1)
    {
        point res;
        for(int i = 0; i < N; i++)
            res[i] = data[i] * v1;
        return res;
    }
};

point f(point p)
{
    point res;
    res[0] = p[1];
    //res[1] = p[2];
    res[1] = -p[0];
    return res;
}

class RK
{
    point k[4];
    double err;
    point method(double h, point p)
    {
        point res;
        k[1] = f(p);
        k[2] = f(p + k[1] * (1. / 3.) * h);
        k[3] = f(p - (k[1] * (1. / 3.) + k[2]) * h);
        k[4] = f(p + (k[1] - k[2] + k[3]) * h);
        res = p + (k[1] + k[2] * 3. + k[3] * 3. + k[4]) * (h / 8.);
        return res;    
    }
public:
    void MRK(double eps, double x0, double x1, point p)
    {
        double h;
        h = (x1 - x0) / 1000.;
        for(int i = 0; i < 1000; i++)
        {
            p = method(h, p);
            cout << p[0] << endl;
        }
    }
};



int main()
{   
    double x0, x1, eps;
    point p;
    RK met;

    ifstream inp("input.txt");
    inp >> x0 >> x1;
    for (int i = 0; i < N; i++)
        inp >> p[i];
    inp.close();

    met.MRK(eps, x0, x1, p);

    return 0;
}