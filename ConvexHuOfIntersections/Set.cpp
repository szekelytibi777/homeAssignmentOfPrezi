#include "Set.h"
#include "Line.h"
#include "Circle.h"
#include "Point.h"
#include "IntersectionCalculator.h"
#include <algorithm>
#include <list>

using namespace std;

Point Set::debugPoint(4.9512, -0.6971);

Set::Set(){
	ofile.open("output.dat");
}

Set::~Set() {
	for (int i = 0; i < primitives.size(); i++) {
		delete primitives[i];
	}
	ofile.close();
}

void Set::getPrimitives(bool fromFile) {
	ifstream infile;
	int numPrimitives;
//	infile.open("stressTest.dat");
	infile.open("test.dat");
	if (fromFile) {
		infile >> numPrimitives;
		for (int i = 0; i < numPrimitives; i++) {
			char pType;
			infile >> pType;
			if (pType == 'L') {
				long x0, y0, x1, y1;
				infile >> x0;
				infile >> y0;
				infile >> x1;
				infile >> y1;
				Line* l = new Line(x0, y0, x1, y1);
				primitives.push_back(l);
			}
			else if (pType == 'C') {
				long x, y, r;
				infile >> x;
				infile >> y;
				infile >> r;
				Circle* c = new Circle(x, y, r);
				primitives.push_back(c);
			}
		}
		infile.close();
	}
	else {

		cin >> numPrimitives;
		for (int i = 0; i < numPrimitives; i++) {
			char pType;
			cin >> pType;
			if (pType == 'L') {
				
				long x0, y0, x1, y1;
				cin >> x0;
				cin >> y0;
				cin >> x1;
				cin >> y1;
				Line *l = new Line(x0, y0, x1, y1);
				primitives.push_back(l);
			}
			else if (pType == 'C') {
				long x, y, r;
				cin >> x;
				cin >> y;
				cin >> r;
				Circle *c = new Circle(x, y, r);
				primitives.push_back(c);
			}
		}
	}
	points.reserve(size_t(numPrimitives) * size_t(numPrimitives) * 2); // my guess
} 

void Set::writeOutPrimitives(bool toFile) {
	if (toFile)
		ofile << primitives.size() << endl;
	cout << primitives.size() << endl;
	for (int i = 0; i < primitives.size(); i++) {
		cout << primitives[i]->toString();
		if (toFile)
			ofile << primitives[i]->toString();
	}
	
}

void Set::writeOutPoints(bool toFile) {
	if (toFile)
		ofile << points.size() << endl;
	cout << points.size() << endl;
	for (int i = 0; i < points.size(); i++) {
		if(toFile)
			ofile << points[i].toString();
		cout << points[i].toString();
	}
}

void Set::writeOutHullPoints(bool toFile) {
	if (toFile) {
		ofile << hullPoints.size() << endl;
		ofile << "yellow" << endl;
	}
	cout << hullPoints.size() << endl;
	for (int i = 0; i < hullPoints.size(); i++) {
		if (toFile)
			ofile << hullPoints[i].toString();
		cout << hullPoints[i].toString();
	}
}

void Set::calcIntersections() {
	points.clear();
	for (int i = 0; i < primitives.size(); i++) {
		for (int j = i; j < primitives.size(); j++) {
			if (i != j) {
				Primitive *p1 = primitives[i];
				Primitive *p2 = primitives[j];
				if (p1 != p2) {
					vector<Point> is = intersect(p1, p2);
					points.insert(points.end(), is.begin(), is.end());
				}
			}
		}
	}
}

vector<Point> Set::intersect(const Primitive *p1, const Primitive *p2) {
	vector<Point> pv;
	short p = perm(p1->t, p2->t);
	
	switch (p) {
		case perm('L', 'L'):
			// Line - Line intersection
			IntersectionCalculator::intersect((Line*)p1, (Line*)p2, pv);
			break;
		case perm('L', 'C'):
			// Line - Circle intersection
			IntersectionCalculator::intersect((Line*)p1, (Circle*)p2, pv);
			break;
		case perm('C', 'L'):
			// Line - Circle intersection
				IntersectionCalculator::intersect((Line*)p2, (Circle*)p1, pv);
			break;
		case perm('C', 'C'):
			// Circle - Circle intersection
			IntersectionCalculator::intersect((Circle*)p1, (Circle*)p2, pv);
			break;
	}
	return pv;
}

Point Set::secondTop(stack<Point>& stk) {
	Point tempPoint = stk.top();
	stk.pop();
	Point res = stk.top();    //get the second top element
	stk.push(tempPoint);      //push previous top again
	return res;
}
	
