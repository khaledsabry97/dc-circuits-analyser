#ifdef _DO_NOT_INCLUDE_ME_
// do not include this header file in project

Documentation of the Classes:
listing public functionality only

#####   Circuit   #####

## SUMMARRY
Circuit();
Circuit(Circuit* c);
Circuit(Circuit& c);
Circuit* Copy();
void Read();
bool Repair();

void Add(Node* n);
bool Remove(Node* n);
Node* GetLastNode();
Node* GetFirstNode();
int GetNumOfNodes();
void Push_back(Node* n);
void Push_front(Node* n);
bool Pop_back();
bool Pop_front();

bool Remove(const double &val, SEARCH_BY type = ID);
Node* GetNode(const double &val, SEARCH_BY type = ID);
bool HasNode(const double &val, SEARCH_BY type = ID);
bool IsEmpty();


/* Constructs */

// normal declaration of circuit
// takes no input, just declare a one
Circuit();

// copy this circuit data to me,
// takes pointer of the other circuit
Circuit(Circuit* c);

<EXAMPLE>
    Circuit* someCirc = new Circuit;
    // fill it with data....
    // ..
    // let's copy it to new one
    Circuit* newcirc = new Circuit(someCirc);
    // newcirc is the same as someCirc
<END>

// copy this circuit data to me
// takes the other circuit as reference
// differs only in the input 
Circuit(Circuit& c);

/* Handle Nodes */

// add node to circuit 
// it pushs it front if it is essential, back otherwise 
// it doesn't check if node is valid, check this before calling add
void Add(Node* n);

<EXAMPLE>
    Circuit* c = new Circuit;
    Node* n = new Node(1);
    // fill the node with data ..
    c->Add(n);  // add node to circuit
<END>

// removes node from circuit
// WARNING! DO NOT GIVE IT A NODE FROM ANOTHER CIRCUIT, IT MAY RESULT IN FATAL ERROR
// WARNING! DO NOT PASS A NULL POINTER, IT WILL THROW ERROR AND TERMINATE PROGRAM
// return true if node is removed, false if no node was given
// boolean values may be used to delete all nodes by a while loop
bool Remove(Node* n);

<EXAMPLE>
    Circuit* c = new Circuit;
    Node* n = new Node(1);
    // fill the node with data ..
    c->Add(n);  // add node to circuit

    // now we want to remove it
    c->Remove(n);
<END>

// returns the address of the last node 
// if empty it returns nullptr
Node* GetLastNode();

<EXAMPLE>
    Circuit* c = new Circuit;
    // fill with data ..
    Node* last = c->GetLastNode();
    if (last != nullptr)
        cout << "Wow I have the last node!\n";
<END>

// returns the address of the first node 
// if empty it returns nullptr
Node* GetFirstNode();

// returns num of nodes in circut
int GetNumOfNodes();

// 1- read nodes from user
// 2- calls Reapair() to remove invalid items -- refer to Circuit::Repair()
// 3- throws (-1) and terminates program if circuit was empty, to avoid affecting other steps in program 
void Read();

<EXAMPLE>
    Circuit* c = new Circuit;
    c->Read();  
    // assume user filled it correctly 
    // it is full of valid data now
<END>

// add given node at the end of the list
// throws -1 and terminates program if it is null
void Push_back(Node* n);

<EXAMPLE>
    Circuit* c = new Circuit;
    Node* n = new Node(3);
    c->Push_back(n);
    // it is at the end of the list
<END>

// same as push_back but adds to front
void Push_front(Node* n);

// delete last node
bool Pop_back();

// delete first element
bool Pop_front();

<EXAMPLE>
    Circuit* c = new Circuit;
    // fill with data ..
    c->Pop_front();     // first one is deleted
    c->Pop_back();      // last one is deleted

    // let's delete em all!
    while (c->Pop_back());
<END>

/* Specific Nodes */

// search for a specific node and removes it if found
// calls Remove() when node is found
bool Remove(const double &val, SEARCH_BY type = ID);

<EXAMPLE>
    Circuit* c = new Circuit;
    // fill it..
    int the_id_i_hate = 4;
    c->Remove(the_id_i_hate, ID);   // this deletes the node with that id 

    // another way
    c->Remove(the_id_i_hate);       // it searchs depending on the id by default

    // i hate the nodes with voltage -1, let's delete first node that has this voltage 
    c->Remove(-1.0, VOLT);

    // let's delete all nodes with -1 volt
    while (c->Remove(-1.0, VOLT));
<END>

// search for specific node 
// returns address of node if found, nullptr otherwise
Node* GetNode(const double &val, SEARCH_BY type = ID);

<EXAMPLE>
    Circuit* c = new Circuit;
    // fill it..
    Node* myNode = c->GetNode(-1, VOLT);
    // myNode now has the address of first node that its volt == -1 v (if it exists)
    // let's delete that node
    if (myNode != nullptr)
        c->Remove(myNode);  // alternative way of deleting 
<END>

// search for specific node 
// returns true if found, false otherwise
bool HasNode(const double &val, SEARCH_BY type = ID);

/* other */

// returns true if circuit is empty, false otherwise
bool IsEmpty();

// returns a copy of this circuit
Circuit* Copy();

<EXAMPLE>
    Circuit* c = new Circuit;
    // fill it..
    Circuit* newC = c->Copy();      // now newC has the same items of c
<END>

// 1- iterates through all nodes and elements
// 2- checks for errors and handles them 
// issues like: c/v source with same sign in two nodes, duplicate element in more than 2 nodes, node that has one element... etc
bool Repair();

<EXAMPLE>
    Circuit* c = new Circuit;
    // fill it..
    c->Repair();
    // now all issues are handled, you can use it safely
<END>

#endif