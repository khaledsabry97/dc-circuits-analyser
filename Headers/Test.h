/*
		Testing functions
	when a test is finished, move it under the preprocessor __OLD_TESTS__
*/
#pragma once
#define __RELEASE__ 
#include "Data.h"
#include "Solving.h"
#include <cstdio>

#define INPUT_FILE "./Test/input"
#define OUTPUT_FILE "./Test/result"

// redirect input/output
// change cin/cout/cerr behaviour to make them print to a file and get input from another
void Redirect_IO(bool redirect)
{
	if (!redirect)
		return;

	freopen(OUTPUT_FILE, "w", stdout);
	freopen(OUTPUT_FILE, "w", stderr);

	freopen(INPUT_FILE, "r", stdin);
}


int main()
{
	//
}

#ifdef __OLD_TESTS__
	void test_remove_node_from_another_circ()
	{
		Circuit c;
		c.Read();
		
		Node* n = new Node(5);
		try
		{
			c.Remove(n);
		}
		catch (const error &err)
		{
			if (err == DEL_NODE_FROM_WRONG_CIRC)
				cout << "it works\n";
		}
	}
	void test_hadi_solving2()
	{
		Circuit* c = new Circuit;
		c->Read();						//Reading the Circuit
		Circuit *c2 = c->Copy();		//Copying The Circuit To Another Pointer
		voltageTransformation(c2);		//Voltage Source Transformation
		cout << "Circuit Before Solving: "<<endl;
		print(c2);						//Print The Circuit Data
		solve(c2);						//Solve Essential Node Of The Copied Circuit
		cout << "Circuit After Solving:"<<endl;
		print(c2);	
		VoltageBack(c2, c);				//This Function Get The Circuit Voltage From The Copied Circuit [c2] To The Main Circuit [c]
		cout << "Main Circuit After Getting The Nodes Voltage Back To It: " <<endl;
		print(c);
		cout << "New Circuit After Solving:"<<endl;
		SolveNonEss(c);					//Solvig Non Essential Nodes [This Function Take THe Main Circuit As A parameter]		
		c->Print();
	}

	void test_khaled_functions()
	{
		Circuit* c = new Circuit;
		c->Read();
		Circuit* c_copy1 = c->Copy();
		Disable_Sources(c_copy1);
		c_copy1->Print();
	}

	int test_for_hadi_funcitons()
	{
		Circuit* c = new Circuit;
		c->Read();						//Reading the Circuit
		Circuit *c2 = c->Copy();		//Copying The Circuit To Another Pointer
		voltageTransformation(c2);		//Voltage Source Transformation
		cout << "Circuit Before Solving: "<<endl;
		print(c2);
		solve(c2);
		cout << "Circuit After Solving:"<<endl;
		print(c2);
		VoltageBack(c2, c);
		cout << "Main Circuit After Getting The Nodes Voltage Back To It: " <<endl;
		print(c);
		cout << "New Circuit After Solving:"<<endl;
		SolveNonEss(c);
		print(c);
	}

	// this test is done +
	int test_circuit3()
	{
		// test circuit 

		Node* n;
		Element* e;

		// add nodes to circuit
		Circuit* c = new Circuit;

		for (int j = 20; j--;)
		{
			n = new Node(j);
			for (int i = j; i--;)
			{
				e = new Element('E', i, i * 3 -9);
				n->Add(e);
			}
			c->Add(n);
		}

		// copy that circuit
		Circuit* newOne = new Circuit(c);

		// another copy
		Circuit nn;
		nn = *newOne;

		newOne->IsEmpty();

		// do the previous lines again wiht this
		n = new Node(22);
		newOne->Add(n);
		newOne->Remove(n);
		n = new Node(33);
		
		Node* temp = newOne->GetNode(2, ID);
		temp = newOne->GetNode(22, ID);
		temp = newOne->GetNode(0, VOLT);
		temp = newOne->GetNode(-2, VOLT);

		bool x = newOne->HasNode(5, ID);
		if (newOne->IsEmpty())
			printf("it is empty\n");
		else 
			printf("wow! it is not empty\n");

		newOne->Remove(5);
		if (newOne->HasNode(5))
			cout << "moseeba!\n";
		else 
			cout << "qeshta \n";

	}

	int test_circuit2()
	{
		// test circuit 

		Node* n;
		Element* e;

		// add nodes to circuit
		Circuit* c = new Circuit;

		for (int j = 20; j--;)
		{
			n = new Node(j);
			for (int i = j; i--;)
			{
				e = new Element('E', i, i * 3 -9);
				n->Add(e);
			}
			c->Add(n);
		}

		n = new Node(22);
		c->Add(n);
		
		Node* temp = c->GetNode(2, ID);
		temp = c->GetNode(22, ID);
		temp = c->GetNode(0, VOLT);

		c->RemoveDuplicates();

		bool x = c->HasNode(5, ID);
		if (c->IsEmpty())
			printf("it is empty\n");
		else 
			printf("wow! it is not empty\n");

		c->Remove(5);
		if (c->HasNode(5))
			cout << "moseeba!\n";
		else 
			cout << "qeshta \n";

		
	}

	int test_circuit()
	{
		// test circuit 

		Node* n;
		Element* e;

		// add nodes to circuit
		Circuit* c = new Circuit;

		for (int j = 20; j--;)
		{
			n = new Node(j);
			for (int i = j; i--;)
			{
				e = new Element('E', i, i * 3 -9);
				n->Add(e);
			}
			c->Add(n);
		}

		n = new Node(22);
		c->Add(n);
		c->Remove(n);

		c->GetLastNode();
		c->GetFirstNode();

		delete c;
	}

	int test_node()
	{
		// elementary node test

		Node* n = new Node(1);

		n->GetId();

		n->ChangeVolt(-9);
		n->GetVolt();
		n->ChangeVolt(+88.1);
		n->GetVolt();

		n->GetNumOfElem();
		n->IsEssential();

		n->GetFirstElem();
		n->GetNext();
		Node* m = new Node(2);
		n->SetNext(m);

		Element* s = new Element('r', 5, 9);
		n->Add(s);
		n->Remove(s);

		n->Add(s);
		s = new Element('j', 6, 90);
		n->Add(s);
		n->Add(s);

		n->GetNumOfElem();
		cout << n->IsEssential();
		n->Remove(s);
		cout << n->IsEssential();
	}

	int test_element()
	{
		// elementary test to element
		Element* n = new Element('r', 5, 33);
		n->GetType();
		n->ChangeType('j');
		n->GetNext();
		n->GetPrev();

		Element* s = new Element('R', 33, 56);
		n->SetNext(s);
		delete s;
		s = new Element('j', 3 ,33);
		n->SetPrev(s);

		n->GetId();
		n->ChangeId(9);

		n->GetValue();
		n->ChangeValue(99);
	}


	void test_eigen_mat()
	{
		Solver s(2,2);
		s.A << 1 ,5, -1, 2;
		s.B << 3, 5;
		s.Print();
		s.Solve();
		cout << s.X;

	}

	void element1()
	{
		Element* n = new Element("t", 55);
		delete n;
	}

	int quick_element_test()
	{
		//mat();
		//element1();
		el2();
	}

#endif /* 	__OLD_TESTS__	 */