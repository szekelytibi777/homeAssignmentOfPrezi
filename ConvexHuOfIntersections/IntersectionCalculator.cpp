#include "IntersectionCalculator.h"
#include <limits>
#include <iostream>
using namespace std;
// used article is writen by Paul Bruke 
// http://paulbourke.net/geometry/circlesphere/
MemberType IntersectionCalculator::epsilon = 1;
// LINE-LINE INTERSECTION ------------------------------------------------------------------
// Source: https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
bool IntersectionCalculator::intersect(const Line* l1, const Line* l2, vector<Point>& result) {
	// lineSection1 parameters
	const MemberType& ax1b = l1->x0;
	const MemberType& ax1e = l1->x1;
	const MemberType& ay1b = l1->y0;
	const MemberType& ay1e = l1->y1;
	// lineSection2 parameters
	const MemberType& ax2b = l2->x0;
	const MemberType& ax2e = l2->x1;
	const MemberType& ay2b = l2->y0;
	const MemberType& ay2e = l2->y1;

	const MemberType& bx1b = l2->x0;
	const MemberType& bx1e = l2->x1;
	const MemberType& by1b = l2->y0;
	const MemberType& by1e = l2->y1;
	// lineSection2 parameters
	const MemberType& bx2b = l1->x0;
	const MemberType& bx2e = l1->x1;
	const MemberType& by2b = l1->y0;
	const MemberType& by2e = l1->y1;

	
	MemberType adenom = (ay2e - ay2b) * (ax1e - ax1b) - (ax2e - ax2b) * (ay1e - ay1b);
	MemberType ana	  = (ax2e - ax2b) * (ay1b - ay2b) - (ay2e - ay2b) * (ax1b - ax2b);
	MemberType anb	  = (ax1e - ax1b) * (ay1b - ay2b) - (ay1e - ay1b) * (ax1b - ax2b);

	MemberType bdenom = (by2e - by2b) * (bx1e - bx1b) - (bx2e - bx2b) * (by1e - by1b);
	MemberType bna	  = (bx2e - bx2b) * (by1b - by2b) - (by2e - by2b) * (bx1b - bx2b);
	MemberType bnb    = (bx1e - bx1b) * (by1b - by2b) - (by1e - by1b) * (bx1b - bx2b);

	if (adenom == 0.0) {
		// if(na == 0.0 && nb = 0.0) COINCIDENT
		// else PARALLEL
		return false;
	}

	MemberType aua = ana / adenom;
	MemberType aub = ana / adenom;
	MemberType bua = bna / bdenom;
	MemberType bub = bna / bdenom;

	if ((aua >= 0.0f && aua <= 1.0f && aub >= 0.0f && aub <= 1.0f)
		&& (bua >= 0.0f && bua <= 1.0f && bub >= 0.0f && bub <= 1.0f))
	{
		// Get the intersection point.
		MemberType x = ax1b + aua * (ax1e - ax1b);
		MemberType y = ay1b + aua * (ay1e - ay1b);
		Point ip(x, y);
		result.push_back(ip);
		return true;
	}
	return false;
}

// CIRCLE-CIRCLE INTERSECTION ----------------------------------------------------------------
bool IntersectionCalculator::intersect(const Circle *c1, const Circle *c2, vector<Point>& result) {
	MemberType dx = c2->x - c1->x;
	MemberType dy = c2->y - c1->y;
	MemberType distance = sqrt(dx*dx + dy*dy);

	if (distance > c1->r + c2->r)
		return false;
	if (distance < abs(c1->r - c2->r))
		return false;
	if (distance == 0 /*&& c1->r == c2->r*/)// circles are coincident. Mark there is no intersection 
		return false;

	MemberType a = (c1->r * c1->r - c2->r * c2->r + distance * distance) / (2 * distance);
	MemberType xc = c1->x + (dx * a / distance);
	MemberType yc = c1->y + (dy * a / distance);
	MemberType h = sqrt(c1->r*c1->r - a*a);
	MemberType rx = -dy * (h / distance);
	MemberType ry = dx * (h / distance);
	Point p1((xc + rx), (yc + ry));
	Point p2((xc - rx), (yc - ry));


	result.push_back(p1);
	if (!(rx == 0 && ry == 0))
		result.push_back(p2);
	return true;
}
// LINE-CIRCLE INTERSECTION ----------------------------------------------------------------
bool IntersectionCalculator::intersect(const Line *l, const Circle *c, vector<Point>& result) {
	
	MemberType dx = l->x1 - l->x0;
	MemberType dy = l->y1 - l->y0;

	MemberType a = dx * dx + dy*dy;	
	MemberType b = 2 * (dx * (l->x0 - c->x) + dy * (l->y0 - c->y));
	MemberType _c = c->x * c->x + c->y * c->y;

	_c += l->x0*l->x0 + l->y0*l->y0;
	_c -= 2 * (c->x*l->x0 + c->y*l->y0);
	_c -= c->r*c->r;

	MemberType bb4ac = b * b - 4 * a * _c;
	if (abs(a) < EPS || bb4ac < 0) {
		return(false);
	}
	MemberType m1 = (-b + sqrt(bb4ac)) / (2 * a);
	MemberType m2 = (-b - sqrt(bb4ac)) / (2 * a);

	if (m1 >= 0 && m1 <= 1) {
		Point pi(l->x0 + m1 * (l->x1 - l->x0), l->y0 + m1 * (l->y1 - l->y0));
		result.push_back(pi);
	}
	if ( m2 >= 0 && m2 <= 1) {
		Point pi(l->x0 + m2 * (l->x1 - l->x0), l->y0 + m2 * (l->y1 - l->y0));
		result.push_back(pi);
	}

	return true;
}

bool IntersectionCalculator::test() {
	return true;
	vector<Point> result;
	Line l1(5, 0, 5, 10);
	Line l2(0, 5, 10, 5);
	Circle c1(5, 5, 3);
	Circle c2(3, 5, 3);
	Circle c3(-1, 5, 5);
	// -------------------- Line-Line --------------------------
	intersect(&l1, &l2, result);
	if (result.size() != 1) {
		cout << "Something wrong with Line-Line intersection. (1)\n";
		return false;
	}
	
	Point& p = result[0];
	if (!(p.getX() == 5 && p.getY() == 5)) {
		cout << "Something wrong with Line-Line intersection. (2)\n";
		return false;
	}
	result.clear();
	// -------------------- Circle-Circle --------------------------
	intersect(&c1, &c2, result);
	if (result.size() != 2) {
		cout << "Something wrong with Circle-Circle intersection. (1)\n";
		return false;
	}
	Point& p0 = result[0];
	Point& p1 = result[1];
	if(!(p0.getX() == 4 && p1.getX() == 4 && p0.getY() == 2 && p1.getY() == 7)) {
		cout << "Something wrong with Circle-Circle intersection. (2)\n";
		return false;
	}
	result.clear();
	// -------------------- Line-Circle --------------------------
	intersect(&l2, &c1, result);
	if (result.size() != 2) {
		cout << "Something wrong with Line-Circle intersection. (1)\n";
		return false;
	}
	p0 = result[0];
	p1 = result[1];
	if (!(p0.getX() == 8 && p1.getX() == 2 && p0.getY() == 5 && p1.getY() == 5)) {
		cout << "Something wrong with Line-Circle intersection. (2)\n";
		return false;
	}
	result.clear();
	return true;
}
