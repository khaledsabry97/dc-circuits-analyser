/*
        Getting voltages, current and power funcitons
    by Hadi, Khaled and M.Youssri 
*/
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

double Get_Total_Supplied_Power(const Circuit*& circuit);

double Get_Total_Dissipated_Power(const Circuit*& circuit);

// returns true if total power is balanced, false otherwise
bool Circuit_Is_Power_Balanced(const Circuit*& circuit);

// get the value of resistance such that it
// receives maximum power from the circuit
double Get_Res_Max(const Circuit*& circiut, const Element*& resistance);

// for the given resistance
double Get_Pow_Max(const Circuit*& circiut, const Element*& resistance);

/*   Extended   */

// current in given element
double Get_Current(const Circuit*& circiut, const Element*& element);

// current in element due to another element
// (the current that due_to_element caused in element)
double Get_Current(const Circuit*& circiut, const Element*& element, const Element*& due_to_element);

// positive when dissipated, negative when supplied
double Get_Power(const Circuit*& circuit, const Element*& element);

// get power that due_to_elemnt caused in element
double Get_Power(const Circuit*& circuit, const Element*& element, const Element*& due_to_element);

// voltage difference between node1 & node2
// given the ids' of them, it searched for them in circuit
// given ids' are expected to be valid (in the circuit)
double Get_VoltDiff(const Circuit*& circuit, const int node1_id, const int node2_id);

// voltage differnt between two nodes that due_to_element caused 
double Get_VoltDiff(const Circuit*& circuit, const int node1_id, const int node2_id, const Element*& due_to_element);