// NumeralSystemConverter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

void Convert() {

	string table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string orig, orig_int = "", res = "";
	float orig_frac = 0;
	int old_ns, new_ns;
	unsigned __int64 decimal = 0;

	cout << "Positive numbers with/without floating point are allowed in the number systems from 2 to 36." << endl;
	cout << "Enter initial number: ";
	cin >> orig;
	cout << "Enter initial numeral system: ";
	cin >> old_ns;
	cout << "Enter new numeral system: ";
	cin >> new_ns;
	cout << endl;

	// Validate the input
	bool incorrect_input;
	incorrect_input = orig.find_first_not_of("." + table.substr(0, old_ns)) != orig.npos;
	if (old_ns > 36 || new_ns > 36 || old_ns < 2 || new_ns < 2 || incorrect_input) {
		cout << "Invalid input" << endl;
		return;
	}

	// Split the number into fractional and integer parts
	int idx = orig.find('.');
	if (idx != orig.npos) {
		string og_frac;
		orig_int = orig.substr(0, idx);
		og_frac = orig.substr(idx + 1);
		int og_frac_size = og_frac.size();
		for (int i = -1; i >= -og_frac_size; i--) {
			orig_frac += table.find(og_frac[-i - 1]) * pow(old_ns, i);
		}
		res = ".";
	}
	else {
		orig_int = orig;
	}

	// Convert integer part to decimal system
	for (int i = 0; i < orig_int.length(); i++) {
		decimal += table.find(toupper(orig_int[i])) * powl(old_ns, orig_int.length() - i - 1);
	}

	// Convert integer to target sytem
	while (decimal > 0) {
		res = table.at(decimal % new_ns) + res;
		decimal /= new_ns;
	}

	// Convert fraction part to target system with set precision
	if (orig_frac > 0) {
		float whole = 0, frac = 0;
		int precision = 3;
		for (int i = 0; i < precision; i++) {
			orig_frac *= new_ns;
			orig_frac = modf(orig_frac, &whole);
			res += table.at(whole);
		}
	}

	// Output the result
	cout << "Result: " << (res.length() > 0 ? res : "The number is too big");

}


int main()
{
	Convert();
}


