#pragma once
#include "Data.h"
#include <iostream>
#include <string>

using namespace std;

/*          Hadi          */

// Matrix Solving Functions
void insert(double **arr,double *arr2,int);
void print(double **arr,double *arr2, int);		//Just  For Debuging The Matrix Work
void swapMat(double arr[][50],double arr2[][1],int,int,double arr3[][50]);
void intElements(double arr[][50],int);
double detMat(double arr[][50],int);
void DoublingMat(double **arr, int);
void init(double **arr, int);
double *SolvingMat(double **arr,double *arr2,int);

// My Own Functions
int sizeOfTheMat(Circuit *c);
double SearchNodeByElement(Element *e, Circuit *c);
Node *SearchNode(Circuit *c, int ID);
Element *SearchElement(Element *e, int, Circuit *c);

//*******************Functions you can use [Orderd]*******************

// Transform The Voltage Source To Current Source
void voltageTransformation(Circuit *&c);	

// Solving Essential Nodes
void solve(Circuit *&c);	

// Get The Voltage Back To The Main Circuit
void VoltageBack(Circuit *in, Circuit*& out);	

// Solving Non-Essentail Nodes
void SolveNonEss(Circuit *&c);	



/*              Khaled & Youssri             */

// remove all Voltage sources and current sources
void Disable_Sources(Circuit* c);

// calculate voltage between two nodes
int Voltage(Node* n1, Node* n2);

// calculate amper between two nodes
int Ampere(Node* n1, Node* n2, Element* e);

// calculate Power between two nodes
int Power(Element* e, Circuit* c);

// find the two nodes that contains that element 
void Get_2_Nodes(Element* e, Node* &n1, Node* &n2, Circuit* c);