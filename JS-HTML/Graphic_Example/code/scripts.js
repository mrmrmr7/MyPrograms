function f(_x)
{
	var res;
	res = Math.exp(-_x) - 0.001;
	return res;
}

function bisection(_left, _right, _eps)
{
	var root;
	var center;
	var stepCount = 0;
	
	do
	{
		center = (_left + _right) / 2.;
		if(f(_left)*f(center) < 0)
		{
			_right = center;
			root = (center + _right) / 2;
		}
		if(f(_right)*f(center) < 0)
		{
			_left = center;
			root = (_left + center) / 2;
		}
		stepCount++;
	}while(Math.abs(f(root)) > _eps);
    console.log("Bisection: " + root + " Step count: " + stepCount);
}

function df(_x)
{
	var res;
	res = (f(_x + 0.1) - f(_x)) / 0.1;
	return res; 
}

function dfs(_x,_lastX)
{
	var res;
	res = (f(_x) - f(_lastX)) / (_x - _lastX);
	return res;
}

function newton(_left, _right, _eps)
{
	var x = (_left + _right) / 2;
	var stepCount = 0;
	
	do
	{
		x = x - f(x) / df(x);
		stepCount++;
	}while(Math.abs(f(x)) > _eps);

    console.log("Newton: " + x + " Step count: " + stepCount);
}

function secut (_left,    _right,    _eps)
{
     var x = (_left + _right) / 2;
     var newX;
     var lastX = (_left + x) / 2;
     var stepCount = 0;

	do
	{
		newX = x - ((x - lastX) / (f(x) - f(lastX))) * f(x);
		lastX = x;
		x = newX;
		stepCount++;
	}while(Math.abs(f(newX)) > _eps);
	
    console.log("Secut: " + newX + " Step count: " + stepCount);
}

function start() 
{
    google.charts.load('current', { 'packages': ['corechart'] });
    var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));
    console.clear();
    
	var left = 1;
	var right = 20;
    var eps = 0.0001;
    bisection(left, right, eps);
	newton(left,right,eps);
	secut(left,right,eps);


    var smt = [['StepCount', 'Value of average distance']];


    var options =
        {
            title: 'Graphic',
            curveType: 'function',
            legend: { position: 'bottom' }
        }
    var x = left;

    while(x < right)
    {
        smt.push([x,Math.exp(-x) - 0.001]);
        x+=0.01;
    }

    google.charts.setOnLoadCallback(drawChart);

    function drawChart() {
        data = google.visualization.arrayToDataTable(smt);
        chart.draw(data, options);
    }
}
