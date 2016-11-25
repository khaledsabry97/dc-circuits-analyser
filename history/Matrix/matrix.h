#pragma once
#include <iostream>
using namespace std;

// prototypes
void insert(double arr[][50],double arr2[][1],int);
void print(double arr[][50],double arr2[][1], int);
void swapMat(double arr[][50],double arr2[][1],int,int,double arr3[][50]);
void intElements(double arr[][50],int);
double detMat(double arr[][50],int);

// implementation
void insert(double arr[][50], double arr2[][1], int size)
{
	cout << "Enter The Array Elements: ";

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			cin >> arr[i][j];
		}
		cin >> arr2[i][1];
	}
}


void print(double arr[][50], double arr2[][1], int size)
{
	for(int i = 0; i < size; i++)
	{
		cout << "|\t";
		for(int j = 0; j < size; j++)
			cout <<arr[i][j] << "\t";
		cout << "|\t";
		cout << arr2[i][1] << "\t|" << endl;
	}
}


void swapMat(double arr[][50], double arr2[][1], int size, int numCol, double arr3[][50])
{
	int swap = 0;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(j == numCol)
			{
				arr3[i][j] = arr2[i][0];
			}
			else
			{
				arr3[i][j] = arr[i][j];
			}
		}
	}
}


void intElements(double arr[][50], int size)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size - 1; j++)
		{
			arr[i][j+size] = arr[i][j];
		}
	}
}


double detMat(double arr[][50], int size)
{
	int test;
	double det = 0, row = 1, sum1 = 0, sum2 = 0;
	if(size == 1)
	{
		det = arr[0][0];
	}
	else if(size == 2)
	{
		det = (arr[0][0]*arr[1][1]) - (arr[0][1]*arr[1][0]);
	}
	else
	{
		for(int j = 0; j < size; j++)
		{
			row = 1;
			test = j;
			for(int i = 0; i < size; i++)
			{
				row = row * arr[i][test];
				test++;
			}
			sum1 = sum1 + row;
		}
		for(int j = 0; j < size; j++)
		{
			row = 1;
			test = j;
			for(int i = size - 1; i >= 0; i--)
			{
				row = row * arr[i][test];
				test++;
			}
			sum2 = sum2 + row;
		}
		det = sum1 - sum2;
	}
	return det;
}
