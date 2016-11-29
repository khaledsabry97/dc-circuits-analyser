#include "Data.h"

/*      Circuit     */

// public:
Circuit();
~Circuit();

bool Add(Node* n);
bool Remove(Node* n);
int GetNumOfNodes();
void Read();
void Push_back(Node* n);
void Push_front(Node* n);
bool Pop_back();
bool Pop_front();

// private:
