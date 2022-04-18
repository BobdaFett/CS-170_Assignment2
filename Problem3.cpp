#include <iostream>
#include <iomanip>
using namespace std;

/*
* Magic square is filled with n^2 values
* Use the following algorithm:
*	Place 1 in the middle of the bottom row.
*	After k has been placed in the (i, j) square, place k + 1 into the square to the right and down, wrapping around the borders.
*	If you reach a square that has been filled, move one square up instead.
* Write and test a funciton with argument n, which prints a magic square in order of n if n is odd.
* 
* 3 rules apply:
* The position of next number is calculated by decrementing row number of the previous number by 1, and incrementing the column number 
*	of the previous number by 1. 
*	At any time, if the calculated row position becomes -1, it will wrap around to n-1. 
*	Similarly, if the calculated column position becomes n, it will wrap around to 0.
*/

void MagicSquare(int n);

int main() {
	int userInput = 0;

	cout << "Please input an odd number for the size of your square: ";
	do {
		cin >> userInput;
		if (cin && userInput % 2 != 0 && userInput > 0) break;
		if (!cin) {
			cout << "Please enter a number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (userInput % 2 == 0) {
			cout << "Please enter an odd number: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (userInput < 0) {
			cout << "Please enter a positive number: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (true);

	MagicSquare(userInput);
	return 0;
}

void MagicSquare(const int n) {
	// Allocate the 2d array (dynamic to use the parameter as a size)
	int** arr = new int*[n];
	for (int i = 0; i < n; i++)
		arr[i] = new int[n];

	// Initialize the array to prevent "uninitialized memory" warnings
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			arr[i][j] = 0;

	// The first cell that is used is the one in the bottom/middle.
	int currentRow = n - 1;
	int currentCol = n / 2;

	int currentNumber = 1;
	do {
		// Checks for problems immediately. Will block uninitialized memory reads.
		if (currentRow >= n) {
			currentRow = 0;
			continue;
		}
		if (currentCol >= n) {
			currentCol = 0;
			continue;
		}

		// These must only trigger if the rows/columns have been corrected. Otherwise, program tries to read garbage memory.
		if (arr[currentRow][currentCol] <= 0) { // All empty cells are filled with a zero.
			arr[currentRow][currentCol] = currentNumber;
		}
		else if (arr[currentRow][currentCol] >= 0) { // The cell must be filled if this triggers
			currentRow--;
			continue;
		}

		// Increment all numbers that need to be incremented.
		currentRow++;
		currentCol++;
		currentNumber++;
	} while (currentNumber < 1 + (n * n));

	// Print array
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(4) << arr[i][j];
		}
		cout << '\n';
	}

	// Deallocate the array
	for (int i = 0; i < n; i++)
		delete[] arr[i];
	delete[] arr;
}