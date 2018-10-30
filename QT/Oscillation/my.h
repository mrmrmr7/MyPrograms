#include <cmath>

class Membrana
{
public:
    double axisStep = 0.05;
    double timeStep = 0.02;
    double fieldWidth = 2;
    double fieldHeight = 3;
    double dx = axisStep * axisStep;
    double dt = timeStep * timeStep;
    double dy = dx;
    int width = fieldWidth / axisStep;
    int length = fieldHeight / axisStep;
    double scale = 1 / axisStep;
    const int steps = 300;
    int t = 2;
    double a = 1;
    double ***layers = new double**[steps + 2];

    void setPrimaryData()
    {
        for(int i = 0; i < width; i++)
        {
            layers[i] = new double*[width];
            for(int j = 0; j < length; j++)
            {
                layers[i][j] = new double[length];
            }
        }
    }

    void makeFirstSteps()
    {
        for(int i = 1; i < width; i++)
            for(int j = 1; j<length; j++)
                //layers[0][i][j]=(i/scale)*(j/scale)*(2.-i/scale)*(3.-j/scale)/64.;
                layers[0][i][j]=(sin(i/50) * cos(j/50) * 50 + 50);

        for(int i = 1; i < width; i++)
            for(int j = 1; j< length; j++)
                layers[1][i][j]=layers[0][i][j];
    }

    void makeNextStep()
    {
        for(int i = 1; i < width; i++)
            for(int j = 1; j < length; j++)
                layers[t][i][j] = a * (dt/dx)*((layers[t-1][i+1][j]-2*layers[t-1][i][j]+layers[t-1][i-1][j])
                        + (layers[t-1][i][j+1] - 2*layers[t-1][i][j] + layers[t-1][i][j-1])) + 2 * layers[t-1][i][j] - layers[t-2][i][j];
        t++;
    }

    void setTimeStep()
    {
        timeStep = 1 * axisStep / (sqrt(2*a));
    }

    void calculateData() {
        makeFirstSteps();
        setTimeStep();

        for(int i = 0; i < steps; i++)
            makeNextStep();
    }
};
