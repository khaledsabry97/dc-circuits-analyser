/*      
    Circuit public methods source
*/
#include "Data.h"

// Constructor
Circuit::Circuit()
	:_firstNode(nullptr), _lastNode(nullptr), _numNodes(0)
{
}

Circuit::Circuit(Circuit* c)
{
    _Copy_this_to_me(c);
}

Circuit::Circuit(Circuit& c)
{
    _Copy_this_to_me(&c);
}

// Deconstructor
Circuit::~Circuit()
{
    while (Remove(_firstNode));
}

// read the whole circuit from the user
void Circuit::Read()
{
    // for temporary storage of elements
    _List my_list;

    _Read_nodes(my_list);
    
    _Remove_invalids(my_list); 
    _Remove_empty_nodes();   

    _Reread_if_empty();
}

// for testing 
void Circuit::Print()
{
	if(IsEmpty())
		cout << "The Circuit Is Empty\n";
	else
	{
        // get nodes in an vector
        int size = GetNumOfNodes();
        vector<Node*> vec(size, nullptr);

        // fill it
        Node* n = GetFirstNode();
        for (int i = 0; i < size; i++, n = n->GetNext())
            vec[i] = n;
        
        // sort it ascendingly
        sort(vec.begin(), vec.end(), _compareNodes);

        // print them sorted in the array
        for (int i = 0; i < size; i++)
        {
            n = vec[i];
            
            cout << "---Node #" << n->GetId() << " with voltage " << n->GetVolt() << " volt\n";

            Element* e = n->GetFirstElement();
            while (e)
            {
                cout << "-Element " << e->GetType() << e->GetId() << " = " << e->GetValue() << '\n';
                e = e->GetNext();
            }
        }
	}
}
            

void Circuit::Add(Node* n)
{
    /* pseudo:
        if essential:
            put at front of my_list
        else
            put at end of my_list

        put:
            ;let the pointer be ptr
            ptr.next points at n
            or -----> n.next points at ptr & ptr 
    */

    // handle Special case, when last and first are nullptrs
    if (n->IsEssential())
        _Push_front(n);
    else 
        _Push_back(n);

    // give it this circuit's address
    n->_from_circuit = this;
}

bool Circuit::Remove(Node* n)
{
    /*  pseudo:
        get previous node:
            start from beginning
            iterate until this.next = n
            if finsished without finding it, throw exception
        ;let prev = n-, this = n
        n-.next = n.next
        delete n

        ;check if n- exists

        ;special cases:
        ;n = firstnode ----> +
        ;n = lastnode -----> +
        ;n is not in my_list ---->  +
    */
    // cant delete null
    if (!n)
        return false;       
    // cant delete node if from another circuit
    if (n->_from_circuit != this)
        throw DEL_NODE_FROM_WRONG_CIRC;

    // node is on edge: first/last
    if (n == _firstNode)
        return _Pop_front();
    else if (n == _lastNode)
        return _Pop_back();

    // node is in middle
    Node* &n_minus = n->_prev;
    Node* &n_plus = n->_next;

    n_minus->_next = n_plus;
    n_plus->_prev = n_minus;
    delete n;
    _numNodes--;

    return true;
}

Node* Circuit::GetLastNode()
{
    return (_lastNode);
}

Node* Circuit::GetFirstNode()
{
    return (_firstNode);
}

int Circuit::GetNumOfNodes()
{
    return(_numNodes);
}

bool Circuit::Remove(const double &val, SEARCH_BY type)
{
    Node* temp = _firstNode;

    // iterate through my_list 
    while (!_IsIt(temp, val, type))
    {
        temp = temp->GetNext();
        if (!temp)  // not found
            return false;
    }

    return Remove(temp);
}

Node* Circuit::GetNode(const double &val, SEARCH_BY type)
{
     Node* temp = _firstNode;

    // iterate through my_list 
    while (!_IsIt(temp, val, type))
    {
        temp = temp->GetNext();
        if (!temp)  // not found
            return nullptr;
    }

    return temp;
}

bool Circuit::HasNode(const double &val, SEARCH_BY type)
{
    Node* temp = _firstNode;

    // iterate through my_list 
    while (!_IsIt(temp, val, type))
    {
        temp = temp->GetNext();
        if (!temp)  // not found
            return false;
    }

    return true;
}

bool Circuit::IsEmpty()
{
    return (_firstNode == nullptr && _lastNode == nullptr);
}

// returns address of new circuit that is deepCopied of this
Circuit* Circuit::Copy()
{
    // allocate data
    Circuit* newCirc = new Circuit;

    // copy nodes
    Node* originalNode = _firstNode;

    // traverse through them all till null
    while (originalNode)
    {
        Node* copiedNode = originalNode->Copy();
        newCirc->Add(copiedNode);

        // go to the next
        originalNode = originalNode->_next;
    }

    // here is your copy
    return newCirc;
}

// operator overloading for copy
Circuit& Circuit::operator= (Circuit &c)
{
    return (*c.Copy());
}

// search for element in circuit 
// returns the address of the element if found
// otherwise nullptr
Element* Circuit::GetElement(char type, const int &id)
{
    // through nodes
    Node* n = GetFirstNode();
    while (n)
    {
        Element* e = n->GetElement(type, id);
        if (e)  // found in this node
            return e;
        else 
            n = n->GetNext();   // no in this node
    }

    // not found
    return nullptr;
}

// returns true if element is found in circuit
// false otherwise
bool Circuit::HasElement(char type, const int &id)
{
    // through nodes
    Node* n = GetFirstNode();
    while (n)
    {
        if (n->HasElement(type, id))  // found in this node
            return true;
        else 
            n = n->GetNext();   // no in this node
    }

    // not found
    return false;
}

// returns 2 nodes that the given element is connected to 
Node** Circuit::GetTerminals(Element* e)
{
    // array to hold the addresses of the terminals
    Node** terminal = new Node*[2];
    terminal[0] = terminal[1] = nullptr;

    // select the first terminal, get him, then do the same for the second one
    int select = 0;

    while (true)   
    {
        // traverse through all nodes to get the first one 
        Node* n = GetFirstNode();
        while (n)
        {
            if (n->HasElement(e->GetType(), e->GetId()))
                terminal[select++] = n;

            n = n->GetNext();
        }

        // both of them is found
        if (terminal[0] && terminal[1])
            break;
        else
        {
            HandleError(UNAVAILABLE_ELEMENT);
            delete[] terminal;
            return nullptr;
            break;
        }
    }

    return terminal;
}

// the same as above, but takes 2 nodes by argument to put nodes in them
Node** Circuit::GetTerminals(Element* e, Node* &n1, Node* &n2)
{
    Node** terminals = GetTerminals(e);
    n1 = terminals[0];
    n2 = terminals[1];

    return terminals;
}

Circuit* Circuit::CopyAndReset()
{
    // allocate data
    Circuit* newCirc = new Circuit;

    // copy nodes
    Node* originalNode = _firstNode;

    // traverse through them all till null
    while (originalNode)
    {
        Node* copiedNode = originalNode->Copy();

        // reset it to zero
        copiedNode->_volt = 0;

        newCirc->Add(copiedNode);

        // go to the next
        originalNode = originalNode->_next;
    }

    // here is your copy
    return newCirc;
}