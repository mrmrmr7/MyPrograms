#ifndef MEMBRANA_H
#define MEMBRANA_H

class Membrana
{
public:
    Membrana();

    int t = 2;

    static constexpr float axisStep = 0.05;
    float timeStep = 0.02;
    float dx = axisStep * axisStep;
    float dt = timeStep * timeStep;
    static constexpr float fieldWidth = 2;
    static constexpr float fieldHeight = 3;
    static const int width = int(fieldWidth / axisStep);
    static const long int length = int(fieldHeight / axisStep);
    static const int steps = 800;
    float dy = dx;
    float scale = 1 / axisStep;
    float a = 1;
    float layers[steps + 2][width + 5][length + 5];


    void makeFirstSteps();

    void makeNextStep();

    void setTimeStep();

    void drawVisualization();
};

#endif // MEMBRANA_H
