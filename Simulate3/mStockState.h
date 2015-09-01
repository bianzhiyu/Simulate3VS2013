/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
/*
* aim to describe state of stocks and indexs
*/
#pragma once
#ifndef __MSTOCKSTATE
#define __MSTOCKSTATE

#include "mTime.h"
#include "mObjectCategory.h"

class mStockState
{
public:
	int Index;
	mTime Time;
	double Price, PreClosingPrice, ClosingPrice, OpeningPrice;
public:
	mStockState() : Index(0), Time(), Price(0), ClosingPrice(0), OpeningPrice(0), PreClosingPrice(0){}
	mStockState(int ind, const mTime& ot, double p, double closingprice): 
		Index(ind), Time(ot), Price(p),ClosingPrice(closingprice)  {}
	mStockState(int ind, const mTime& ot, double p, double closingprice,double openingprice): 
		Index(ind), Time(ot), Price(p),ClosingPrice(closingprice),OpeningPrice(openingprice)  {}
	mStockState(int ind, const mTime& ot, double p, double preclosingprice, double closingprice, double openingprice) :
		Index(ind), Time(ot), Price(p), PreClosingPrice(preclosingprice), ClosingPrice(closingprice), OpeningPrice(openingprice)  {}

	mStockState(const mStockState& mm)
	{
		Index = mm.Index;
		Time = mm.Time;
		Price = mm.Price;
		ClosingPrice = mm.ClosingPrice;
		OpeningPrice = mm.OpeningPrice;
		PreClosingPrice = mm.PreClosingPrice;
	}
	mStockState& operator =(const mStockState& mm)
	{
		Index = mm.Index;
		Time = mm.Time;
		Price = mm.Price;
		ClosingPrice = mm.ClosingPrice;
		OpeningPrice = mm.OpeningPrice;
		PreClosingPrice = mm.PreClosingPrice;
		return *this;
	}

	double getPrice() const {return Price;}
	void setPrice(double d) {Price=d;}

	double getClosingPrice() const {return ClosingPrice;}
	void setClosingPrice(double d) {ClosingPrice=d;}

	double getPreClosingPrice() const { return PreClosingPrice; }
	void setPreClosingPrice(double d)	{ PreClosingPrice = d; }

	double getOpeningPrice() const {return OpeningPrice;}
	void setOpeningPrice(double d) {OpeningPrice=d;}

	void setTime(const mTime& ot) {Time=ot;}
	mTime getTime() const {return Time;}

	void setIndex(int i)  {Index=i;}
	int getIndex()  const {return Index;}

	void setAll(int ind, const mTime& ot, double p, double closingprice)
	{ Index=ind; Time=ot; Price=p; ClosingPrice=closingprice;}
	void setAll(int ind, const mTime& ot, double p, double closingprice,double openingprice)
	{Index=ind; Time=ot; Price=p; ClosingPrice=closingprice;OpeningPrice=openingprice;}
	void setAll(int ind, const mTime& ot, double p, double preclosingprice, double closingprice, double openingprice)
	{
		Index = ind; Time = ot; Price = p; PreClosingPrice = preclosingprice;
		ClosingPrice = closingprice; OpeningPrice = openingprice;
	}

	void setTimeNPrice (const mTime& ot,double p)
	{ Time=ot; Price=p;};
};

#endif