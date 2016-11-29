#include "Data.h"


/*      Element     */

// public:

Element(const char &type, const int &id, const double &value);
~Element();

char GetType();
void ChangeType(const char &c);
int GetId();
void ChangeId(const int &num);
double GetValue();
void ChangeValue(const int &num);


// private:

void _SetType(const char &c);
void _SetValue(const int &num);
void _SetId(const int &id);