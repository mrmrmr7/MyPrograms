#include <iostream> 
#include<cmath> 

using namespace std; 

int main() 
{ 
    int r1,r2,r3,r4,r5;
    int sum;
    int s[170];

    for(int i = 0; i < 170; i++)
        s[i] = 0;

    for (int i = 0; i < 1000000; i++)
    {
        r1 = rand() % 36 + 1;

        do
        {
            r2 = rand() % 36 + 1;
        } while (r2 == r1);

        do
        {
            r3 = rand() % 36 + 1;
        } while (r3 == r2 || r3 == r1);

        do
        {
            r4 = rand() % 36 + 1;
        } while (r4 == r3 || r4 == r2 || r4 == r1);

        do
        {
            r5 = rand() % 36 + 1;
        } while (r5 == r4 || r5 == r3 || r5 == r2 || r5 == r1);

        sum = r1 + r2 + r3 + r4 + r5;
        s[sum]++;
    }

    for(int i = 15; i < 170; i++)
        cout << i << " - " << s[i] << endl;

    int max = 16;
    int min = 15;
    for (int i = 0; i < 170; i++)
    {        
        if(s[i] > s [max])
            max = i;
        if(s[i] < s[min])
            min = i;
    }

    int step = (s[max] - s[min]) / 150;

    for (int i = 0; i < 170; i++)
    {
        for(int j = (s[i] / step); j <=s[i]; j+=step)
        {
            cout << "*";
        }
        cout << endl;
    }

    system("pause");
}