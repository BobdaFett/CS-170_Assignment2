#include <iostream>
using namespace std;

const int SIZE = 100;
int reverseInt(int input);
int merge(int values[], int low, int high);
int mergeTogether(int values[], int low, int mid, int high);

int main() {
	return 0;
}

int reverseInt(int input) {
	// Copied straight off the board.
	// Reverse a number by placing the last digit before the reversal of it.... i have no idea what he's saying.
	if (input < 10) return input; // this will not work if the number is greater than 10.
	else {
		int head = input % 10;
		int next = input % 10;
		if (next < 10) head *= 10;
		int tail = reverseInt(input / 10); // This is the part that's throwing me off.
		int temp = tail;
		while (temp) {
			head *= 10;
			temp /= 10;
		}
		return head + tail;
	}
}

int merge(int values[], int low, int high) {
	int mid;
	if (low < high) {
		mid = (low + high) / 2;
		merge(values, low, mid);
		merge(values, mid + 1, high);
		mergeTogether(values, low, mid, high);
	}
}

void mergeTogether(int values[], int low, int mid, const int high) {
	// Not all of these values will be in the correct order between the two lists.
	int first_loc = low, second_loc = mid + 1, merged_loc = low;
	static int merged_list[SIZE]; // You get the idea with this one.
	while ((first_loc <= mid) && (second_loc <= high)) {
		if (values[first_loc] <= values[second_loc])
			merged_list[merged_loc++] = values[first_loc++];
		else merged_list[merged_loc++] = values[second_loc++];
	}

	// One half is empty, one still has stuff in it. Find it.
	while (first_loc < mid)
		merged_list[merged_loc++] = values[first_loc];
	while (second_loc < high)
		merged_list[merged_loc++] = values[second_loc]
	//Data is now in merged_list. Copy to the merged list.
}