#include "membrana.h"
#include <cmath>
#include <iostream>

Membrana::Membrana()
{
      drawVisualization();
}
\


void Membrana::makeFirstSteps()
{
    for(int i = 1; i < width; i++)
    {
        for(int j = 1; j < length; j++)
        {
            //layers[0][i][j]=(i/scale)*(j/scale)*(2.-i/scale)*(3.-j/scale)/64.;
            layers[0][i][j]=sin(i)*100;
        }
    }
    for(int i = 1; i < width; i++)
        for(int j = 1; j< length; j++)
            layers[1][i][j]=layers[0][i][j];
}

void Membrana::makeNextStep()
{
    for(int i = 1; i < width; i++)
        for(int j = 1; j < length; j++)
        {
            layers[t][i][j] = a * (dt/dx)*((layers[t-1][i+1][j]-2*layers[t-1][i][j]+layers[t-1][i-1][j])
                            + (layers[t-1][i][j+1] - 2*layers[t-1][i][j] + layers[t-1][i][j-1])) + 2 * layers[t-1][i][j] - layers[t-2][i][j];
        }
    t++;
}

void Membrana::setTimeStep()
{
    timeStep = 1 * axisStep / (sqrt(2*a));
}

void Membrana::drawVisualization() {
    makeFirstSteps();

    for(int i = 0; i < steps; i++)
        makeNextStep();
}
