#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

// Author: Lucas Vas

int* makeOneDimArray(int arr[][10], int rows);
clock_t measure(int* inputArray, int size, void (*sortMethod)(int*, int));
void SelectionSort(int* inputArray, int size);
void merge(int arr[], int start, int mid, int end);
void mergeSort(int arr[], int start, int end);
void printArray(int arr[], int size);

int main() {
	int testing[100][10]{};
	int random = 0;
	for (int row = 0; row < sizeof(testing) / sizeof(testing[0]); row++) {
		for (int col = 0; col < sizeof(testing[row]) / sizeof(int); col++) {
			random = rand() % 100 + 1;
			/*cout << "testing[" << row << "][" << col << "] = " << random << endl;*/
			testing[row][col] = random;
		}
	}
	int* oneDimArray = makeOneDimArray(testing, sizeof(testing) / sizeof(testing[0])); // create the 1d array.
	clock_t ticksSelection = measure(oneDimArray, 1000, SelectionSort);
	delete[] oneDimArray; // Return to memory

	cout << "The total number of milliseconds this sort took to complete was " << ticksSelection << "ms." << endl;
	return 0;
}

// This function only takes an x * 10 array.
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

// Measures the amount of time for a sorting algorithm.
clock_t measure(int* inputArray, int size, void (*sortMethod)(int*, int)) {
	clock_t start, end;

	start = clock();
	sortMethod(inputArray, size);
	/*printArray(inputArray, size);*/ // This was so that i could verify this was not counting in seconds
	end = clock();

	/*cout << "Total ticks per second: " << CLOCKS_PER_SEC << endl;*/

	// Get number of ticks that went by.
	clock_t totalTicks = end - start;
	/*cout << "Total number of ticks: " << totalTicks << endl;*/
	// This is actually all in milliseconds, no need to truly convert anything, however just to make sure in case CLOCKS_PER_SEC is dynamic divide properly.
	return (double)totalTicks / (double)(CLOCKS_PER_SEC / 1000);
}

// Anything after this point is a sorting algorithm.

void SelectionSort(int* values, int size) {
	int min_loc, temp;
	for (int current_loc = 0; current_loc < size - 1; current_loc++) {
		// Get the first value in the list, mark it as the smallest (for now)
		min_loc = current_loc;

		// Loop through the remaining values in the list and find the actual smallest number - store the index.
		for (int index = current_loc + 1; index < size; index++)
			if (values[min_loc] > values[index])
				min_loc = index;

		// Swap the smallest number with the value at the current_loc
		temp = values[current_loc];
		values[current_loc] = values[min_loc];
		values[min_loc] = temp;
	}
}

// This merge sort doesn't actually work for the function pointer in measure().

void merge(int arr[], const int start, const int mid, const int end) {
	// Create a temp array
	int* tempArray = new int[end - start + 1];

	// Create a temp int, crawlers for both first and second half indexes
	int temp = 0, firstIndex = start, secondIndex = end;

	// Traverse both arrays and add the smaller of both elements in temp
	while (firstIndex < mid && secondIndex < end) {
		if (arr[firstIndex] < arr[secondIndex])
			tempArray[temp++] = arr[firstIndex++];
		else
			tempArray[temp++] = arr[secondIndex++];
	}

	// Add the elements that are left in both arrays
	while (firstIndex <= mid) {
		tempArray[temp] = arr[firstIndex];
		temp++; firstIndex++;
	}
	while (secondIndex <= end) {
		tempArray[temp] = arr[secondIndex];
		temp++; secondIndex++;
	}

	// Copy entire temp array to the original array.
	for (int i = start; i < end; i++)
		arr[i] = tempArray[i - start];
}

// This algorithm actually does the sorting of the array.
void mergeSort(int arr[], int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		mergeSort(arr, start, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, start, mid, end);
	}
}

// Only for debugging.
void printArray(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		cout << "arr[" << i << "] = " << arr[i] << endl;
	}
}