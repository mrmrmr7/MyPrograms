#include <iostream>

using namespace std;
int main(){
	int mass[171];
	int x1, x2, x3, x4, x5, x;
	for (int i = 0; i <= 170; i++){
		mass[i] = 0;
	}
	for (int j = 0; j < 10000000 ;j++)
	{
		x1 = 1 + rand() % 36;

		do {
			x2 = 1 + rand() % 36;
		} while (x2 == x1);
		do {
			x3 = 1 + rand() % 36;
		} while (x3 == x1 && x3 == x2);
		do {
			x4 = 1 + rand() % 36;
		} while (x4 == x1 && x4 == x2 && x4 == x3);
		do {
			x5 = 1 + rand() % 36;
		} while (x5 == x1 && x5 == x2 && x5 == x3 && x5 == x4);

		x = x1 + x2 + x3 + x4 + x5;
	//	if (j > 60000){
	//		cout << x << endl;
	//  }
		mass[x]++; 
	}
	for (int i = 0; i <= 170; i++){
		cout << i << "= " << mass[i] << endl;
	}
	cout << endl;
	cout << x1 << " " << x2 << " " << x3 << " " << x4 << " " << x5 << endl;
    cin >> x;
}