#include <iostream>
#include <string>
using namespace std;
int main() {

	string testing = "This is designed to test substrings in a C++ program.";

	int temp = testing.find("sign");
	cout << temp << endl;
	cout << testing.substr(temp) << endl;

	//try to print just the "sign" string from the whole string, hopefully in various different ways.
	cout << testing.substr(temp, 4) << endl;
	cout << testing.substr(temp, testing.find('n', temp) - (temp - 1)) << endl;

	return 0;
}