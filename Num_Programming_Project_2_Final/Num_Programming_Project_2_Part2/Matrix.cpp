/*
	Ong, Johnny

	September 30, 2020

	CS 3010.01 Numerical Methods
	Programming Project 2
*/

#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

Matrix::Matrix()
{
	matrix = new double* [1];

	numOfEquations = 0;
	stoppingError = 0;
}

Matrix::~Matrix()
{
	deleteMatrices();
}

void Matrix::deleteMatrices()
{
	for (int i = 0; i < numOfEquations; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

	matrix = nullptr;
}

void Matrix::init()
{
	cout << "Please enter the number of equations (n <= 10): ";
	int input = 0;
	numOfEquations = verifyInput(input);
	while (!(numOfEquations <= 10 && numOfEquations > 0))
	{
		cout << "Invalid number of equations. Try again." << endl;
		numOfEquations = verifyInput(input);
	}
	cout << endl;

	createMatrix();
	setBMatrix();
	setStoppingError();
	setSolutionMatrix();
}

void Matrix::initFile()
{
	cout << "Please enter the number of equations (n <= 10): ";
	int input = 0;
	numOfEquations = verifyInput(input);
	while (!(numOfEquations <= 10 && numOfEquations > 0))
	{
		cout << "Invalid number of equations. Try again." << endl;
		numOfEquations = verifyInput(input);
	}
	cout << endl;

	cout << "Enter filename (including .txt): ";
	string file;
	cin >> file;
	ifstream infile;
	infile.open(file);
	if (infile.fail())
	{
		cout << "Error; File could not be found. Try Again." << endl;
		initFile();
	}

	double data = 0;
	matrix = new double* [numOfEquations];
	while (!infile.eof())
	{
		for (int i = 0; i < numOfEquations; i++)
		{
			matrix[i] = new double[numOfEquations];
			for (int j = 0; j < numOfEquations + 1; j++)
			{
				infile >> data;
				if (j == numOfEquations)
				{
					b.push_back(data);
				}
				else
				{
					matrix[i][j] = data;
				}
			}
		}
	}
	setStoppingError();
	setSolutionMatrix();
}

void Matrix::createMatrix()
{
	cout << "Enter the coefficients for the equations (x1, x2, x3, x4,...,xn): " << endl;

	matrix = new double* [numOfEquations];
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << "Row " << i << ": ";
		matrix[i] = new double[numOfEquations];
		for (int j = 0; j < numOfEquations; j++)
		{
			double input = 0;
			matrix[i][j] = verifyInput(input);
		}
	}
}

void Matrix::setBMatrix()
{
	cout << "Enter values for B: " << endl;

	b.reserve(numOfEquations);
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << "B" << i << ": ";
		double input = 0;
		b.push_back(verifyInput(input));
	}
}

void Matrix::setSolutionMatrix()
{
	double input = 0;
	originalVector.reserve(numOfEquations);

	cout << "Enter starting solution: ";
	for (int i = 0; i < numOfEquations; i++)
	{
		originalVector.push_back(verifyInput(input));
	}
	x = originalVector;
	y = x;
}

void Matrix::setStoppingError()
{
	cout << "Enter a desired Stopping Error: ";
	stoppingError = verifyInput(stoppingError);
}

void Matrix::printAll()
{
	cout << "Printing Matrix" << endl;
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << "Row " << i << ": ";
		for (int j = 0; j < numOfEquations; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << b[i] << endl;
	}
	cout << endl;

	cout << "Printing Solution Matrix" << endl;
	cout << "[ ";
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << x.at(i) << " ";
	}
	cout << "]T" << endl;

	cout << "Print Euclidean norm: " << normVector() << endl;
	cout << endl;
}

void Matrix::printResults()
{
	cout << "Printing Solution Matrix" << endl;
	cout << "[ ";
	for (int i = 0; i < numOfEquations; i++)
	{
		cout << x[i] << " ";
	}
	cout << "]T" << endl;

	cout << "Print Euclidean norm: " << normVector() << endl;
	cout << endl;
}

int Matrix::getNumOfEquations()
{
	return numOfEquations;
}

double Matrix::getStoppingError()
{
	return stoppingError;
}

int Matrix::verifyInput(int input)
{
	if (!(cin >> input))
	{
		cout << "Invalid character. Please try again: ";
		cin.clear();
		cin.ignore(123, '\n');
		verifyInput(input);
	}

	return input;
}
double Matrix::verifyInput(double input)
{
	if (!(cin >> input))
	{
		cout << "Invalid character. Please try again: ";
		cin.clear();
		cin.ignore(123, '\n');
		verifyInput(input);
	}

	return input;
}

double Matrix::normVector()
{
	double numerator = 0;
	double denominator = 0;

	for (int i = 0; i < numOfEquations; i++)
	{
		numerator += pow(x.at(i) - y.at(i), 2);
		denominator += pow(x.at(i), 2);
	}

	return sqrt(numerator) / sqrt(denominator);
}

void Matrix::jacobi()
{
	double delta = pow(10, -10);
	x = originalVector;

	for (int k = 0; k < 50; k++)
	{
		y = x;
		for (int i = 0; i < numOfEquations; i++)
		{
			double sum = b[i];
			double diag = matrix[i][i];
			if (abs(diag) < delta)
			{
				cout << "Diagonal element too small " << endl;
				return;
			}
			for (int j = 0; j < numOfEquations; j++)
			{
				if (j != i)
				{
					sum -= matrix[i][j] * y[j];
				}
			}
			x.at(i) = sum / diag;
		}
		printResults();
		if (normVector() < stoppingError)
		{
			return;
		}
	}
	cout << "maximum iterations reached" << endl;
}

void Matrix::gauss()
{
	double delta = pow(10, -10);
	x = originalVector;

	for (int k = 0; k < 50; k++)
	{
		y = x;
		for (int i = 0; i < numOfEquations; i++)
		{
			double sum = b[i];
			double diag = matrix[i][i];
			if (abs(diag) < delta)
			{
				cout << "Diagonal element too small " << endl;
				return;
			}
			for (int j = 0; j < i; j++)
			{ 
				sum -= matrix[i][j] * x[j];
			}
			for (int j = i + 1; j < numOfEquations; j++)
			{
				sum -= matrix[i][j] * x[j];
			}
			x.at(i) = sum / diag;
		}
		printResults();
		if (normVector() < stoppingError)
		{
			return;
		}
	}
	cout << "maximum iterations reached" << endl;
}