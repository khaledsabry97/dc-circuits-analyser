#include "Data.h"


/*      Element     */

// public:

Element::Element(const char &type, const int &id, const double &value);
Element::~Element();

char Element::GetType();
void Element::ChangeType(const char &c);
int Element::GetId();
void Element::ChangeId(const int &num);
double Element::GetValue();
void Element::ChangeValue(const int &num);


// private:

void Element::_SetType(const char &c);
void Element::_SetValue(const int &num);
void Element::_SetId(const int &id);