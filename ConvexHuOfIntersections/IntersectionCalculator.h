#pragma once
#include "Line.h"
#include "Circle.h"
#include "Point.h"
#include <vector> 
#include <limits>
using namespace std;
class IntersectionCalculator
{
public:
	static MemberType epsilon;
	static bool intersect(const Line *l1, const Line *l2, vector<Point> &result);
	static bool intersect(const Circle *c1, const Circle *c2, vector<Point>& result);
	static bool intersect(const Line *l, const Circle *c, vector<Point>& result);
	static bool test();
};

#define EPS IntersectionCalculator::epsilon

