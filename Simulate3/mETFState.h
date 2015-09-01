/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#pragma once
#ifndef __METFSTATE
#define __METFSTATE

#include "mTime.h"
#include "mStockState.h"

/*class mETFState: public mStockState
*/
class mETFState: public mStockState
{
public:
	mETFState()  {}
	mETFState(int ind, const mTime& ot, double p, double closingprice): mStockState(ind,ot,p,closingprice) {}
	mETFState(int ind, const mTime& ot, double p, double closingprice,double openingprice): mStockState(ind,ot,p,closingprice,openingprice)  {}
	mETFState(const mETFState& mm): mStockState(mm) {}
	mETFState& operator = (const mETFState& mm)
	{
		this->mStockState::operator=(mm);
		return *this;
	}
};

#endif