#include "data.h"
#include "Solving.h"

void voltageTransformation(Circuit* &C)
{
	char n[3];
	int id[3];
	double v[3];
	int count = 0;
	
	Node *Head = C->GetFirstNode();
	while (Head != NULL)
	{
		count = 0;

		if(!Head->IsEssential())
		{
			Element *e = Head->GetFirstElement();
			while (e)
			{
				if (e->GetType() == 'E')
				{
					n[0] = e->GetType();
					id[0] = e->GetId();
					v[0] = e->GetValue();
					if (!e->GetNext())
					{
						n[1] = e->GetPrev()->GetType();
						id[1] = e->GetPrev()->GetId();
						v[1] = e->GetPrev()->GetValue();
					}
					else
					{
						n[1] = e->GetNext()->GetType();
						id[1] = e->GetNext()->GetId();
						v[1] = e->GetNext()->GetValue();
					}
					n[2] ='J';
					id[2] = -1 * id[0];
					v[2] = v[0] / v[1];
					break;
				}
				e = e->GetNext();
			}

			if (e)
			{
				Node *temp = C->GetFirstNode();
				while (temp != NULL)
				{
					Element *tempE = temp->GetFirstElement();
					while (tempE != NULL)
					{
						if(tempE->GetType() == n[0] && tempE->GetId() == id[0])
						{
							tempE->ChangeType(n[2]);
							tempE->ChangeId(id[2]);
							tempE->ChangeValue(-1 * v[2]);
							Element *last = new Element(n[1], id[1], v[1]);
							temp->Add(last);
							count++;
							//delete last;
							break;
						}
						if(tempE->GetType() == n[1] && tempE->GetId() == id[1])
						{
							Element *last = new Element(n[2], id[2], v[2]);
							temp->Add(last);
							count++;
							break;
						}
						tempE = tempE->GetNext();
					}
					if (count > 2)
						break;
					temp = temp->GetNext();
				}
				C->Remove(Head);
				Head = C->GetFirstNode();
			}
			
		}
		Head = Head->GetNext();
	}

}

void print(Circuit *C)
{
	if(C->IsEmpty())
		cout << "The Circuit Is Already Empty\n";
	else
	{
		Node *Head = C->GetFirstNode();
		while (Head != NULL)
		{
			cout << "The " << Head->GetId() << " Node Has Volt: " << Head->GetVolt() <<endl;
			Element *temp = Head->GetFirstElement();
			while (temp != NULL)
			{
				cout << "The Element Type Is: " << temp->GetType() << "\tAnd Id: " << temp->GetId() << "\tAnd val: " << temp->GetValue() << "\n";
				temp = temp->GetNext();
			}
			Head = Head->GetNext();
		}
	}
}


void insert(double **arr,double *arr2, int size)
{
	cout<<"Enter The Array Elements: "<<endl;
	int i, j;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			cin>>arr[i][j];
		}
		cin>>arr2[i];
	}
}
void print(double **arr,double *arr2, int size)
{
	int i, j;
	for(i=0;i<size;i++)
	{
		cout<<"|\t";
		for(j=0;j<size;j++)
		{
			cout<<arr[i][j]<<"\t";
		}
		cout<<"|\t";
		cout<<arr2[i]<<"\t|"<<endl;
	}
}
void swapMat(double **arr,double *arr2,int size,int numCol,double **arr3)
{
	int i, j, swap;
	swap = j = i = 0;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(j == numCol)
			{
				arr3[i][j] = arr2[i];
			}
			else
			{
				arr3[i][j] = arr[i][j];
			}
		}
	}
}
void intElements(double **arr,int size)
{
	int i, j;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size-1;j++)
		{
			arr[i][j+size] = arr[i][j];
		}
	}
}
double detMat(double **arr,int size)
{
	int i, j, test;
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
		for(j=0;j<size;j++)
		{
			row = 1;
			test = j;
			for(i=0;i<size;i++)
			{
				row = row * arr[i][test];
				test++;
			}
			sum1 = sum1 + row;
		}
		for(j=0;j<size;j++)
		{
			row = 1;
			test = j;
			for(i=size-1;i>=0;i--)
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

int sizeOfTheMat(Circuit *c)
{
	int count = 0;
	Node *n = c->GetFirstNode();
	while (n)
	{
		if (n->IsEssential())
			count++;
		n = n->GetNext();
	}
	return count;
}

void init(double **arr, int size)
{
	int i, j;
	for(i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			arr[i][j] = 0;
		}
	}
}

void DoublingMat(double **arr, int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			arr[j][i] = arr[i][j];
		}
	}
}

