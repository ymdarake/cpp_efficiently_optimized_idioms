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

// The && means "rvalue reference" and is a reference to which we can bind an rvalue. The word "rvalue" is intended to complement "lvalue," which roughly means "something that can appear on the left-hand side of an assignment." So an rvalue is – to a first approximation – a value that you can’t assign to, such as an integer returned by a function call. Thus, an rvalue reference is a reference to something that nobody else can assign to, so we can safely "steal" its value. The res local variable in operator+() for Vectors is an example.
// A move constructor does not take a const argument: after all, a move constructor is supposed to remove the value from its argument. A move assignment is defined similarly.
