#include <iostream>
#include "vector.h"// not completed so this file doesn't compile

using namespace std;

void f(const Vector<int>& vec, const list<string>& lst, int x, const string& s)
{
	cout << "number of values less than " << x
	<< ": " << count(vec,[&](int a){ return a<x; })
	<< '\n';
	cout << "number of values less than " << s
	<< ": " << count(lst,[&](const string& a){ return a<s; })
	<< '\n';
}

/*
The notation [&](int a){ return a<x; } is called a lambda expression.
It generates a function object exactly like Less_than<int>{x}.
The [&] is a capture list specifying that all local names used in the lambda body (such as x)
will be accessed through references.
Had we wanted to ‘‘capture’’ only x, we could have said so: [&x].
Had we wanted to give the generated object a copy of x, we could have said so: [=x].
Capture nothing is [ ],
capture all local names used by reference is [&],
and capture all local names used by value is [=].
*/
