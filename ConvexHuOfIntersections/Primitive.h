#pragma once
#include <string>
typedef double MemberType;
class Primitive
{
public:
	char t = 'P';
	virtual std::string toString() = 0;
};

