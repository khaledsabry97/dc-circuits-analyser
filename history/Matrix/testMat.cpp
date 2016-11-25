#include<iostream>
#include "matrix.h"
#include "matrix.h"
using namespace std;


int main()
{
	// punch of declerations
	double arr[50][50];
	double arr3[50][50];
	double arr2[50][1];
	int size, numCol, i;
	double mainDet = 0;
	double det[50];
	double final[50];

	// input
	cout<<"Enter The Size Of The Matrix: ";
	cin>>size;

	insert(arr,arr2,size);
	print(arr,arr2,size);
	intElements(arr,size);
	mainDet = detMat(arr,size);

	for(numCol = 0; numCol < size; numCol++)
	{
		swapMat(arr,arr2,size,numCol,arr3);
		print(arr3,arr2,size);
		intElements(arr3,size);
		det[numCol] = detMat(arr3,size);
	}

	// get determine
	cout<<"The Det Of Matrix is:  "<<mainDet<<endl;
	for(numCol = 0; numCol < size; numCol++)
	{
		if(mainDet == 0)
		{
			cout<<"No Soluotion!."<<endl;
			break;
		}
		else
		{
			final[numCol] = det[numCol] / mainDet;
		}
		cout << "The " << numCol + 1 << " Det = " << final[numCol] << endl;
	}

	// success
	return 0;
}
