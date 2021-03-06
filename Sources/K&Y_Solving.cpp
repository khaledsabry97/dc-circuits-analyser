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

Node *searchNode(Circuit *c, Element *e, int nodeID)
{
	Node *n = c->GetFirstNode();
	while (n)
	{
		Element *ele = n->GetFirstElement();
		while (ele)
		{
			if (ele->GetId() == e->GetId() && ele->GetType() ==e->GetType() && n->GetId() != nodeID)
			{
				return n;
			}
			ele = ele->GetNext();
		}
		n = n->GetNext();
	}
	return NULL;
}

// remove all Voltage sources and current sources only one source remains
// return circuit with one (voltag or current) source 
Circuit* Disable_Sources_superpostion(Circuit* c,Element* e_temp)
{
	Circuit* c_copy = c->CopyAndReset();
	Node* n = c_copy->GetFirstNode();
	Node *n_temp;
	while(n != NULL)
	{
		Element* e = n->GetFirstElement();
		while(e != NULL)
		{
			if(e->GetType()=='J')
			{
				//check only on voltag and current sources and delete them
				if(e_temp->GetId() == e->GetId() && e_temp->GetType() == e->GetType())
					//this condion is just to let a specific source 
				{
					e = e->GetNext();
					continue;
				}
				else
				{
					n->Remove(e);
					e = n->GetFirstElement();
					continue;
				}
			}
			else if (e->GetType() == 'E')
			{
				if (!n->IsEssential())
				{
					if(e_temp->GetId() == e->GetId() && e_temp->GetType() == e->GetType())
					{
						e = e->GetNext();
						continue;
					}
					n_temp = searchNode(c_copy, e, n->GetId());
					Element *e_temp2 = n_temp->GetFirstElement();
					while (e_temp2->GetType() != e->GetType() && e_temp2->GetId() != e->GetId())
						e_temp2 = e_temp2->GetNext();
					n->Remove(e);
					e = n->GetFirstElement();
					Element *ele = e->Copy();//solution: add a copy of e in n_temp, not e itself
					n_temp->Remove(e_temp2);
					n_temp->Add(ele);
					bool test = c_copy->Remove(n->GetId());
					n = c->GetFirstNode();
					e = n->GetFirstElement();
					continue;
				}
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
	Node *n_temp;
	while(n != NULL)
	{
		Element* e = n->GetFirstElement();
		while(e != NULL)
		{
			if(e->GetType() == 'E' || e->GetType()=='J')
			//check only on voltag and current sources and delete them
			{
				if (!n->IsEssential())
				{
					n_temp = searchNode(c, e, n->GetId());
					Element *e_temp2 = n_temp->GetFirstElement();
					while (e_temp2->GetType() != e->GetType() && e_temp2->GetId() != e->GetId())
						e_temp2 = e_temp2->GetNext();
					n->Remove(e);
					e = n->GetFirstElement();
					Element *ele = e->Copy();//solution: add a copy of e in n_temp, not e itself
					n_temp->Remove(e_temp2);
					n_temp->Add(ele);
					bool test = c->Remove(n->GetId());
					n = c->GetFirstNode();
					e = n->GetFirstElement();
					continue;
				}
				else
				{
					n->Remove(e);
					e = n->GetFirstElement();
					continue;
				}
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

				Node** terminals = c->GetTerminals(e);
				//get two nodes the have the resistance
				Node* n5 = terminals[0];
				if( terminals[0] != n1 )
			    //what we do here is just to have the correct sign 
				//and this is important for to get the correct power and the total power
				{
					terminals[0] = n1;
			     	terminals[1] = n5;
				}
				double V =Voltage(terminals[0],terminals[1]);
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
				Node** terminals = c->GetTerminals(e);
				//get two nodes the have the resistance
				Node* n5 = terminals[0];
				if( terminals[0] != n2 )
			    //what we do here is just to have the correct sign 
				//and this is important for to get the correct power and the total power
				{
					terminals[0] = n2;
			     	terminals[1] = n5;
				}
				double V =Voltage(terminals[0],terminals[1]);
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
    Node** terminals = c->GetTerminals(e);

	// not one of them is found, element is not in circuit
	if (terminals == NULL)
		return 0;
	
	switch (e->GetType())
	{
	case'E':
		{
		I = Ampere(terminals[0],terminals[1],e,c);
		//get the ampere
		if(! terminals[0]->IsEssential())
			// this condition is important for sign
		    //and this is important for to get the correct power and the total power
		{
			e_temp = terminals[0]->GetFirstElement();
			if(e_temp->GetType() != e ->GetType())
			{ 
				e_temp= e_temp->GetNext();
			}
		}
		else 
		{
			e_temp = terminals[1]->GetFirstElement();
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
			e_temp = terminals[0]->GetFirstElement();
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
			return(-1 * (terminals[0]->GetVolt()-terminals[1]->GetVolt())*(e_temp->GetValue()));
		}

	default: //R
		//volt n1 - volt n2= v12 
		//P = [v12 *V12]/ R
		return(((terminals[0]->GetVolt()-terminals[1]->GetVolt())*(terminals[0]->GetVolt()-terminals[1]->GetVolt()))/e->GetValue());
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
			//else if( e1->GetType() == 'E'|| e1->GetType() == 'J' )
			//{
				/*P = Power (e1,c);*/
			//	if(P < 0 )
			//	//this case is just to ensure that the power is dissipated or supplied
			//	P = 0;
			//}
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
			if (e1->GetType() == 'R')
			{
				e1 = e1->GetNext();
				continue;
			}
			//if (e1->GetType() == 'E' || e1->GetType() == 'J' )
			//{
				P = Power(e1,c);
			//	if( P > 0)
			//	//this case is just to ensure that the power is dissipated or supplied
			//		P = 0;
			//}
			TP = TP + P;
			P = 0;
			e1 = e1->GetNext();
		}
		n1 = n1->GetNext();
	}
	return TP / 2;
}

// returns true if total power is balanced, false otherwise
void Check_Circ_Is_PowerBalanced(Circuit* c)
{
	double TSP = fabs(Get_Total_Supplied_Power(c));
	double TDP = fabs(Get_Total_Dissipated_Power(c));

	// set precision when printing to 4 digits
	cout.precision(4);

	// it is required to print both
	cout << "Total Supplied Power = " << TSP << '\n';
	cout << "Total Dissipated Power = " << TDP << '\n';

	// store difference in integer so we get only 0 or 1 ommitting tiny differences in float number
	int difference = Round(TSP, 4) - Round(TDP, 4);
	
	// to be balanced, difference should be between -1 and 1
	if (difference <= 1 && difference >= -1)
		cout << "The Circuit Is Balanced\n";
	else
		cout << "The Circuit Isn't Balanced\n";
}


double Get_Res_Max(Circuit* c, Element* resistance)
{
	Circuit *circuit = c->CopyAndReset();

	bool removed_1,removed_2;
	Element* resistance_2;  //pointer to the resistance in second node
	int resistance_2id;     //to store id of resistance

	Disable_Sources(circuit);

	Node** nodes = nullptr;  //array of pointers to nodes that have resistance
	nodes = circuit->GetTerminals(resistance);   

	resistance_2id = resistance->GetId();
	Element *res = nodes[0]->GetElement(resistance->GetType(), resistance->GetId());

	removed_1 = nodes[0]->Remove(res);   //delete resistance in first node

	resistance_2 = nodes[1]->GetElement('R', resistance_2id);

	removed_2 = nodes[1]->Remove(resistance_2);  //delete resistance in second node

	Element* e1 = new Element('j', 100, 1);    

	Element* e2= new Element('j', 100, -1);

	nodes[0]->Add(e1);                 //put current source in the place of resistance
								
	nodes[1]->Add(e2);

	Circuit *c2 = circuit->CopyAndReset();		//Copying The Circuit To Another Pointer

	voltageTransformation(c2);		//Voltage Source Transformation

	solve(c2);

	VoltageBack(c2, circuit);

	SolveNonEss(circuit);	

	print(circuit);

	return abs( Voltage(nodes[0], nodes[1]) );    // voltage ==  Rth
}


double Get_Pow_Max(Circuit* c, Element* resistance)
{
	Circuit *circuit = c->CopyAndReset();

	double vth;

	Circuit *c2 = circuit->Copy();		//CopyAndReseting The Circuit To Another Pointer
	
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

    Circuit *c3 = c2->Copy();		//CopyAndReseting The Circuit To Another Pointer
	   
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
	int i=0;
	double I;
    Node** terminals = circuit->GetTerminals(element);
	//get two nodes the have the element
	switch (element->GetType())
	{
	case'E':
		{
		I = Ampere(terminals[0],terminals[1],element,circuit);
		//get the ampere
		if(! terminals[0]->IsEssential())
			// this condition is important for sign
		    //and this is important for to get the correct power and the total power
		{
			e_temp = terminals[0]->GetFirstElement();
			if(e_temp->GetType() != element ->GetType())
			{ 
				e_temp= e_temp->GetNext();
			}
		}
		else 
		{
			e_temp = terminals[1]->GetFirstElement();
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
			e_temp = terminals[0]->GetFirstElement();
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
			return((terminals[0]->GetVolt()-n2->GetVolt())*(e_temp->GetValue()));
		}

	default: //R
		//volt n1 - volt n2= v12 
		//P = [v12 *V12]/ R
		//assert(e_temp->GetValue() == 0 && "error, attempt to divide on zero, elemet e_temp value is zero");
		if (e_temp->GetValue() == 0)
		{
			cout << RED << "\terror, attempt to divide on zero, elemet e_temp value is zero" <<endl << WHITE;
			return 0;
		}

		return(((terminals[0]->GetVolt() - terminals[1]->GetVolt()) * (terminals[0]->GetVolt() - terminals[1]->GetVolt())) / e_temp->GetValue());
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

	if (!node1)
	{
		cout << "The First Node Doesn't Exist\n";
		return 0;
	}
	if (!node2)
	{
		cout << "The Second Node Is Not Exist\n";
		return 0;
	}

	return Voltage(node1, node2);
}

// voltage differnt between two nodes that due_to_element caused 
double Get_VoltDiff(Circuit* circuit, const int node1_id, const int node2_id, Element*& due_to_element)
{ 
	Circuit *c2;
  
	c2 = Disable_Sources_superpostion(circuit, due_to_element);

    Circuit *c3 = c2->CopyAndReset();		//Copying The Circuit To Another Pointer
	   
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