int direction(Point a, Point b, Point c) {
	MemberType val = (b.y - a.y) * (c.x - b.x) - (b.x - a.y) * (c.y - b.y);
	if (val == 0)
		return 0;    //colinear
	else if (val < 0)
		return 2;    //anti-clockwise direction
	return 1;    //clockwise direction
}

int Set::squaredDist(Point p1, Point p2) {
	MemberType s = ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	return (int)s;
}

Point Set::p0(long(0), long(0)	);

int Set::comparePoints(const void* a, const void* b) {
	Point* p1 = (Point*)a;
	Point* p2 = (Point*)b;
	int dir = direction(Set::p0, *p1, *p2);
	if (dir == 0)
		return (squaredDist(p0, *p2) >= squaredDist(p0, *p1)) ? -1 : 1;
	return (dir == 2) ? -1 : 1;
}
// Graham Scan Algorithm to Find the Convex Hull
// source: https://www.tutorialspoint.com/cplusplus-program-to-implement-graham-scan-algorithm-to-find-the-convex-hull
void Set::findHullPoints() {
	if (points.size() < 2)
		return;
	hullPoints.clear();

	MemberType minY = points[0].y;
	int min = 0;
	for (int i = 1; i < points.size(); i++) {
				MemberType y = points[i].y;
		if (y <= minY){
			if (points[i].x < points[min].x) {
				minY = points[i].y;
				min = i;
			}
		}
	}
	Point temp = points[0];          // SWAP
	points[0] = points[min];
	points[min] = temp;
	p0 = points[0];
		std::qsort(&points[1], points.size() - 1, sizeof(Point), Set::comparePoints);
	size_t arrSize = 1;
	for (size_t i = 1; i < points.size(); i++) {
	//	if (points[i] == debugPoint || points[i+1] == debugPoint)
	//		cout << "!!!! \n";
		while (i < points.size()-1 && direction(p0, points[i], points[i + 1]) == 0)
			i++;
		
		points[arrSize] = points[i];
		arrSize++;
	}
	if (arrSize < 3)
		return;
	stack<Point> stk;
	//if (points[0] == debugPoint || points[1] == debugPoint || points[0] == debugPoint)
	//	cout << "!!!!!\n";
	stk.push(points[0]);
	stk.push(points[1]);
	stk.push(points[2]);
	for (int i = 3; i < arrSize; i++) {
		while (direction(secondTop(stk), stk.top(), points[i]) != 2)
			stk.pop();
		stk.push(points[i]);
	}
	while (!stk.empty()) {
 		hullPoints.push_back(stk.top());    //add points from stack
		stk.pop();
	}
}
// Convex Hull | Set 1 (Jarvis’s Algorithm or Wrapping)
// source: https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
void Set::findConvexHullJarvis() {
	int n = points.size();
	if (n < 3)
		return;
	hullPoints.clear();
	// Find the leftmost point 
	int l = 0;
	for (int i = 1; i < n; i++)
		if (points[i].x < points[l].x)
			l = i;
	// Start from leftmost point, keep moving counterclockwise until reach the start point again.  
	// This loop runs O(h) times where h is number of points in result or output. 
	int p = l, q;
	do
	{
		// Add current point to result 
		hullPoints.push_back(points[p]);

		// Search for a point 'q' such that orientation(p, x, q) is counterclockwise for all points 'x'. 
		// The idea is to keep track of last visited most counterclock-wise point in q. If any point 'i' is more counterclock-wise than q, then update q. 
		q = (p + 1) % n;

		for (int i = 0; i < n; i++)
		{
			// If i is more counterclockwise than current q, then update q 
			if (orientation(points[p], points[i], points[q]) == 2)
				q = i;
		}

		// Now q is the most counterclockwise with respect to p. Set p as q for next iteration,  so that q is added to result 'hull' 
		p = q;
	} while (p != l); // While we don't come to first point
}

int Set::orientation(Point& p, Point &q, Point &r) {
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;		// colinear 
	return (val > 0) ? 1 : 2;	// clock or counterclock wi
}

double Set::calcAreaOfTheConvexHull() {
	double area = 0;
	int j = hullPoints.size() - 1;
	for (int i = 0; i < hullPoints.size(); i++) {
		const Point &pi = hullPoints[i];
		const Point& pj = hullPoints[j];
		area += (pj.x + pi.x) * (pj.y - pi.y);
		j = i;
	}
	double res = abs(area / 2.0);
	cout << res;
	ofile << res << endl;
	return area;
}