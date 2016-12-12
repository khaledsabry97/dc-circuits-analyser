//#pragma once
#include "Data.h"
#include <iostream>
#include <string>

using namespace std;


//Matrix Solving Functions

void insert(double **arr,double *arr2,int);
void print(double **arr,double *arr2, int);		//Just  For Debuging The Matrix Work
void swapMat(double arr[][50],double arr2[][1],int,int,double arr3[][50]);
void intElements(double arr[][50],int);
double detMat(double arr[][50],int);
void DoublingMat(double **arr, int);
void init(double **arr, int);
double *SolvingMat(double **arr,double *arr2,int);

//My Own Functions

int sizeOfTheMat(Circuit *c);

double SearchNodeByElement(Element *e, Circuit *c);

Node *SearchNode(Circuit *c, int ID);

Element *SearchElement(Element *e, int, Circuit *c);




//*****************************************************Functions That You can Use [Orderd]**********************************************************************************

void voltageTransformation(Circuit *&c);	//Transform The Voltage Source To Current Source

void solve(Circuit *&c);	//Solving Essential Nodes

void VoltageBack(Circuit *in, Circuit*& out);	//Get The Voltage Back To The Main Circuit

void SolveNonEss(Circuit *&c);	//Solving None Essentail Nodes

void print(Circuit *c);		//Just For Testing