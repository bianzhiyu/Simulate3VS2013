/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
/*
* Aim to describe state of son fund (part fund)
*/
#pragma once
#ifndef __MSONFUNDSTATE
#define	__MSONFUNDSTATE

#include "mTime.h"
#include "mStockState.h"

/*class mSonFundState : public mStockState
* double NetValue;
*/
class mSonFundState : public mStockState
{
public:
	double NetValue;
public:
	mSonFundState(): mStockState(), NetValue(0)  {}
	mSonFundState(int ind, const mTime& ot, double p, double closingprice): 
		mStockState(ind,ot,p,closingprice),NetValue(0) {}
	mSonFundState(int ind, const mTime& ot, double p, double closingprice,double openingprice): 
		mStockState(ind,ot,p,closingprice,openingprice),NetValue(0)  {}
	mSonFundState(int ind, const mTime& ot, double p, double closingprice,double openingprice,double netvalue): 
		mStockState(ind,ot,p,closingprice,openingprice),NetValue(netvalue)  {}
	mSonFundState(const mSonFundState& mm):mStockState((mStockState)mm)
	{
		NetValue=mm.NetValue;
	}
	mSonFundState& operator=(const mSonFundState&mm)
	{
		this->mStockState::operator=((mStockState)mm);
		NetValue=mm.NetValue;
		return *this;
	}
};

#endif