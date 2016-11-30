#include "Header.h"

char menu()
{
	char choise;
	cout << "\n1- Add A New Node:\n";
	cout << "2- Print The Lists:\n";
	cout << "x- Exit\n\n";
	cin >> choise;
	return choise;
}

bool isEmpty(node *head)
{
	if(head == NULL)
		return true;
	return false;
}
bool Empty(element *head)
{
	if(head == NULL)
		return true;
	return false;
}

void input(node *&head, node *&last)
{
	element *headE, *lastE;
	char choise;
	string name;
	double val;
	do
	{
		choise = menu();
		switch (choise)
		{
		case '1':
			headE = lastE = NULL;
			do
			{
				cout << "Enter The Element Name Then Value\n";
				cout << "Enter x If You  Have Not No More Elements\n";
				cin >> name;
				//Checing Some Errors
				if(name[0] != 'r' && name[0] != 'j' && name[0] != 'e')	//Check If The Input Is Only One Of Our Three Inputs
					cout << "Wrong Input\n";
				else if (searchDuplicat(head, name) == false)			//Check If The Element Exsists More Than Two Times
					cout << "You Have Inserted This Element More Than 2 Times\nIt Won't Be Inserted Agian!!\n";
				else if (name[0] == 'x')
					break;
				else
				{
					cin >> val;
					insertelement(headE, lastE, name, val);
				}
			} while (name[0] != 'x');
			if(searcherors(headE))
			{
				insertnode(head, last, headE);
			}
			else
			{
				cout << "You Have Entered Less Than Two Element In This Node\n";
				cout << "To Enter The Node Again Press 1\n";
			}
			break;
		case '2':
			printData(head);
			break;
		case 'x':
			cout << "End Of Input\n";
			break;
		default:
			cout << "Wrong Input\nPlease Try Again\n";
			break;
		}
	} while (choise != 'x');
}

void insertelement(element *&head, element *&last, string name, double val)
{
	element *temp = new element;
	temp->name = name;
	temp->val = val;
	if(Empty(head))
	{
		temp->nextElement = NULL;
		head = temp;
		last = temp;
	}
	else if (name[0] == 'e')	//If The Element Is A Voltage Source Element Insert It In The First
	{
		temp->nextElement = head;
		head = temp;
	}
	else
	{
		temp->nextElement = last->nextElement;
		last->nextElement = temp;
		last = temp;
	}
}

bool searcherors(element *data)
{
	if(data == NULL)	//Check If The User Insert An Empty Node
		return false;
	else if(data->nextElement == NULL)	//Check If The User Insert A Node Contains One Element
		return false;
	else
		return true;
}

bool searchDuplicat(node *head, string name)
{
	int count = 0;
	while(head != NULL)
	{
		element *temp = head->e;
		while (temp != NULL)
		{
			if(name == temp->name)
			{
				count++;
			}
			temp = temp->nextElement;
		}
		head = head->nextNode;
	}
	if(count >= 2)
		return false;
	else
		return true;
}

void insertnode(node *&head, node *&last, element *data)
{
	node *temp = new node;
	if(data->nextElement->nextElement == NULL)
		temp->ess = false;
	else
		temp->ess = true;
	temp->e = data;
	if(isEmpty(head))
	{
		temp->nextNode = NULL;
		head = temp;
		last = temp;
	}
	else if(temp->ess)		//If The Node Is Essential Node Insert It At The Last Of The List
	{
		temp->nextNode = NULL;
		last->nextNode = temp;
		last = temp;
	}
	else	//If The Node Isn't Essential Insert It At The First Of The List
	{
		temp->nextNode = head;
		head = temp;
	}
}

void printData(node *head)
{
	if(isEmpty(head))
		cout << "The List Is Already Empty\n";
	else
	{
		int i = 1;
		while (head != NULL)
		{
			cout << "The " << i << " Node Contains:\n";
			element *temp = head->e;
			while (temp != NULL)
			{
				cout << "The Element Name Is: " << temp->name << "\tAnd val: " << temp->val << "\n";
				temp = temp->nextElement;
			}
			i++;
			head = head->nextNode;
		}
	}
}

void deleteNode(node *&head, node *del)
{
	if (isEmpty(head))
		return;
	else if (head == del)
	{
		node *temp = head;
		head = temp->nextNode;
		delete temp;
	}
	else
	{
		node *temp = head;
		while (temp != NULL)
		{
			if(temp->nextNode == del)
			{
				node *Temp = temp->nextNode;
				temp->nextNode = Temp->nextNode;
				delete Temp;
				break;
			}
			temp = temp->nextNode;
		}
	}
}

void voltageTransformation(node *&head)
{
	string n[3];
	double v[3];
	int count = 0;
	node *Temp = head;
	while (Temp != NULL)
	{
		count = 0;
		if(!Temp->ess && Temp->e->name[0] == 'e')
		{
			n[0] = Temp->e->name;
			v[0] = Temp->e->val;
			n[1] = Temp->e->nextElement->name;
			v[1] = Temp->e->nextElement->val;
			n[2] = "J" + Temp->e->name;
			v[2] = v[0] / v[1];
			node *temp = head;
			while (temp != NULL)
			{
				element *tempE = temp->e;
				while (tempE != NULL)
				{
					if(tempE->name == n[0])
					{
						tempE->name = n[2];
						tempE->val = v[2];
						element *last = tempE;
						while (last->nextElement != NULL)
							last = last->nextElement;
						insertelement(tempE, last, n[1], v[1]);
						temp->ess = true;
						count++;
						break;
					}
					if(tempE->name == n[1])
					{
						element *last = tempE;
						while (last->nextElement != NULL)
							last = last->nextElement;
						insertelement(tempE, last, n[2], -1*v[2]);
						temp->ess = true;
						count++;
						break;
					}
					tempE = tempE->nextElement;
				}
				if (count > 2)
					break;
				temp = temp->nextNode;
			}
			deleteNode(head, Temp);
			Temp->nextNode = head;
		}
		Temp = Temp->nextNode;
	}

}

void doubleList(node *head, node *&head2)
{
	node *last2 = NULL;
	element *headE, *lastE;
	while (head != NULL)
	{
		headE = lastE = NULL;
		element *temp = head->e;
		while (temp != NULL)
		{
			insertelement(headE, lastE, temp->name, temp->val);
			temp = temp->nextElement;
		}
		insertnode(head2, last2, headE);
		head = head->nextNode;
	}
}