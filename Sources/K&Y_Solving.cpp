#include "Solving.h"

/*		private		*/

// remove all Voltage sources and current sources
void Disable_Sources(Circuit*& c);

// calculate voltage between two nodes
double Voltage(Node* n1, Node* n2);

// calculate amper between two nodes
double Ampere(Node* n1, Node* n2, Element* e, Circuit* c);

// calculate Power between two nodes
double Power(Element* e, Circuit* c);

// find the two nodes that contains that element 
void Get_2_Nodes(Element* e, Node* &n1, Node* &n2, Circuit* c);

// remove all Voltage sources and current sources only one source remains
Circuit* Disable_Sources_superpostion(Circuit* c,Element* e_temp);

// remove all Voltage sources and current sources only one source remains
// return circuit with one (voltag or current) source 
Circuit* Disable_Sources_superpostion(Circuit* c,Element* e_temp)
{
	Circuit* c_copy = c->Copy();
	Node* n = c_copy->GetFirstNode();
	while(n != NULL)
	{
		Element* e = n->GetFirstElement();
		while(e != NULL)
		{
			if(e->GetType() == 'E' || e->GetType()=='J')
			{
				//check only on voltag and current sources and delete them
				if(e_temp->GetId() != e->GetId() || e_temp->GetType()!= e->GetType())
					//this condion is just to let a specific source 
				n->Remove(e);
			}
			e = e->GetNext();
		}
		n = n->GetNext();
	}
	return c_copy;
}

// remove all Voltage sources and current sources
void Disable_Sources(Circuit*& c)
{
	Node* n = c->GetFirstNode();
	while(n != NULL)
	{
		Element* e = n->GetFirstElement();
		while(e != NULL)
		{
			if(e->GetType() == 'E' || e->GetType()=='J')
			//check only on voltag and current sources and delete them
			{
				n->Remove(e);
			}
			e = e->GetNext();
		}
		n = n->GetNext();
	}
}

// calculate voltage between two nodes
double Voltage(Node* n1, Node* n2)
{
	return(n1->GetVolt()-n2->GetVolt());     //v1-v2
}

// calculate amper between two nodes
double Ampere(Node* n1, Node* n2, Element* e, Circuit* c)
{
	if(e->GetType() == 'J') 
		// if the element is a current source so return the value of the current source
		return e->GetValue();

	else if(e->GetType() == 'E' )
		// if the element is a voltage source so the voltage source must be between two nodes
	{
		if(!n1->IsEssential())
			// if the n1 is non essential so this node has a voltage source and a resistance 
			// dr said that he will not test any an ideal source so if there is a voltage source there must be a non essential node
		{
			Element* e1 = n1->GetFirstElement();
			if(e1->GetId() == e ->GetId() && e1->GetType() == e->GetType())
				//check to get the resistance not the voltag
			{ 
				e1= e1->GetNext();
			}
				Node* n3= n1;
				Node* n4 = n2;
				Get_2_Nodes(e1,n3,n4,c);
				//get two nodes the have the resistance
				Node* n5 = n3;
				if( n3 != n1 )
			    //what we do here is just to have the correct sign 
				//and this is important for to get the correct power and the total power
				{
					n3 = n1;
			     	n4 = n5;
				}
				double V =Voltage(n3,n4);
				double A = V/e1->GetValue();
				return A;
		}
		else 
		{
			Element* e1 = n2->GetFirstElement();
			if(e1->GetId() == e ->GetId() && e1->GetType() == e->GetType())
			{ 
				e1= e1->GetNext();
			}
				Node* n3= n1;
				Node* n4 = n2;
				Get_2_Nodes(e1,n3,n4,c);
			    //get two nodes the have the resistance

				Node* n5 = n3;
				if( n3 != n2 )
				//what we do here is just to have the correct sign 
				//and this is important for to get the correct power and the total power
				{
					n3 = n2;
			     	n4 = n5;
				}
				double V =Voltage(n3,n4);
				double A = V/e1->GetValue();
				return A;
		}
	}
	else   // the element is a resistance
	    return ((n1->GetVolt() - n2->GetVolt()) / e->GetValue());     //(v1-v2)/r 
}


