#pragma once
#include "Primitive.h"

using namespace std;
class Line: public Primitive
{
public:
	MemberType x0, y0, x1, y1;
	MemberType a, b, c;
	Line(long _x0 = 0, long _y0 = 0, long _x1 = 0, long _y1 = 0)
		: x0((MemberType)_x0)
		, y0((MemberType)_y0)
		, x1((MemberType)_x1)
		, y1((MemberType)_y1)

	{
		t = 'L';
		// components of line's equation
		a = y1 - y0;
		b = x0 - x1;
		c = a * x0 + b *y0;
	}

	string toString() {
		string res = "L " + to_string((long)x0) + " " + to_string((long)y0) + " " + to_string((long)x1) + " " + to_string((long)y1) + "\n";
		return res;
	}
};

