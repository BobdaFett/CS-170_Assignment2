#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

int* makeOneDimArray(int arr[][10], int rows);
void SelectionSort(int* inputArray);
clock_t measure(int* inputArray, void (*sortMethod)(int*));

int main() {
	int testing[5][10]{};
	int random = 0;
	for (int row = 0; row < sizeof(testing) / sizeof(testing[0]); row++) {
		for (int col = 0; col < sizeof(testing[row]) / sizeof(int); col++) {
			random = rand() % 100 + 1;
			cout << "testing[" << row << "][" << col << "] = " << random << endl;
			testing[row][col] = random;
		}
	}
	int* oneDimArray = makeOneDimArray(testing, sizeof(testing) / sizeof(testing[0])); // create the 1d array.
	clock_t ticksToSort = measure(oneDimArray, SelectionSort);
	delete[] oneDimArray; // Return to memory
	return 0;
}

// This function only takes a 10 * 10 array.
// Must include the number of rows, as I have not found out how to get this without it.
int* makeOneDimArray(int arr[][10], int rows) {

	// Dereferencing a pointer to an array is the same as asking for the first row of it.
	int arrSize = (rows) * (sizeof(arr[0]) / sizeof(int));
	int col = sizeof(arr[0]) / sizeof(int);
	int* result = new int[arrSize];

	// Put all values, row by row, into one-dimensional array.
	int currentIndex = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < col; j++, currentIndex++)
			result[currentIndex] = arr[i][j];

	return result;
}

void SelectionSort(int* values) {
	int min_loc, temp;
	for (int current_loc = 0; current_loc < sizeof(values) - 1; current_loc++) {
		// Get the first value in the list, mark it as the smallest (for now)
		min_loc = values[current_loc];

		// Loop through the remaining values in the list and find the actual smallest number - store the index.
		for (int index = 0; index < sizeof(values); index++)
			if (values[min_loc] > values[index])
				min_loc = index;

		// Swap the smallest number with the value at the current_loc
		temp = values[current_loc];
		values[current_loc] = values[min_loc];
		values[min_loc] = temp;
	}

	cout << "Sorting finished." << endl;
}

/// <summary>
/// Measures the amount of time, in milliseconds, that it takes a sorting algorithm to complete.
/// <para>Uses clock_t</para>
/// </summary>
/// <param name="inputArray:">list of values to sort.</param>
/// <param name="sortMethod:">the function to measure duration of.</param>
clock_t measure(int* inputArray, void (*sortMethod)(int*)) {
	clock_t start, end;
	
	start = clock();
	sortMethod(inputArray);
	end = clock();

	cout << "Total ticks per second: " << CLOCKS_PER_SEC << endl;

	// Get number of seconds that went by.
	clock_t totalTicks = end - start;
	cout << "Total number of ticks: " << totalTicks << endl;
	// This is actually all in milliseconds.
	return totalTicks;
}