#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <vector>
#include "dislin.h"

using namespace std;

const int N = 2;

class PointData
{    
public:
    double data[N];
    float x;
    PointData()
    {
        memset(data, 0, N * sizeof(double));
    };

    double & operator[](unsigned int index)
    {
        if (index >= N)
            throw out_of_range("index out of range");
        return data[index];
    }

    PointData operator + (PointData v1)
    {
        PointData res;
        for(int i = 0; i < N; i++)
            res[i] = (*this)[i] + v1[i];
        return res;
    }

    PointData operator - (PointData v1)
    {
        PointData res;
        for(int i = 0; i < N; i++)
            res[i] = (*this)[i] - v1[i];
        return res;
    }

    PointData operator * (double v1)
    {
        PointData res;
        for(int i = 0; i < N; i++)
            res[i] = data[i] * v1;
        return res;
    }
};

PointData f(PointData p)
{
    PointData res;
    res[0] = pow(p[1], 3.);  
    res[1] = -p[0];
    return res;
}

class RK
{
private:
    PointData k[4];
    double beginX, endX;
    PointData nowPoint;
    double eps;
    double error;

public:

    void MRK()
    {
        getData();
        
        double h;
        std::vector <PointData> line;
        double xa = beginX, xb = endX;
        
        h = (endX - beginX) / 1000.;
        
        while (xa < xb)
        { 
            h = step(h);
            nowPoint = method(h);
            nowPoint.x = xa;
            line.push_back(nowPoint);
            xa += h;
        }        

        draw(line);
    }

    void getData()
    {
        ifstream inp("inputData.txt");
        inp >> beginX >> endX >> eps;
        for (int i = 0; i < N; i++)
            inp >> nowPoint[i];
        inp.close();
    }

    double step(double oldStep)
    {
        double newStep, del, error;
        newStep = oldStep;
        PointData smallStep, bigStep;

        do
        {
            smallStep = method(newStep);
            bigStep = method(newStep * 2.);

            del = 0;
            for (int i = 0; i < N; i++)
                del += pow((smallStep[i] - bigStep[i]) / eps, 2.);

            error = pow(del / N, 1. / 2.);

            newStep = 0.9 * newStep * abs(pow(1./error, 1. /5.));
        } while (error > 1);

        return newStep;
    }

    PointData method(double h)
    {
        PointData res;
        k[1] = f(nowPoint);
        k[2] = f(nowPoint + k[1] * (1. / 3.) * h);
        k[3] = f(nowPoint - (k[1] * (1. / 3.) + k[2]) * h);
        k[4] = f(nowPoint + (k[1] - k[2] + k[3]) * h);
        res = nowPoint + (k[1] + k[2] * 3. + k[3] * 3. + k[4]) * (h / 8.);
        return res;    
    }

    void draw(std::vector <PointData> line)
    {
        int n = line.size() - 1;
        
        float *abscissOfPoint = new float [line.size()];
        float *ordinatOfPoint = new float [line.size()];

        for(int i = 0; i < line.size(); i++)
        {
            ordinatOfPoint[i] = line[i][0];
            abscissOfPoint[i] = line[i].x;
        }

        double y_min, y_max;        
        
        metafl ("xwin");

            disini ();        
        for(int i = 0; i < 2; i++)
        {
            erase();
            sendbf();
            axspos (450, 1800);
            axslen (2200, 1200);


            ticks  (9, "x");
            ticks  (10, "y");
            
            cout << n << endl;

            y_min = ordinatOfPoint[0];
            y_max = ordinatOfPoint[0];

            for (int i = 1; i < n; i++)
            {
                if (ordinatOfPoint[i] > y_max)
                    y_max = ordinatOfPoint[i];
                if (ordinatOfPoint[i] < y_min)
                    y_min = ordinatOfPoint[i];
            }

            titlin ("Demonstration of CURVE", 3);

            for(int j = 0; j <n; j++)
            {
                abscissOfPoint[j]+=0.1;
            }
            graf   (abscissOfPoint[0], abscissOfPoint[n], abscissOfPoint[0], 
                (abscissOfPoint[n] - abscissOfPoint[0]) / 10, y_min, y_max + (y_max - y_min) / 200,
                    y_min, (y_max - y_min) / 10);
            setrgb (0.7, 0.7, 0.7);
            grid   (1, 1);


            color  ("fore");
            height (50);
            title  ();
            color("red");
            curve  (abscissOfPoint, ordinatOfPoint, n); 
            for(int lol = 0; lol <= 100000; lol++)
            {
                int lal;
                lal++;
            }
        }
        disfin ();
    }
};



int main()
{   
    RK met;

    met.MRK();

    return 0;
}