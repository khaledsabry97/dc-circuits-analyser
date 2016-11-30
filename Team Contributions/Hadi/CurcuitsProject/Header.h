#include <iostream>
#include <string>
using namespace std;
struct element
{
	string name;
	double val;
	element *nextElement;
};
struct node
{ 
	double volt;
	bool ess;
	element *e;
	node *nextNode;
};

char menu();	//Main Menu

void input(node *&head, node *&last);	//Input From The User

bool isEmpty(node *head);	//Check Is The Node List Is Empty Or Not

bool Empty(element *head);	//Check The Element List Is Empty Or Not

void insertnode(node *&head, node *&last, element *data);	//Insert A Node

void insertelement(element *&head, element *&last, string name, double val);	//Insert An Element

bool searcherors(element *data);	//Checking Some Errors

bool searchDuplicat(node *head, string name);	//Check If The Element Exsist More Than Two Times

void printData(node *head);		//Print The Data [This Function For Testing Only We Will Remove It After The Last Test]

void deleteNode(node *&head, node *del);	//Deleting Node By Its Address

void voltageTransformation(node *&head);	//Voltage Transformation From Currnt Source

void doubleList(node *head, node *&head2);	//Doubling The Nodes List