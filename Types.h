#include <vector>
#include <algorithm>

#pragma once

struct dot{
private:
	double x;
	double y;
public:
	dot() {
		x = 0;
		y = 0;
	}
	dot(double ax, double ay) {
		x = ax;
		y = ay;
	}
	double poll_x() {
		return x;
	}
	double poll_y() {
		return y;
	}
	void set_x(double ax) {
		x = ax;
	}

	void set_x(dot d) {
		x=(d).poll_x();
	}
	void set_y(double ay) {
		y = ay;
	}
	void set_y(dot d) {
		y=(d).poll_y();
	}

	void set(dot d) {
		x=(d).poll_x();
		y=(d).poll_y();
	}

	void setup(double rad, double deg) {
		x = rad * cos(deg);
		y = rad * sin(deg);
	}
	void cal() {
		return;
	}
	dot operator-(dot const& obj)
	{
		dot res;
		res.x = x - obj.x;
		res.y = y - obj.y;
		return res;
	}
	dot operator+(dot const& obj)
	{
		dot res;
		res.x = x + obj.x;
		res.y = y + obj.y;
		return res;
	}
	dot operator*(double const& obj)
	{
		dot res;
		res.x = x * obj;
		res.y = y * obj;
		return res;
	}
};

struct Vec2{
	Vec2() {
		leftDot = new dot();
		rightDot = new dot();
	}
	~Vec2() {
		// delete leftDot;
		// delete rightDot;
	}
	dot* leftDot;
	dot* rightDot;
};
