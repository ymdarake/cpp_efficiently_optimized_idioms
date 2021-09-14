class Vector {
public:
	Vector(int s);
	Vector(const Vector& a); // copy constructor
	Vector& operator=(const Vector& a); // copy assignment
	Vector(Vector&& a); // move constructor
	Vector& operator=(Vector&& a); // move assignment
	double& operator[](int i);
	int size();
private:
	double* elem;// elem points to an array of sz doubles
	int sz;
};

/*
The && means "rvalue reference" and is a reference to which we can bind an rvalue.
The word "rvalue" is intended to complement "lvalue," which roughly means "something that can appear on the left-hand side of an assignment."
So an rvalue is – to a first approximation – a value that you can’t assign to,
such as an integer returned by a function call.
Thus, an rvalue reference is a reference to something that nobody else can assign to,
so we can safely "steal" its value. The res local variable in operator+() for Vectors is an example.

A move constructor does not take a const argument: after all,
a move constructor is supposed to remove the value from its argument.
A move assignment is defined similarly.

A move operation is applied when an rvalue reference is
used as an initializer or as the right- hand side of an assignment.
After a move, a moved-from object should be in a state that allows a destructor to be run.

Typically, we also allow assignment to a moved-from object.
The standard-library algorithms (Chapter 12) assumes that.
Our Vector does that.

Where the programmer knows that a value will not be used again,
but the compiler can’t be expected to be smart enough to figure that out,
the programmer can be specific:
*/
Vector f() {
	Vector x(1000);
	Vector y(2000);
	Vector z(3000);
	z = x;						// we get a copy (x might be used later in f())
	y = std::move(x); // we get a move (move assignment)
	// ... better not use x here ...
	return z;					// we get a move
}

/*
The standard-library function move() doesn’t actually move anything.
Instead, it returns a reference to its argument from which we may move – an rvalue reference;
it is a kind of cast
When we return from f(), z is destroyed after its elements has been moved out of f() by the return.
However, y’s destructor will delete[] its elements.
*/
