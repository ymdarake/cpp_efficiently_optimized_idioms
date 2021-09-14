template<typename T> void update(T& target)
{
	if constexpr(is_pod<T>::value)
		simple_and_fast(target); // for "plain old data"
	else
		slow_and_safe(target);
}
// The is_pod<T> is a type trait (§13.9.1) that tells us whether a type can be trivially copied.