// calculate Power between two nodes
double Power(Element* e, Circuit* c)
{
	Node* n1;
	Node* n2;
	Element* e_temp;
	int i = 0;
	double I;


	//get two nodes the have the element
    Get_2_Nodes(e, n1, n2, c);
	
	switch (e->GetType())
	{
	case'E':
		{
		I = Ampere(n1,n2,e,c);
		//get the ampere
		if(! n1->IsEssential())
			// this condition is important for sign
		    //and this is important for to get the correct power and the total power
		{
			e_temp = n1->GetFirstElement();
			if(e_temp->GetType() != e ->GetType())
			{ 
				e_temp= e_temp->GetNext();
			}
		}
		else 
		{
			e_temp = n2->GetFirstElement();
			if(e_temp->GetType() != e ->GetType())
			{ 
				e_temp= e_temp->GetNext();
			}
		}
		    return (-1 * I*e_temp->GetValue() );
			// -1 I added it after ads told me supplied power is negative
			//and disspated power is positive
		}
		
	case'J':
		{
			//volt n1 - volt n2= v12
			//P = v12 * I
			e_temp = n1->GetFirstElement();
			// I try here to handel the sign 
			//by pointing a pointer to one of the two nodes that have the current source
		    // to get the value and the sign
		    bool check =true;
			while(check)
			{
				if(e_temp->GetId() == e->GetId()&& e_temp->GetType() == e->GetType())
				check = false;
				else
				e_temp = e_temp->GetNext();
			}
			return(-1 * (n1->GetVolt()-n2->GetVolt())*(e_temp->GetValue()));
		}

	default: //R
		//volt n1 - volt n2= v12 
		//P = [v12 *V12]/ R
		return(((n1->GetVolt()-n2->GetVolt())*(n1->GetVolt()-n2->GetVolt()))/e->GetValue());
		break;
		}


}

// find the two nodes that contains that element 
void Get_2_Nodes(Element* e, Node* &n1, Node* &n2, Circuit* c)
{
	Node* n = c->GetFirstNode();
	int i=0;
	int j=0;
	int id = e->GetId();
	char type = e->GetType();

	while(i<=1)
	{
		Element* e_temp = n->GetFirstElement();
		while(e_temp != NULL && j == 0)
		{
			if(e_temp->GetId() == id && e_temp->GetType() == type && i <= 0)
			{
				n1=n;
				j=1;
			}
			else if(e_temp->GetId() == id && e_temp->GetType() == type)
			{
				n2=n;
				j=1;
			} 
			else
				e_temp = e_temp->GetNext();
		}

		if (e_temp == NULL || j == 0)
		{
			n = n->GetNext();
		}
		else
		{
			j=0;
			n = n->GetNext();
			i++;
		}
	}
}

/*		public		*/

double Get_Total_Dissipated_Power(Circuit* c)
{
	Node* n1 = c->GetFirstNode();
	
	double TP = 0 ,P = 0;
	while (n1!=NULL)
	{
		Element* e1 =n1->GetFirstElement();
		while( e1 !=NULL)
		{
			if(e1->GetType() == 'R')
			{
				P = Power(e1,c);
			}
			else if( e1->GetType() == 'E'|| e1->GetType() == 'J' )
			{
				P = Power (e1,c);
				if(P < 0 )
				//this case is just to ensure that the power is dissipated or supplied
				P = 0;
			}
			TP = TP + P;
			P = 0;
			e1 = e1->GetNext();
		}
		n1 = n1->GetNext();
	}
	return TP / 2;
}

// calculate total power supplied in the circuit "negative"
double Get_Total_Supplied_Power(Circuit* c)
{
	double TP = 0 ,P = 0;

	Node* n1 = c->GetFirstNode();
	
	while (n1 != NULL)
	{
		Element* e1 = n1->GetFirstElement();
		while(e1 != NULL)
		{
			if (e1->GetType() == 'E' || e1->GetType() == 'J' )
			{
				P = Power(e1,c);
				if( P > 0)
				//this case is just to ensure that the power is dissipated or supplied
					P = 0;
			}
			TP = TP + P;
			P = 0;
			e1 = e1->GetNext();
		}
		n1 = n1->GetNext();
	}
	return TP / 2;
}

// returns true if total power is balanced, false otherwise
bool Circuit_Is_Power_Balanced(Circuit* circuit)
{
	double TSP = Get_Total_Supplied_Power(circuit);
	double TDP = Get_Total_Dissipated_Power(circuit);
	return ( Round(TSP, 1) + Round(TDP, 1) == 0 );
}


double Get_Res_Max(Circuit* circuit, Element* resistance)
{
	circuit = circuit->Copy();

	bool removed_1,removed_2;
	Element* resistance_2;  //pointer to the resistance in second node
	int resistance_2id;     //to store id of resistance

	Disable_Sources(circuit);

	Node** nodes = nullptr;  //array of pointers to nodes that have resistance
	nodes = circuit->GetTerminals(resistance);   

	resistance_2id = resistance->GetId();

	removed_1 = nodes[0]->Remove(resistance);   //delete resistance in first node

	resistance_2 = nodes[1]->GetElement(R, resistance_2id);

	removed_2 = nodes[1]->Remove(resistance_2);  //delete resistance in second node

	Element* e1 = new Element('j', 100, 1);    

	Element* e2= new Element('j', 100, -1);

	nodes[0]->Add(e1);                 //put current source in the place of resistance
								
	nodes[1]->Add(e2);

	Circuit *c2 = circuit->Copy();		//Copying The Circuit To Another Pointer

	voltageTransformation(c2);		//Voltage Source Transformation

	solve(c2);

	VoltageBack(c2, circuit);

	SolveNonEss(circuit);	

	return abs( Voltage(nodes[0], nodes[1]) );    // voltage ==  Rth
}