double *SolvingMat(double **arr,double *arr2,int size)
{
	double **arr3 = new double*[size];
	for (int i = 0; i < size; i++)
		arr3[i] = new double[(2*size)-1];
	intElements(arr, size);
	double mainDet = detMat(arr,size);
	double *det = new double[size];
	for(int numCol=0;numCol<size;numCol++)
	{
		swapMat(arr,arr2,size,numCol,arr3);
		intElements(arr3,size);
		det[numCol] = detMat(arr3,size);
	}
	for(int numCol=0;numCol<size;numCol++)
	{
		if(mainDet == 0)
			return NULL;
		else
			det[numCol] = det[numCol] / mainDet;
	}
	return det;
}

Element *SearchElement(Element *e, int NodeID, Circuit *c)
{
	Node *temp = c->GetFirstNode();
	while (temp)
	{
		if (!temp->IsEssential())
		{
			Element *tempE = temp->GetFirstElement();
			if (tempE->GetType() == e->GetType() && tempE->GetId() == e->GetId())
			{
				if(temp->GetId() != NodeID)
				{
					if (tempE->GetNext())
						return tempE->GetNext();
					return tempE->GetPrev();
				}
			}
		}
		temp = temp->GetNext();
	}
	return NULL;
}

void solve(Circuit *&c)
{
	int size = sizeOfTheMat(c) - 1;
	double series = 0;
	double sumR, sumJ;
	double CS = 0;
	int i, j, count;
	i = 0;
	j = 0;
	count = 0;
	double **arr = new double*[size];
	for (int i = 0; i < size; i++)
		arr[i] = new double[(2*size)-1];
	init(arr, size);
	double *arr2 = new double[size];
	Node *n = c->GetFirstNode();
	while (n)
	{
		if (n->IsEssential())
		{
			count++;
			if (count == 1)
			{
				n = n->GetNext();
				continue;
			}
			Element *e = n->GetFirstElement();
			sumR = 0;
			sumJ = 0;
			CS = 0;
			series = 0;
			while (e)
			{
				series = 0;
				if(e->GetType() == 'R')
					series = e->GetValue();
				else if(e->GetType() == 'J')
					CS += e->GetValue();
				Element *tempE = SearchElement(e, n->GetId(), c);
				while (tempE)
				{
					if(tempE->GetType() == 'R')
						series += tempE->GetValue();
					else if(tempE->GetType() == 'J')
						CS = tempE->GetValue();
					tempE = SearchElement(tempE, n->GetId(), c);
				}
				if (series != 0)
					sumR += 1 / series;
				e = e->GetNext();
			}
			sumJ += CS;
		}
		arr[i][i] = sumR;
		arr2[i] = sumJ;
		i++;
		if(count == size + 1)
			break;
		n = n->GetNext();
	}
	n = c->GetFirstNode();
	count = 0;
	series = 0;
	sumR = 0;
	i = j = 0;
	while (n)
	{
		if (n->IsEssential())
		{
			count++;
			if (count == 1)
			{
				n = n->GetNext();
				continue;
			}
			Element *e = n->GetFirstElement();
			sumR = 0;
			while (e)
			{
				if(e->GetType() == 'R')
					series = e->GetValue();
				else
				{
					e = e->GetNext();
					continue;
				}
				Element *tempE = SearchElement(e, n->GetId(), c);
				if (!tempE)
				{
					j = count -1;
					Node *tempN = n->GetNext();
					while (tempN)
					{
						while (!tempN->IsEssential())
						{
							tempN = tempN->GetNext();
							if (!tempN)
								break;
						}
						if(!tempN)	
							break;
						Element *eCom = tempN->GetFirstElement();
						while (eCom)
						{
							if (e->GetType() == eCom->GetType() && e->GetId() == eCom->GetId())
							{
								arr[i][j] += -1 / series;
								break;
							}
							eCom = eCom->GetNext();
						}
						j++;
						tempN = tempN->GetNext();
					}
				}
				else
				{
					Element *eCom = NULL;
					while (tempE)
					{
						if(tempE->GetType() == 'R')
						{
							series += tempE->GetValue();
							eCom = tempE;
						}
						else
							break;
						tempE = SearchElement(tempE, n->GetId(), c);
					}
					if (tempE != NULL)
					{
						if (tempE->GetType() != 'R')
						{
							break;
						}
					}
					j = count - 1;
					Node *tempN = n->GetNext();
					while (tempN)
					{
						while (!tempN->IsEssential())
						{
							tempN = tempN->GetNext();
							if (!tempN)
								break;
						}
						if (!tempN)
							break;
						Element *eCom2 = tempN->GetFirstElement();
						while (eCom2)
						{
							if (eCom->GetType() == eCom2->GetType() && eCom->GetId() == eCom2->GetId())
							{
								arr[i][j] += -1 / series;
								break;
							}
							eCom2 = eCom2->GetNext();
						}
						j++;
						tempN = tempN->GetNext();
					}
				}
				e = e->GetNext();
			}
			i++;
			if(i == size)
				break;
		}
		n = n->GetNext();
	}
	DoublingMat(arr, size);
	double *volts = SolvingMat(arr, arr2, size);
	n = c->GetFirstNode();
	count = 0;
	i = 0;
	while (n)
	{
		if (n->IsEssential())
		{
			count++;
			if (count == 1)
				n->ChangeVolt(0);
			else
			{
				n->ChangeVolt(volts[i]);
				i++;
			}
		}
		n = n->GetNext();
	}
}

