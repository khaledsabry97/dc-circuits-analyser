#include "Data.h"
#include "Solving.h"

void print_interface_commands()
{
	cout	 << GREEN
			 << "Enter the action you want to perform" << endl
			 << "Valid commands" << endl
			 << "-> I				current passing through the element" << endl
			 << "-> P				the power supplied or disipated by the element" << endl
			 << "-> V				the voltage difference between two nodes" << endl
			 << "-> R				the maximum resistance  " << endl
			 << "-> M				the maximum power" << endl
			 << "-> x				Exit" << endl
			 << WHITE;
}

void Interface(Circuit * c) {
	void print_interface_commands();
	char option;
	
	while (true) {
		cin >> option;
		option = toupper(option);


		if(option=='I'){
			cout << "Enter the element please  " << endl;
			char TYPE; int ID;
			cin >> TYPE >> ID;
			TYPE = toupper(TYPE);
			Element* e;
			e = c->GetElement(TYPE, ID);
			if (!e)
			{
				cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
				void print_interface_commands();
				continue;
			}
			cout << "press 1 to get current due to spacefic source, 0 to continue " << endl;
			int option2;
			cin >> option2;

			if (option2 == 1 && e->GetType() == 'R') {
				Element  *spacefic = NULL;
				char Stype; int Sid;
				cout << "Enter the Source please  " << endl;
				cin >> Stype >> Sid;
				Stype = toupper(Stype);
				spacefic = c->GetElement(Stype, Sid);
				if (!spacefic)
				{
					cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
					void print_interface_commands();
					continue;
				}
				else if (spacefic->GetType() == 'J' || spacefic->GetType() == 'E')
					cout << "I= " << Get_Current(c, e, spacefic) << endl;
				else
				{
					cout << BLUE << "You Didn't Enter A Source\n Please Try Again\n" << WHITE;
					void print_interface_commands();
					continue;
				}
			}
			else
			{
				if (TYPE == 'R')
					cout << "I= " << fabs(Get_Current(c, e)) << endl;
				else
					cout << "I= " << Get_Current(c, e) << endl;
			}
	}

			
		else if (option == 'V') {
			cout << "Enter the element " << endl;
			Element *E = NULL;
			char Type1; int ID1;
			cin >> Type1 >> ID1;
			E = c->GetElement(Type1, ID1);
			if (!E)
			{
				cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
				void print_interface_commands();
				continue;
			}
			int Node1, Node2;
			Node** ptr = NULL;
			ptr =  c->GetTerminals(E);
			Node1 = ptr[0]->GetId();
			Node2 = ptr[1]->GetId();
			Element  *e1 = NULL;
			cout << "press 1 to get Voltage Dif due to spacefic source , 0 to continue" << endl;
			int option2;
			cin >> option2;
			if (option2 == 1 && E->GetType() == 'R') {

				cout << "Enter the source please " << endl;
				char Stype; int Sid;
				cin >> Stype >> Sid;
				e1 = c->GetElement(Stype, Sid);
				if (!e1)
				{
					cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
					void print_interface_commands();
					continue;
				}
				else if (e1->GetType() == 'J' || e1->GetType() == 'E')
					cout << "V= " << Get_VoltDiff(c, Node1, Node2, e1)<<endl;
				else
				{
					cout << BLUE << "You Didn't Enter A Source\n Please Try Again\n" << WHITE;
					void print_interface_commands();
					continue;
				}	
			}
			else
			{
				if(E->GetType() == 'J')
					cout << "V= " << Get_VoltDiff(c, Node1, Node2)<<endl;
				else
					cout << "V= " << fabs(Get_VoltDiff(c, Node1, Node2))<<endl;
			}


		}

		else if (option == 'P') {
			cout << "Enter the element please  " << endl;
			Element *e1 = NULL;
			char PTYPE; int PID;
			cin >> PTYPE >> PID;
			e1 = c->GetElement(PTYPE, PID);
			if (!e1)
			{
				cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
				void print_interface_commands();
				continue;
			}
			cout<<"P= "<<Get_Power(c, e1)<<endl;


		}
		else if (option == 'R') {
			cout << "Enter the Resistance please  " << endl;
			Element *E2 = NULL;
			char RTYPE; int RID;
			cin >> RTYPE >> RID;
			E2 = c->GetElement(RTYPE, RID);
			if (!E2)
			{
				cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
				void print_interface_commands();
				continue;
			}
			else if (E2->GetType() == 'R')
				cout<<"Rmax = "<<Get_Res_Max(c, E2)<<endl;
			else
			{
				cout << BLUE << "You Didn't Enter An Resestance\nPlease Try The Option Again\n";
				void print_interface_commands();
				continue;
			}
		}
		else if (option == 'M') {
			cout << "Enter the Resistance please  " << endl;
			Element *E3 = NULL;
			char MTYPE; int MID;
			cin >> MTYPE >> MID;
			E3 = c->GetElement(MTYPE, MID);
			if (!E3)
			{
				cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
				void print_interface_commands();
				continue;
			}
			else if (E3->GetType() == 'R')
				cout << "Pmax = " << Get_Pow_Max(c, E3) << endl;
			else
			{
				cout << BLUE << "You Didn't Enter An Resestance\nPlease Try The Option Again\n";
				void print_interface_commands();
				continue;
			}
		}

		else if (option == 'X')
		{
			break;
		}
		else if (option == 'H')
		{
			void print_interface_commands();
		}
		else {
			HandleError(INVALID_INPUT);
		}
		
	}
}