#include<iostream>
#include<string>
using namespace std;
struct node
{
	string element;
	float val;
	//bool ess;
	node *next;
};
bool isEmpty(node *&head);
char menu();
void insertAsFirstElement(node *&head, node *&last, string element, float val);
void insert(node *&head, node *&last, string element, float val);
void remove(node *&head, node *&last);
void showList(node *current);

bool isEmpty(node *&head)
{
	if(head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
char menu()
{
	char choise;
	cout << "Menu"<<endl;
	cout << "1. Add An Item."<<endl;
	cout << "2. remove An Item."<<endl;
	cout << "3. Show The List."<<endl;
	cout << "4. Exit."<<endl;

	cin >> choise;
	return choise;
}
void insertAsFirstElement(node *&head, node *&last, string element, float val)
{
	node *temp = new node;
	temp->element = element;
	temp->val = val;
	temp->next = NULL;
	head = temp;
	last = temp;
}
void insert(node *&head, node *&last, string element, float val)
{
	if(isEmpty(head))
	{
		insertAsFirstElement(head, last, element, val);
	}
	else
	{
		node *temp = new node;
		temp->element = element;
		temp->val = val;
		temp->next = NULL;
		last->next = temp;
		last = temp;
	}
}
void remove(node *&head, node *&last)
{
	if(isEmpty(head))
	{
		cout<<"The List Is Already Empty"<<endl;
	}
	else if(head == last)
	{
		delete head;
		head = NULL;
		last = NULL;
	}
	else
	{
		node *temp = head;
		head = head->next;
		delete temp;
	}
}
void showList(node *current)
{
	if(isEmpty(current))
	{
		cout<<"The List Is Empty"<<endl;
	}
	else
	{
		cout<<"The List Contains: "<<endl;
		while(current != NULL)
		{
			cout<< current->element<<"   ";
			cout<< current->val<<endl;
			current = current->next;
		}
	}
}
int main()
{
	node *head = NULL;
	node *last = NULL;
	char choise;
	string element;
	float val;

	do
	{

		choise = menu();

		switch (choise)
		{
		case '1':
			cout<< "Please enter The element: ";
			cin>> element >>val;
			insert(head, last, element, val);
			break;
		case '2':
			remove(head, last);
			break;
		case '3' :
			showList(head);
			break;
		default:
			cout<<"System exit"<<endl;
		}
	}while (choise != '4');


	return 0;
}