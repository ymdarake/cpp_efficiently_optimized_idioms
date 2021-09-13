#include "vector.h"
#include <stdexcept>


Vector::Vector(int s)
	:elem(new double[s]), sz(s)
{
	if (s < 0)
		throw std::length_error("Vector constructor: negative size");
}

double& Vector::operator[](int i)
{
	return elem[i];
}

int Vector::size()
{
	return sz;
}
