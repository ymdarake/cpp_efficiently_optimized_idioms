#include "vector.h"

struct Point {
	int x;
	int y;
};

class Shape {
public:
	virtual Point center() const = 0;
	virtual void move(Point to) = 0;

	virtual void draw() const = 0;
	virtual void rotate(int angle) = 0;

	virtual ~Shape() {}
	// ...
};

class Circle : public Shape {
public:
	Circle(Point p, int rad);

	Point center() const override
	{
		return x;
	}
	void move(Point to) override
	{
		x = to;
	}

	void draw() const override;
	void rotate(int) override {};

private:
	Point x;
	int r;
};

class Smiley : public Circle {
public:
	Smiley(Point p, int rad) : Circle(p, rad), mouth(nullptr) {}

	~Smiley()
	{
		delete mouth;
		for (auto p :eyes)
			delete p;
	}

	void move(Point to) override;
	void draw() const
	{
		Circle::draw();
		for (auto p : eyes) {
			p->draw();
		}
		mouth->draw();
	}
	void rotate(int) override;

	void add_eye(Shape* s)
	{
		eyes.push_back();
	}

	void set_mouth(Shape* s);
	virtual void wink(int i);

private:
	vector<Shape*> eyes;
	Shape* mouth;
}


void rotate_all(std::vector<Shape*>& v, int angle)
{
	for (auto p: v) {
		p->rotate(angle);
	}
};

/**
 * dynamic_cast
 *
 * if (Smiley∗ p = dynamic_cast<Smiley∗>(ps)) { // ... does ps point to a Smiley? ... // ... a Smiley; use it
 * }
 * else {
 * // ... not a Smiley (p above is nullptr), try something else ...
 * }
 *
 * class Smiley : public Circle { // ...
 * private:
 * 	vector<unique_ptr<Shape>> eyes; // usually two eyes unique_ptr<Shape> mouth;
 * };
 *
 * Now each object is owned by a unique_ptr that will delete the object when it is no longer needed, that is, when its unique_ptr goes out of scope.
For the unique_ptr version of user() to work, we need versions of draw_all() and rotate_all() that accept vector<unique_ptr<Shape>>s.
 *
 */