#include <iostream> 
#include<cmath> 

using namespace std; 

int main() 
{ 
    int sum;
    int s[170];

    for(int i = 0; i < 170; i++)
        s[i] = 0;

    for (int i = 1; i <= 36; i++)
        for (int j = 1; j <= 36; j++)
            if(j != i)
                for(int k = 1; k <= 36; k++)
                    if(k != j && k != i)
                        for(int l = 1; l <= 36; l++)
                            if(l != i && l != j && l != k)
                                for (int m = 1; m <= 36; m++)
                                    if(m != i && m != j && m != k && m != l)
                                    {
                                        sum = i + j + k + l + m;
                                        s[sum]++;
                                    }

    int max = 15;
    int min = 15;
    for (int i = 15; i < 170; i++)
    {        
        if(s[i] > s [max])
            max = i;
        if(s[i] < s[min])
            min = i;
    }

    int step = (s[max] - s[min]) / 150;

    cout << "Sum: -  S rasst. : bez rasst : Gistogramma" << endl;
    for (int i = 15; i < 170; i++)
    {
        // cout.width(4);
        // cout << i << " - ";
        // cout.width(9);
        // cout << s[i] << " : ";
        // cout.width(9);
        // cout << s[i] / 120 << " : ";
        for(int j = (s[i] / step); j <=s[i]; j+=step)
            cout << "*";
        cout << endl;
    }


    system("pause");
}