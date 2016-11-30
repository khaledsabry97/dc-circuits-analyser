#include "Header.h"
using namespace std;
int main()
{
	node *head, *last, *head2;
	head = last = head2 = NULL;
	input(head, last);
	doubleList(head, head2);
	voltageTransformation(head2);
	printData(head2);
	return 0;
}