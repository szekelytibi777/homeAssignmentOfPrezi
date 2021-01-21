#pragma once
#include "Primitive.h"
#include <iomanip>
#include <sstream>
using namespace std;
class Point
{
public:
	Point(long _x=0, long _y=0) : x((MemberType)_x), y((MemberType)_y) {}
	Point(MemberType _x = 0, MemberType _y = 0) : x(_x), y(_y) {}
	MemberType x, y;

	long getX() {
		return (long)x;
	}

	long getY() {
		return (long)y;
	}

	std::string toString() {
		std::stringstream ss;
		ss << fixed << setprecision(4) << x << " " << y << "\n";
		return ss.str();
	}
};

inline bool operator==(const Point& p1, const Point& p2) {
	MemberType epsilon = .001;
	if (abs(p2.x - p1.x) < epsilon && abs(p2.y - p1.y) < epsilon)
		return true;
	else
		return false;
}