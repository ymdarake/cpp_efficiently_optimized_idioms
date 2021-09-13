#include "vector.h"
#include <iostream>

using namespace std;


void f(Vector& v)
{
	try {
		v[v.size()] = 7;
	} catch (out_of_range& err) {
		cerr << err.what() << '\n';
	}
}