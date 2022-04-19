#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdarg>
using namespace std;

// Author: Lucas Vas

void write(string userInput ...);
//void writeTest(string userInput, int count ...);

int main() {
	// Biggest concern with this is that the va_list requires a size.

	// These should both show the same values.
	/*writeTest("Example {0:i}: I want to print the number {1:e}. Extra number {2}...", 3, 12.8, 32.0, 300.0045);*/
	write("Example {0:i}: I want to print the number {1:e}. Extra number {2}... this is currency: {3:c}", 12.8, 32.0, 300.0045, 4.0);
	return 0;
}

void write(string userInput ...) {
	string format_tag;

	// Get number of values
	int size = 0;
	for (int i = 0; i < userInput.size(); i++) {
		if (userInput[i] == '{') size++;
	}

	// Put all extra values into a vector list
	vector<double> inputList(size);
	double testing = 0;
	va_list inputs;
	va_start(inputs, userInput);
	for (auto& arg : inputList) { // cannot use automatic typing, unfortunately.
		arg = va_arg(inputs, double);
		//cout << arg << endl; // Debug
	}
	cout << '\n';
	va_end(inputs); // Return va_list to the memory, before i forget.

	// Print the string character by character, except for the {} tags.
	int index;
	for (int i = 0; i < userInput.length(); i++) {

		// Anything within the braces.
		if (userInput[i] == '{') {
			format_tag = userInput.substr(i, userInput.find('}', i) - (i - 1)); // Disregarded warning because string will always return within these two values, no side effects.

			// Replace format key in original string with a blank space.
			userInput.replace(userInput.find(format_tag), format_tag.length() - 1, "");

			// Check for list index and formatting style.
			// Store the index of the number expected, and the number to print. For the syntax to work this must be a number.
			index = (int)format_tag[1] - 48; // would convert into ASCII
			double toPrint = inputList[index];

			switch (format_tag[3]) {
			case 'c': // currency
				cout << "$" << std::fixed << setprecision(2) << inputList[index];
				break;
			case 'e': // scientific notation
				cout << std::scientific << toPrint;
				break;
			case 'f': // default decimal places
				cout << std::fixed << toPrint;
				break;
			case 'i': // round to int
				cout << (int)toPrint;
				break;
			default: // only if none of these match (would most likely be a closed brace)
				cout.unsetf(cout.flags()); // unset all flags that are currently in place.
				cout << toPrint;
				break;
			}
		}
		// Every character except for the tags
		else cout << userInput[i];
	}
}