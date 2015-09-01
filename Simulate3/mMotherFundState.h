/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
/* Mother Fund : fund of funds
* Aim to describe state of FoFs, including estimated netvalue
*/
#pragma once
#ifndef __MMOTHERFUNDSTATE
#define __MMOTHERFUNDSTATE

#include "mTime.h"
#include "mStockState.h"

/*class mMotherFundState: public mStockState, double EstimatedNetValue,investPct;
*/
class mMotherFundState: public mStockState
{
public:
	double EstimatedNetValue,investPct;
public:
	mMotherFundState():  EstimatedNetValue(0),investPct(0.95)  {}
	mMotherFundState(int ind, const mTime& ot, double p, double closingprice): 
		mStockState(ind,ot,p,closingprice), EstimatedNetValue(0),investPct(0.95)  {}

	mMotherFundState(int ind, const mTime& ot, double p, double closingprice,double openingprice): 
		mStockState(ind,ot,p,closingprice,openingprice), EstimatedNetValue(0),investPct(0.95)   {}

	mMotherFundState(int ind, const mTime& ot, double p, double closingprice,double openingprice,double investpct): 
		mStockState(ind,ot,p,closingprice,openingprice), EstimatedNetValue(0),investPct(investpct)   {}

	mMotherFundState(const mMotherFundState& mm): mStockState((mStockState)(mm))
	{
		EstimatedNetValue=mm.EstimatedNetValue;
		investPct=mm.investPct;
	}
	mMotherFundState& operator =(const mMotherFundState& mm)
	{
		this->mStockState::operator=((mStockState)mm);
		EstimatedNetValue=mm.EstimatedNetValue;
		investPct=mm.investPct;
		return (*this);
	}

	void setinvestPct(double d){investPct=d;}
	double getinvestPct() const {return investPct;}

	void setEstimatedNetValue(double d) {EstimatedNetValue=d;}
	double estimateNetValue(double ContempIndexPrice,double ClosingIndexPrice);
	//closing price is at the last day, contemp price is at today
	double getEstimatedNetValue() const {return EstimatedNetValue;}

	double getClosingNetValue()  const {return ClosingPrice;}
	void  setClosingNetValue(double d) {ClosingPrice=d;}
};

#endif