double Get_Pow_Max(Circuit* circuit, Element* resistance)
{
	circuit = circuit->Copy();

	double vth;

	Circuit *c2 = circuit->Copy();		//Copying The Circuit To Another Pointer
	
	voltageTransformation(c2);		//Voltage Source Transformation
	
	solve(c2);
	
	VoltageBack(c2, circuit);
	
	SolveNonEss(circuit);

	Node** nodes = circuit->GetTerminals(resistance);

	vth = Voltage(nodes[0], nodes[1]);   //Vth is the voltage acroos the resistance

	double rth = Get_Res_Max( circuit,  resistance);

	// just for debugging
	assert(rth != 0 && "trying to divide on zero, v-thevenin is zero, cant divide on it!");

	return ((vth * vth )/( 4 * rth));   //return pmax

}

/*   Extended public   */

// current in given element
double Get_Current(Circuit* circuit, Element* element)
{
	Node** nodes = circuit->GetTerminals(element);       //get terminals of element

 	return  Ampere(nodes[0], nodes[1], element, circuit);
}

// current in element due to another element
// (the current that due_to_element caused in element)
double Get_Current(Circuit* circuit, Element* element, Element* due_to_element)
{
   	Circuit *c2;
  
	c2 = Disable_Sources_superpostion(circuit,due_to_element);    //disable the sources in the copied circuit except the due to element

    Circuit *c3 = c2->Copy();		//Copying The Circuit To Another Pointer
	   
	voltageTransformation(c3);		//Voltage Source Transformation

	solve(c3);

	VoltageBack(c3, c2);

	SolveNonEss(c2);

	return  Get_Current(c2,  element);

}

// positive when dissipated, negative when supplied
double Get_Power(Circuit* circuit, Element* element)
{
	Node* n1;
	Node* n2;
	Element* e_temp = element;
	int id=element->GetType();
	int i=0;
	double I;
    Get_2_Nodes(element,n1,n2,circuit);
	//get two nodes the have the element
	switch (id)
	{
	case'E':
		{
		I = Ampere(n1,n2,element,circuit);
		//get the ampere
		if(! n1->IsEssential())
			// this condition is important for sign
		    //and this is important for to get the correct power and the total power
		{
			e_temp = n1->GetFirstElement();
			if(e_temp->GetType() != element ->GetType())
			{ 
				e_temp= e_temp->GetNext();
			}
		}
		else 
		{
			e_temp = n2->GetFirstElement();
			if(e_temp->GetType() != element ->GetType())
			{ 
				e_temp= e_temp->GetNext();
			}
		}
		    return (-1 * I*e_temp->GetValue() );
			// -1 I added it after ads told me supplied power is negative
			//and disspated power is positive
		}
		
	case'J':
		{
			//volt n1 - volt n2= v12
			//P = v12 * I
			e_temp = n1->GetFirstElement();
			// I try here to handel the sign 
			//by pointing a pointer to one of the two nodes that have the current source
		    // to get the value and the sign
		    bool check =true;
			while(check)
			{
				if(e_temp->GetId() == element->GetId() && e_temp->GetType() == element->GetType())
					check = false;
				else
					e_temp =e_temp->GetNext();
			}
			return((n1->GetVolt()-n2->GetVolt())*(e_temp->GetValue()));
		}

	default: //R
		//volt n1 - volt n2= v12 
		//P = [v12 *V12]/ R
		assert(e_temp->GetValue() == 0 && "error, attempt to divide on zero, elemet e_temp value is zero");

		return(((n1->GetVolt() - n2->GetVolt()) * (n1->GetVolt() - n2->GetVolt())) / e_temp->GetValue());
		break;
		}


}

// voltage difference between node1 & node2
// given the ids' of them, it searched for them in circuit
// given ids' are expected to be valid (in the circuit)
double Get_VoltDiff(Circuit* circuit, const int node1_id, const int node2_id)
{
	Node*node1 = circuit->GetNode( node1_id);

	Node*node2 = circuit->GetNode( node2_id);      //get pointers to the nodes by their id

	return Voltage(node1, node2);
}

// voltage differnt between two nodes that due_to_element caused 
double Get_VoltDiff(Circuit* circuit, const int node1_id, const int node2_id, Element*& due_to_element)
{ 
	Circuit *c2;
  
	c2 = Disable_Sources_superpostion(circuit, due_to_element);

    Circuit *c3 = c2->Copy();		//Copying The Circuit To Another Pointer
	   
	voltageTransformation(c3);		//Voltage Source Transformation

	solve(c3);

	VoltageBack(c3, c2);

	SolveNonEss(c2);

	return Get_VoltDiff(c2,  node1_id,  node2_id);
}

double roundf(double x)
{
   return x >= 0.0f ? floorf(x + 0.5f) : ceilf(x - 0.5f);
}

// round num to given precision
double Round(const double &num, const int precision)
{
  int helper = pow(10, precision);
  
  // check helper is not zero
  assert(helper != 0 && "dividing on zero");
  
  return (roundf(num * helper) / helper);
}
