#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "Primitive.h"
#include "Point.h"
#include <stack>
using namespace std;
	
class Set
{
public:
	Set();
	~Set();
	vector<Primitive *> primitives;
	vector<Point> points;
	vector<Point> hullPoints;
	ofstream ofile;
	void getPrimitives(bool fromFile = false);
	void writeOutPoints(bool toFile = false);
	void writeOutHullPoints(bool toFile = false);
	void writeOutPrimitives(bool toFile = false);
	void calcIntersections();
	void findHullPoints();
	void findConvexHullJarvis();
	double calcAreaOfTheConvexHull();
	vector<Point> intersect(const Primitive *p1, const Primitive *p2);
	static constexpr short perm(const char t1, const char t2) 
	{
		return (t1 << 8) | t2;
	}

	static Point debugPoint;
	
private:
	int orientation(Point &p, Point &q, Point &r);
	
	static Point p0;
	static int comparePoints(const void* a, const void* b);
	static int squaredDist(Point p1, Point p2);
	Point secondTop(stack<Point> &stk);	

};

