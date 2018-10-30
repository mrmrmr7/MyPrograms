function start() {
    var a = [];
    var wid = 600;
    var hei = 600;
    var step = 1;
    var x = Math.floor(Math.random() * wid);
    var y = Math.floor(Math.random() * wid);
    var countOfSteps = 50000000;
    var speedOfColorize = 1;
    var walls = [[[0,0],[0,hei]],//из верхнего левого в нижний левый
                [[0,hei],[wid,hei]], // из нижнего левого в нижний правый
                [[wid,hei],[wid,0]], // из верхнего правого в нижний правый
                [[0,0],[wid,0]]]; // из верхнего левого в верхний правый
    
    drawWalls();
    
    var countOfWalls = walls.length;
    
    x = 300;
    y = 300;

    document.getElementById('myField').width = wid;
    document.getElementById('myField').height = hei;

    for (var i = 0; i < Number(wid); i++) {
        a[i] = [];
        for (var j = 0; j < Number(hei); j++)
            a[i][j] = 0;
    }

    for(var i = 1; i < countOfSteps; i++)
    {
            move();
            a[x][y]+=speedOfColorize;
    }

    drawField();
    drawFinalPoint();

    function drawWalls()
    {
        //var lineOfWalls = [[50,50],[450,50],[450,450],[50,450],[50,100],[400,100],[400,400],[150,400]];
        //[[300,300],[300,500],[500,500],[500,200],[200,200]];

        // for(var i = 0; i < lineOfWalls.length - 1; i++)
        // {
        //     if(lineOfWalls[i + 1][1] >= lineOfWalls[i][1])
        //     {
        //         walls.push([[lineOfWalls[i][0] - 5, lineOfWalls[i][1] - 5],[lineOfWalls[i + 1][0] + 5, lineOfWalls[i + 1][1] + 5]]);
        //     }
        //     else
        //     {
        //         walls.push([[lineOfWalls[i][0] + 5, lineOfWalls[i][1] + 5],[lineOfWalls[i + 1][0] - 5, lineOfWalls[i + 1][1] - 5]]);            
        //     }
        // }

        // walls.push([[320,500],[300,300]]);
        // walls.push([[320,480],[500,500]]);
        // walls.push([[480,250],[500,500]]);
        // walls.push([[240,250],[500,270]]); 
        // walls.push([[240,250],[260,550]]);
        // walls.push([[240,530],[550,550]]);
        // walls.push([[530,200],[550,550]]);
        // walls.push([[200,200],[530,220]]);
        //мини лабиринт

        walls.push([[300,0],[300,550]]);
        walls.push([[300,552],[300,800]]);
        //проскальзывание через стеночку
    }

    function move()
    {       
        var check;
        var mov;     
        mov = Math.floor(Math.random() * 4);
        if (mov == 0)
        {
            check = true;
            for(var j = 0; j < countOfWalls; j++)
                if((y >= walls[j][0][1] && y <= walls[j][1][1]) || (y >= walls[j][1][1] && y <= walls[j][0][1]))
                    if((x < walls[j][0][0]) && ((x + step) >= walls[j][0][0]) || (x < walls[j][1][0]) && ((x + step) >= walls[j][1][0]))
                        check = false;

            if(check  == true)
                x+=step;  
        }

        if(mov == 1)
        {                
            check = true;
            for(var j = 0; j < countOfWalls; j++)
                if((y >= walls[j][0][1] && y <= walls[j][1][1]) || (y >= walls[j][1][1] && y <= walls[j][0][1]))
                    if((x >= walls[j][1][0]) && ((x - step) < walls[j][1][0]) || (x >= walls[j][0][0]) && ((x - step) < walls[j][0][0]))
                        check = false;

            if(check  == true)
                x-=step;
        }

        if (mov == 2)
        {
            check = true;
            for(var j = 0; j < countOfWalls; j++)
                if((x >= walls[j][0][0] && x <= walls[j][1][0]) || (x >= walls[j][1][0] && x <= walls[j][0][0]))
                    if((y > walls[j][1][1]) && ((y - step) <= walls[j][1][1]) || (y > walls[j][0][1]) && ((y - step) <= walls[j][0][1]))
                        check = false;

            if(check  == true)
                y-=step;
        }

        if (mov == 3)
        {
            check = true;
            for(var j = 0; j < countOfWalls; j++)
                if((x >= walls[j][0][0] && x <= walls[j][1][0]) || (x >= walls[j][1][0] && x <= walls[j][0][0]))
                    if((y < walls[j][0][1]) && ((y + step) >= walls[j][0][1]) || (y < walls[j][1][1]) && ((y + step) >= walls[j][1][1]))
                        check = false;
                        
            if(check  == true)
                y+=step;
        }
    }

    function drawField()
    {    
        var ctx = document.getElementById('myField').getContext('2d');  
        for (var k = 0; k < wid; k++) {
            for (var j = 0; j < hei; j++) {
                if (a[k][j] <= 255) {
                    ctx.fillStyle = "rgb(0," + String(a[k][j]) + ",0)";
                }
                else {
                    if (a[k][j] <= 510) {
                        ctx.fillStyle = "rgb(" + String(a[k][j] - 255) + ",255,0)";
                    }
                    else {
                        ctx.fillStyle = "rgb(255," + String(765 - a[k][j]) + ",0)";
                    }
                }
                ctx.fillRect(k, j, 1, 1);
            }
        }
    }

    function drawFinalPoint()
    {
        var ctx = document.getElementById('myField').getContext('2d');  
        ctx.fillStyle = "rgb(0,0,255)";
        ctx.fillRect(x - 3, y - 3, 6, 6);
    }

    console.log("done");
}
