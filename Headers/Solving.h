/*
        Getting voltages, current and power funcitons
    by Hadi, Khaled and M.Youssri 
*/
#pragma once
#include "Data.h"
#include "Errors.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/*          Hadi          */

// Matrix Solving Functions

void insert(double **arr,double *arr2,int);		//Inserting The Matrix
void print(double **arr,double *arr2, int);		//Just  For Debuging The Matrix Work
void swapMat(double arr[][50],double arr2[][1],int,int,double arr3[][50]);		//Swaping The Matrix Column To Make The Detemined Matrix
void intElements(double arr[][50],int);			//Doubling n-1 Column
double detMat(double arr[][50],int);			//Determining The Matrix
void DoublingMat(double **arr, int);			
void init(double **arr, int);					//Initializing The Matrix
double *SolvingMat(double **arr,double *arr2,int);		//Solving The Equations


// My Own Functions

int sizeOfTheMat(Circuit *c);					//Counting The Size Of The Matrix Using The Circuit

int countCircuit(Circuit *c);					//Counting The Circuit Nodes

double SearchNodeByElement(Element *e, Circuit *c);		//Searching For The Essential Node By The Element

Node *SearchNodeNon(Element *&e, Circuit *c, int ID);	//Searching For The Non Essential Node By The Element [This Function Returns The another Node That Has The Element e And Returns The Another Element Next To The Element In The Node]

Node *SearchNode(Circuit *c, int ID);				//Searching The Node By Its ID

Element *SearchElement(Element *e, int, Circuit *c);		//Searching The Element

void print(Circuit *c);		//Just For Testing


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

double Get_Total_Supplied_Power(Circuit* circuit);

double Get_Total_Dissipated_Power(Circuit* circuit);

// returns true if total power is balanced, false otherwise
bool Circuit_Is_Power_Balanced(Circuit* circuit);

// get the value of resistance such that it
// receives maximum power from the circuit
double Get_Res_Max(Circuit* circuit, Element* resistance);

// for the given resistance
double Get_Pow_Max(Circuit* circuit, Element* resistance);

/*   Extended   */

// current in given element
double Get_Current(Circuit* circuit, Element* element);

// current in element due to another element
// (the current that due_to_element caused in element)
double Get_Current(Circuit* circuit, Element* element, Element* due_to_element);

// positive when dissipated, negative when supplied
double Get_Power(Circuit* circuit, Element* element);

// get power that due_to_elemnt caused in element
double Get_Power(Circuit* circuit, Element* element, Element* due_to_element);

// voltage difference between node1 & node2
// given the ids' of them, it searched for them in circuit
// given ids' are expected to be valid (in the circuit)
double Get_VoltDiff(Circuit* circuit, const int node1_id, const int node2_id);

// voltage differnt between two nodes that due_to_element caused 
double Get_VoltDiff(Circuit* circuit, const int node1_id, const int node2_id, Element*& due_to_element);

void Interface(Circuit *c);

double roundf(double x);
double Round(const double &num, const int precision);