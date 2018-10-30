function start() {
    var reDrawGraphicFrequency = 10;
    var frequency = 100;
    var step = 250;
    var NumberOfStep = 0;
    var speedOfColorChanges = 1;

    var posX = 0;
    var posY = posX;

    var ctx = document.getElementById('myField').getContext('2d');
    google.charts.load('current', { 'packages': ['corechart'] });
    var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));

    var smt = [['StepCount', 'Value of average distance']];
    var particle = document.getElementById("particle");
    particle.style.height = String(step) + 'px';
    particle.style.width = String(step) + 'px';
    var cont = document.getElementById("place");
    var lY = document.getElementById("linX");
    var lX = document.getElementById("linY");
    var arr = [];
    for (var i = 0; i < 500; i++) {
        arr[i] = [];
        for (var j = 0; j < 500; j++)
            arr[i][j] = Number(0);
    }

    var sum = 0;
    var sumX = 0;
    var sumY = 0;
    var rand;
    var dist;
    var data;


    var lenses = [];
    var arrX = [];
    var arrY = [];

    var options =
        {
            title: 'Graphic',
            curveType: 'function',
            legend: { position: 'bottom' }
        }

    
        function nextPos() {
        reColor();
        if (rand == 1) { posX += step; }
        if (rand == 2) { posX -= step; }
        if (rand == 3) { posY += step; }
        if (rand == 4) { posY -= step; }

        if (posX < 0) { posX = 0 }
        if (posX > cont.clientWidth - particle.clientWidth) { posX = cont.clientWidth - particle.clientWidth; }
        if (posY < 0) { posY = 0 }
        if (posY > cont.clientHeight - particle.clientHeight) { posY = cont.clientHeight - particle.clientHeight; }
    }

    function reColor() {
        arr[posX][posY] += speedOfColorChanges;
        if (arr[posX][posY] <= 255) {
            ctx.fillStyle = "rgb(0," + String(arr[posX][posY]) + ",0)";
        }
        else {
            if (arr[posX][posY] <= 510) {
                ctx.fillStyle = "rgb(" + String(arr[posX][posY] - 255) + ",255,0)";
            }
            else {
                ctx.fillStyle = "rgb(255," + String(715 - arr[posX][posY]) + ",0)";
            }
        }

        ctx.fillRect(posX, posY, step, step);
    }

    function reDrawGraphic() {
        smt.push([(lenses.length / frequency).toFixed(1) + 'sec', sum]);
        google.charts.setOnLoadCallback(drawChart);
    }

    function drawChart() {
        data = google.visualization.arrayToDataTable(smt);
        chart.draw(data, options);
    }

    particle.style.top = posY + 'px';
    particle.style.left = posX + 'px';
    particle.style.visibility = "visible";

    function frame() {
        nextPos();
        NumberOfStep++;
        dist = Math.sqrt(Math.pow((cont.clientHeight / 2) - posX + step / 2, 2) + Math.pow((cont.clientHeight / 2) - posY + step / 2, 2));
        lenses.push(dist);

        arrX.push(posX + step / 2);
        arrY.push(posY + step / 2);

        for (var i = 0; i < lenses.length; i++) {
            sum += lenses[i];
            sumX += arrX[i];
            sumY += arrY[i];
        }

        sum /= lenses.length;
        sumX /= lenses.length;
        sumY /= lenses.length;

        document.toWrite.cout.value = dist.toFixed(3);
        document.toWrite.steps.value = NumberOfStep;
        document.toWrite.averag.value = sum.toFixed(3);
        lY.style.height = (sumY + 10).toFixed(1) + 'px';
        lX.style.width = (sumX + 10).toFixed(1) + 'px';
    

        rand = Math.floor(Math.random() * (5) + 1);

        particle.style.top = posY + 'px';
        particle.style.left = posX + 'px';

        if (NumberOfStep % reDrawGraphicFrequency == 0)
            reDrawGraphic();
            
    }

    var id = setInterval(frame, 0);
}
