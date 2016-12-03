#pragma once
//#include "Solver.h"
#include "Data.h"

#define __TEST__

int main()
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

// int main()
// {
//     // test circuit 

//     Node* n;
//     Element* e;

//     // add nodes to circuit
//     Circuit* c = new Circuit;

//     for (int j = 20; j--;)
//     {
//         n = new Node(j);
//         for (int i = j; i--;)
//         {
//             e = new Element('E', i, i * 3 -9);
//             n->Add(e);
//         }
//         c->Add(n);
//     }

//     n = new Node(22);
//     c->Add(n);
    
//     Node* temp = c->GetNode(2, ID);
//     temp = c->GetNode(22, ID);
//     temp = c->GetNode(0, VOLT);

//     c->RemoveDuplicates();

//     bool x = c->HasNode(5, ID);
//     if (c->IsEmpty())
//         printf("it is empty\n");
//     else 
//         printf("wow! it is not empty\n");

//     c->Remove(5);
//     if (c->HasNode(5))
//         cout << "moseeba!\n";
//     else 
//         cout << "qeshta \n";

    
// }

// int main()
// {
//     // test circuit 

//     Node* n;
//     Element* e;

//     // add nodes to circuit
//     Circuit* c = new Circuit;

//     for (int j = 20; j--;)
//     {
//         n = new Node(j);
//         for (int i = j; i--;)
//         {
//             e = new Element('E', i, i * 3 -9);
//             n->Add(e);
//         }
//         c->Add(n);
//     }

//     n = new Node(22);
//     c->Add(n);
//     c->Remove(n);

//     c->GetLastNode();
//     c->GetFirstNode();

//     delete c;
// }

// int main()
// {
//     // elementary node test

//     Node* n = new Node(1);

//     n->GetId();

//     n->ChangeVolt(-9);
//     n->GetVolt();
//     n->ChangeVolt(+88.1);
//     n->GetVolt();

//     n->GetNumOfElem();
//     n->IsEssential();

//     n->GetFirstElem();
//     n->GetNext();
//     Node* m = new Node(2);
//     n->SetNext(m);

//     Element* s = new Element('r', 5, 9);
//     n->Add(s);
//     n->Remove(s);

//     n->Add(s);
//     s = new Element('j', 6, 90);
//     n->Add(s);
//     n->Add(s);

//     n->GetNumOfElem();
//     cout << n->IsEssential();
//     n->Remove(s);
//     cout << n->IsEssential();
// }

// int main()
// {
//     // elementary test to element
//     Element* n = new Element('r', 5, 33);
//     n->GetType();
//     n->ChangeType('j');
//     n->GetNext();
//     n->GetPrev();

//     Element* s = new Element('R', 33, 56);
//     n->SetNext(s);
//     delete s;
//     s = new Element('j', 3 ,33);
//     n->SetPrev(s);

//     n->GetId();
//     n->ChangeId(9);

//     n->GetValue();
//     n->ChangeValue(99);
// }

// void mat()
// {
//     Solver s(2,2);
//     s.A << 1 ,5, -1, 2;
//     s.B << 3, 5;
//     s.Print();
//     s.Solve();
//     cout << s.X;

// }

// void element1()
// {
//     Element* n = new Element("t", 55);
//     delete n;
// }

// int main()
// {
//     //mat();
//     //element1();
//     el2();
// }