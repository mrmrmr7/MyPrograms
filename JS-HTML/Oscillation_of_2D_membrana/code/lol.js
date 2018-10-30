var data = null;
var graph = null;
var t = 2;

data = new vis.DataSet();
var options = 
{
    width:  '600px',
    height: '600px',
    style: 'surface',
    showPerspective: true,
    showGrid: false,
    showShadow: false,
    showAnimationControls: true,
    keepAspectRatio: true,
    verticalRatio: 0.5,
    animationInterval: 10, // milliseconds
    animationPreload: true
};

var axisStep = 0.0002;
var timeStep = 0.00005;
var fieldWidth = 2;
var fieldHeight = 3;
var layers = [];
var dt = timeStep * timeStep;
var dx = axisStep * axisStep;
var dy = dx;
var width = fieldWidth / axisStep;
var length = fieldHeight / axisStep;
var scale = 1 / axisStep;
var steps = 3000;
var a = 1;

for(var k = 0; k <= steps + 2; k++)
{   layers.push([]);
    for(var i = 0; i <= width;i++)
    {
        layers[k].push([]);
        for(var j = 0; j <= length; j++)
        {
            layers[k][i].push(0);
        }
    }
}

function makeFirstSteps()
{
    for(var i = 1; i < width; i++)
        for(var j = 1; j<length; j++)
            //layers[0][i][j]=(i/scale)*(j/scale)*(2.-i/scale)*(3.-j/scale)/64.;
            layers[0][i][j]=(Math.sin(i/50) * Math.cos(j/50) * 50 + 50);

    for(var i = 1; i < width; i++)
        for(var j = 1; j< length; j++)
            layers[1][i][j]=layers[0][i][j];
}

function makeNextStep()
{
    
    //dt = timeStep * timeStep;
    for(var i = 1; i < width; i++)
        for(var j = 1; j < length; j++)
            layers[t][i][j] = a * (dt/dx)*((layers[t-1][i+1][j]-2*layers[t-1][i][j]+layers[t-1][i-1][j])
                            + (layers[t-1][i][j+1] - 2*layers[t-1][i][j] + layers[t-1][i][j-1])) + 2 * layers[t-1][i][j] - layers[t-2][i][j];
    t++;
}

function printDataToGraph()
{
    for(var t = 0; t < steps; t++)
        for(var i = 0; i <= width; i++)
            for(var j = 0; j <= length; j++)
                data.add([{x:i/scale,y:j/scale,z:layers[t][i][j],filter:t*timeStep}]);
}

function setTimeStep()
{
    timeStep = 1 * axisStep / (Math.sqrt(2*a));
    console.log(timeStep);
}

function drawVisualization() {
    makeFirstSteps();
    setTimeStep();

    for(var i = 0; i < steps; i++)
        makeNextStep();

    //printDataToGraph();

    console.log(layers);
    
    var container = document.getElementById('mygraph');
    graph = new vis.Graph3d(container, data, options);
}