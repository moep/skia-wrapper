#include <iostream>
using namespace std;

#include "test.h"

int main() {
	cout << "main" << endl;
	EineKlasse *k = new EineKlasse(42);
	int i = k->eineFunktion(11);
	cout << "i: " << 11 << endl;
	delete k;
}