void VoltageBack(Circuit *in, Circuit*& out)
{
	Node *n = in->GetFirstNode();
	Node *n2 = NULL;
	while (n)
	{
		n2 = SearchNode(out, n->GetId());
		if (n2)
			n2->ChangeVolt(n->GetVolt());
		n = n->GetNext();
	}
}
Node *SearchNode(Circuit *c, int ID)
{
	Node *n = c->GetFirstNode();
	while (n)
	{
		if (n->GetId() == ID)
			return n;
		n = n->GetNext();
	}
	return NULL;
}

double SearchNodeByElement(Element *e, Circuit *c)
{
	Node *n = c->GetFirstNode();
	while (n)
	{
		if (n->IsEssential())
		{
			Element *eCom = n->GetFirstElement();
			while (eCom)
			{
				if (e->GetId() == eCom->GetId() && e->GetType() == eCom->GetType())
				{
					return n->GetVolt();
				}
				eCom = eCom->GetNext();
			}
		}
		n = n->GetNext();
	}
	return 0;
}

void SolveNonEss(Circuit *&c)
{
	Node *n = c->GetFirstNode();
	while (n)
	{
		if (!n->IsEssential())
		{
			Element *e = n->GetFirstElement();
			double volt[2], sumR, sumV;
			sumR = 0;
			sumV = 0;
			int i = 0;
			while (e)
			{
				Element *eCom2 = e;
				if (e->GetType() == 'R')
					sumR += e->GetValue();
				else if(e->GetType() == 'E')
					sumV += e->GetValue();
				Element *eCom = SearchElement(e, n->GetId(), c);
				while (eCom)
				{
					eCom2 = eCom;
					if (eCom->GetType() == 'R')
						sumR += eCom->GetValue();
					else if(e->GetType() == 'E')
						sumV += eCom->GetValue();
					eCom = SearchElement(e, n->GetId(), c);
				}
				volt[i] = SearchNodeByElement(eCom2, c);
				i++;
				e =e->GetNext();
			}
			double IPranch = ((volt[0] - volt[1]) / sumR);
			e = n->GetFirstElement();
			sumR =  0;
			while (e)
			{
				if (e->GetType() == 'R')
				{
					Element *eCom2 = e;
					if (e->GetType() == 'R')
						sumR += e->GetValue();
					Element *eCom = SearchElement(e, n->GetId(), c);
					while (eCom)
					{
						eCom2 = eCom;
						if (eCom->GetType() == 'R')
							sumR += eCom->GetValue();
						eCom = SearchElement(e, n->GetId(), c);
					}
					double NodeV = SearchNodeByElement(eCom2, c);
					n->ChangeVolt(sumV - ((IPranch * sumR) - NodeV));
				}
				e = e->GetNext();
			}
		}
		n = n->GetNext();
	}
}