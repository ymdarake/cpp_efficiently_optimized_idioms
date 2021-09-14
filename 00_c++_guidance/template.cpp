/**
 * Template argument deduction
 */
template<typename T>
class Vector2 {
public:
	using value_type = T;
// ...
	Vector2(initializer_list<T>);// initializer-list constructor

	//range constructor
	template<typename Iter>
	Vector2(Iter, Iter) −> Vector2<typename Iter::value_type>;// deduction guide
// ...
};

Vector2 v1 {1,2,3,4,5};
Vector2 v2(v1.begin(),v1.begin()+2);
