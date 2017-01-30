#include "Data.h"
#include "Solving.h"

void print_interface_commands()
{
	cout	 << GREEN
			 << "Enter the action you want to perform" << endl
			 << "Valid commands:" << endl
			 << "----> I \tcurrent passing through an element" << endl
			 << "----> P \tpower supplied or disipated in an element" << endl
			 << "----> VN \tvoltage difference between two nodes" << endl
			 << "----> VE \tvoltage difference on element" <<endl
			 << "----> R \tmaximum resistance  " << endl
			 << "----> M \tmaximum power" << endl
			 << "----> H \thelp" << endl
			 << "----> C \tcredits" << endl
			 << "----> # \tmake a comment" << endl
			 << "----> x \tExit" << endl << endl
			 << WHITE;
}

void Interface(Circuit * c) {
	print_interface_commands();
	char option;
	
	while (true) {
		Print_Prompt();
		cin >> option;
		option = toupper(option);


		if(option=='I'){
			cout << "Enter the element please  " << endl;
			char TYPE; int ID;
			Print_Prompt();
			cin >> TYPE >> ID;
			TYPE = toupper(TYPE);
			Element* e;
			e = c->GetElement(TYPE, ID);
			if (!e)
			{
				cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
				print_interface_commands();
				continue;
			}
			cout << BLUE << "press 1 to get current due to spacefic source, 0 to continue " << endl << WHITE;
			int option2;
			Print_Prompt();
			cin >> option2;

			if (option2 == 1 && e->GetType() == 'R') {
				Element  *spacefic = NULL;
				char Stype; int Sid;
				cout << "Enter the Source please  " << endl;
				Print_Prompt();
				cin >> Stype >> Sid;
				Stype = toupper(Stype);
				spacefic = c->GetElement(Stype, Sid);
				if (!spacefic)
				{
					cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
					print_interface_commands();
					continue;
				}
				else if (spacefic->GetType() == 'J' || spacefic->GetType() == 'E')
					cout << GREEN << "I= " << Get_Current(c, e, spacefic) << endl << WHITE;
				else
				{
					cout << RED << "You Didn't Enter A Source\n Please Try Again\n" << WHITE;
					print_interface_commands();
					continue;
				}
			}
			else
			{
				if (TYPE == 'R')
					cout << GREEN << "I= " << fabs(Get_Current(c, e)) << endl << WHITE;
				else
					cout << GREEN << "I= " << Get_Current(c, e) << endl << WHITE;
			}
	}

			
		else if (option == 'V') {
			char op;
			cin >> op;
			op = toupper(op);
			if (op == 'E')
			{
				cout << "Enter the element " << endl;
				Element *E = NULL;
				char Type1; int ID1;
				Print_Prompt();
				cin >> Type1 >> ID1;
				Type1 = toupper(Type1);
				E = c->GetElement(Type1, ID1);
				if (!E)
				{
					cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
					print_interface_commands();
					continue;
				}
				int Node1, Node2;
				Node** ptr = NULL;
				ptr =  c->GetTerminals(E);
				Node1 = ptr[0]->GetId();
				Node2 = ptr[1]->GetId();
				Element  *e1 = NULL;
				cout << BLUE << "press 1 to get Voltage Dif due to spacefic source , 0 to continue" << endl << WHITE;
				int option2;
				Print_Prompt();
				cin >> option2;
				if (option2 == 1 && E->GetType() == 'R') {

					cout << "Enter the source please " << endl;
					char Stype; int Sid;
					Print_Prompt();
					cin >> Stype >> Sid;
					Stype = toupper(Stype);
					e1 = c->GetElement(Stype, Sid);
					if (!e1)
					{
						cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
						print_interface_commands();
						continue;
					}
					else if (e1->GetType() == 'J' || e1->GetType() == 'E')
						cout << GREEN << "V= " << fabs(Get_VoltDiff(c, Node1, Node2, e1)) << endl << WHITE;
					else
					{
						cout << RED << "You Didn't Enter A Source\n Please Try Again\n" << WHITE;
						print_interface_commands();
						continue;
					}	
				}
				else
				{
					if(E->GetType() == 'J')
						cout << GREEN << "V= " << Get_VoltDiff(c, Node1, Node2) << endl << WHITE;
					else
						cout << GREEN << "V= " << fabs(Get_VoltDiff(c, Node1, Node2)) << endl << WHITE;
				}
			}
			else if (op == 'N')
			{
				int node1, node2;
				//node1 = node2 = -1;
				cout << "Enter The Two Nodes\n";
				cin >> node1 >> node2;
				cout << BLUE << "press 1 to get Voltage Dif due to spacefic source , 0 to continue" << endl << WHITE;
				int op2;
				cin >> op2;
				if (op2 == 1)
				{
					cout << "Enter the source please " << endl;
					char Stype; int Sid;
					Print_Prompt();
					cin >> Stype >> Sid;
					Stype = toupper(Stype);
					Element *e1 = c->GetElement(Stype, Sid);
					if (!e1)
					{
						cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
						print_interface_commands();
						continue;
					}
					else if (e1->GetType() == 'J' || e1->GetType() == 'E')
						cout << GREEN << "V= " << fabs(Get_VoltDiff(c, node1, node2, e1)) << endl << WHITE;
					else
					{
						cout << RED << "You Didn't Enter A Source\n Please Try Again\n" << WHITE;
						print_interface_commands();
						continue;
					}
				}
				else
					cout << GREEN << "V = " << fabs(Get_VoltDiff(c, node1, node2)) << endl << WHITE;
			}
		}

		else if (option == 'P') {
			cout << "Enter the element please  " << endl;
			Element *e1 = NULL;
			char PTYPE; int PID;
			Print_Prompt();
			cin >> PTYPE >> PID;
			PTYPE = toupper(PTYPE);
			e1 = c->GetElement(PTYPE, PID);
			if (!e1)
			{
				cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
				print_interface_commands();
				continue;
			}
			cout<< GREEN << "P= "<<Get_Power(c, e1) << endl << WHITE;
		}
		else if (option == 'R') {
			cout << "Enter the Resistance please  " << endl;
			Element *E2 = NULL;
			char RTYPE; int RID;
			Print_Prompt();
			cin >> RTYPE >> RID;
			RTYPE = toupper(RTYPE);
			E2 = c->GetElement(RTYPE, RID);
			if (!E2)
			{
				cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
				print_interface_commands();
				continue;
			}
			else if (E2->GetType() == 'R')
				cout<< GREEN << "Rmax = "<<Get_Res_Max(c, E2) << endl << WHITE;
			else
			{
				cout << RED << "You Didn't Enter An Resestance\nPlease Try The Option Again\n" << WHITE;
				print_interface_commands();
				continue;
			}
		}
		else if (option == 'M') {
			cout << "Enter the Resistance please  " << endl;
			Element *E3 = NULL;
			char MTYPE; int MID;
			Print_Prompt();
			cin >> MTYPE >> MID;
			MTYPE = toupper(MTYPE);
			E3 = c->GetElement(MTYPE, MID);
			if (!E3)
			{
				cerr << RED << "\tEntered element doesn\'t exist\n" << WHITE;
				print_interface_commands();
				continue;
			}
			else if (E3->GetType() == 'R')
				cout << GREEN << "Pmax = " << Get_Pow_Max(c, E3) << endl << WHITE;
			else
			{
				cout << RED << "You Didn't Enter An Resestance\nPlease Try The Option Again\n" << WHITE;
				print_interface_commands();
				continue;
			}
		}

		else if (option == 'X')
		{
			cout << "System Exit\nThank You\n";
			Print_Credits();
			break;
		}
		else if (option == 'H')
		{
			print_interface_commands();
		}
		else if (option == '#')
		{
			continue;
		}
		else if (option == 'C')
		{
			Print_Credits();
		}
		else {
			HandleError(INVALID_INPUT);
		}
		
	}
}