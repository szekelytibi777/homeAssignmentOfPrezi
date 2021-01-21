#pragma once
#include "Primitive.h"
using namespace std;
class Circle: public Primitive
{
public:
	MemberType x, y, r;
	Circle(long _x = 0, long _y = 0, long _r = 0)
	: x((MemberType)_x)
	, y((MemberType)_y)
	, r((MemberType)_r) 
	{
		t = 'C';
	}

	string toString() {
		string res = "C " + to_string((long)x) + " " + to_string((long)y) + " " + to_string((long)r) + "\n";
		return res;
	}
};

