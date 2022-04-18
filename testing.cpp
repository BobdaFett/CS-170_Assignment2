#include <iostream>
using namespace std;

void printArray(int a[5]);
void printTwoDim(int a[][5]);
int* makeOneDimArray(int a[][10]);

const int SIZE = 10;

void main() {
	int arr[5][5] = {};
	for (int i = 0; i < 5; i++) arr[i][0] = i;
	for (int i = 0; i < 5; i++) arr[0][i] = i;
	printTwoDim(arr);
}

void printArray(int a[5]) {
	for (int i = 0; i < 5; i++)
		cout << a[i] << endl;
}

// This works.
void printTwoDim(int a[][5]) {
	// Create array

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << a[i][j] << " ";
		}
		cout << '\n';
	}
}

int* makeOneDimArray(int a[][SIZE]) {
	int* result = new int[SIZE * SIZE]; // Creates a DA one-dimensional array.
	cout << "sizeof(result) = " << sizeof(result) << endl;
	for (int i = 0; i < sizeof(a) / sizeof(int); i++) {}

	return result;
}