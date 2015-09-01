/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#pragma once
#ifndef __mOperationCategory
#define __mOperationCategory

class mOperationCategory
{
public:
	static const int StartCode=0;
	static const int EndCode=15;

	static const int buyPartA=0;	//llint,positive
	static const int sellPartA=1;	//llint,positive
	static const int buyPartB=2;	//llint,positive
	static const int sellPartB=3;	//llint,positive

	///4-7 may be deserted
	static const int buyMotherFund=4;	//optnum : +
	static const int redeemMotherFund=5;	//optnum : +
	static const int splitMotherFund=6;	//optnum : +
	static const int combinePartAB=7;	//optnum : +

	static const int buyMotherFundInOpenMarket = 8;		//double : real reaction, llint: expected share ; positive
	static const int buyMotherFundInClosingMarket=9;	//double , positive
	//static const int cancelbuyMotherFundInOpenMarket = 16; //ddouble : real reaction, llint: expected share ; positive
	
	static const int redeemMotherFundInOpenMarket=10;	//llint,positive
	static const int redeemMotherFundInClosingMarket = 11;	//llint,positive

	static const int splitMotherFundInOpenMarket=12;	//llint,positive
	static const int splitMotherFundInClosingMarket=13;	//llint,positive

	static const int combinePartABInOpenMarket=14;		//llint,positive
	static const int combinePartABInClosingMarket=15;	//llint,positive
private:
	int OperationCategory;
public:
	mOperationCategory():OperationCategory(0) {}
	mOperationCategory(int d):OperationCategory(d) {}
	mOperationCategory(const mOperationCategory& mm) {OperationCategory=mm.OperationCategory;}
	operator int () const {return OperationCategory;}
	mOperationCategory& operator = (mOperationCategory i) {OperationCategory=i.OperationCategory; return *this;}
	mOperationCategory& operator = (int i) {OperationCategory=i; return *this;}
	bool operator == (int d) const {return (OperationCategory==d);}
	bool operator != (int d) const {return (OperationCategory!=d);}

	friend bool operator ==(int , const mOperationCategory&);
	friend bool operator !=(int , const mOperationCategory&);
};

bool operator ==(int , const mOperationCategory&);
bool operator !=(int , const mOperationCategory&);


#endif