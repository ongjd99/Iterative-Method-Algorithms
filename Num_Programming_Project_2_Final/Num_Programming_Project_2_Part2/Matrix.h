/*
	Ong, Johnny

	September 30, 2020

	CS 3010.01 Numerical Methods
	Programming Project 2
*/

#pragma once

#include <vector>

class Matrix
{
public:
	// Beginning initialization 
	Matrix();
	~Matrix();
	void deleteMatrices();
	void init();
	void initFile();

	// Setting up 
	void createMatrix();
	void setBMatrix();
	void setSolutionMatrix();
	void setStoppingError();
	
	//Helpful
	void printAll();
	void printResults();
	int getNumOfEquations();
	double getStoppingError();
	double verifyInput(double);
	int verifyInput(int);

	// Calculations
	double normVector();
	void jacobi();
	void gauss();

private:
	double** matrix;
	std::vector<double> b;
	std::vector<double> originalVector;
	std::vector<double> x;
	std::vector<double> y;

	int numOfEquations;
	double stoppingError;

};