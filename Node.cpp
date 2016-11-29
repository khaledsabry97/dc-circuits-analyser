#include "Data.h"

/*      Node        */

// public:
Node(const int &id);
~Node();

int GetId();
void ChangeVolt(const double &v);
double GetVolt();
int GetNumOfElem();
bool IsEssential();
void Add(Element* e);
void Remove(Element* e);

// private:
