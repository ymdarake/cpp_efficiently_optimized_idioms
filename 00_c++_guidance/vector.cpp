#include "vector.h"
#include <stdexcept>


Vector::Vector(int s)
	:elem(new double[s]), sz(s)
{
	if (s < 0)
		throw std::length_error("Vector constructor: negative size");
}

Vector::Vector(Vector&& a)
	:elem(a.elem), // "grab the elements" from a
	sz(a.sz)
{
	a.elem = nullptr; // now a has no elements
	a.sz = 0;
}

double& Vector::operator[](int i)
{
	return elem[i];
}

int Vector::size()
{
	return sz;
}
