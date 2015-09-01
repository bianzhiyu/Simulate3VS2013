/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#pragma once
#ifndef __mObjectCategory
#define __mObjectCategory

class mObjectCategory
{
public:
	static const int Stock=0;
	static const int Index=1;
	static const int ETF=2;
	static const int StructuredFund=3; //A+B+M
	static const int PartA=4;
	static const int PartB=5;
	static const int MotherFund = 6;
private:
	int ObjectCategory;
public:
	mObjectCategory():ObjectCategory(0) {}
	mObjectCategory(const mObjectCategory& mm){ObjectCategory=mm.ObjectCategory;}
	mObjectCategory(int d):ObjectCategory(d) {}
	operator int() const {return ObjectCategory;}
	mObjectCategory& operator = (int i) {ObjectCategory=i; return *this;}
	mObjectCategory& operator = (mObjectCategory i) {ObjectCategory=i.ObjectCategory; return *this;}
	bool operator == (int d) const {return (ObjectCategory==d);}
	bool operator != (int d) const {return (ObjectCategory!=d);}
	friend bool operator == (int,const mObjectCategory&);
	friend bool operator != (int, const mObjectCategory&);
};

bool operator == (int,const mObjectCategory&);
bool operator != (int,const mObjectCategory&);

#endif