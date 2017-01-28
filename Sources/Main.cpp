#include <iostream>
#include <string>
#include "Data.h"
#include "Solving.h"
using namespace std;

// uncomment this on release
//#include "Test.h"

void SolveTheCircuit(Circuit*& c)
{						//Reading the Circuit
	Circuit *c2 = c->Copy();		//Copying The Circuit To Another Pointer
	voltageTransformation(c2);		//Voltage Source Transformation
	solve(c2);						//Solve Essential Node Of The Copied Circuit
	VoltageBack(c2, c);				//This Function Get The Circuit Voltage From The Copied Circuit [c2] To The Main Circuit [c]
	SolveNonEss(c);					//Solvig Non Essential Nodes [This Function Take The Main Circuit As A parameter]	

	delete c2;	
}

#ifndef __RELEASE__ 

int main()
{
	Print_Help();
	Print_Credits();

    Circuit* c = new Circuit;
	c->Read();

	SolveTheCircuit(c);

	Circuit_Is_Power_Balanced(c);
		
	Interface(c);

	delete c;
}

#endif	/* __RELEASE__ */