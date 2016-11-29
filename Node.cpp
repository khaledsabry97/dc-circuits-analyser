#include "Data.h"

/*      Node        */

// public:
Node::Node(const int &id);
~Node::Node();

int Node::GetId();
void Node::ChangeVolt(const double &v);
double Node::GetVolt();
int Node::GetNumOfElem();
bool Node::IsEssential();
void Node::Add(Element* e);
void Node::Remove(Element* e);

// private:
