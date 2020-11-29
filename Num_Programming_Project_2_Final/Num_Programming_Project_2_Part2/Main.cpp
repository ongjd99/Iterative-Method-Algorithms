/*
	Ong, Johnny

	September 30, 2020

	CS 3010.01 Numerical Methods
	Programming Project 2
*/

#include "Matrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	Matrix a;
	cout << "Will you be inputting a txt file? Y/N ";
	char ans;
	cin >> ans;
	cout << endl;
	if (toupper(ans) == 'Y')
	{
 		a.initFile();
	}
	else
	{
		a.init();
	}
	a.printAll();
	cout << "Performing Jacobi Iterative Method" << endl;
	cout << "----------------------------------" << endl;
	a.jacobi();

	cout << "Performing Gauss Seidel Method" << endl;
	cout << "----------------------------------" << endl;
	a.gauss();

	cout << endl;
	system("Pause");
	return 0;
}