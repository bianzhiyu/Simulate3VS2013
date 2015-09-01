/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#pragma once
#ifndef __MSTOCKSTREAMLISTENER
#define __MSTOCKSTREAMLISTENER

#include "mStockState.h"
#include "mSonFundState.h"
#include "mMotherFundState.h"

/*mStockState InitialIndexState,ContempIndexState;
*mSonFundState InitialSFundAState,ContempSFundAState,InitialSFundBState,ContempSFundBState;
*mMotherFundState MFundState;
*/
class StockStreamListener
{
public:
	mStockState InitialIndexState,ContempIndexState;
	mSonFundState InitialSFundAState,ContempSFundAState,InitialSFundBState,ContempSFundBState;
	mMotherFundState MFundState;
public:
	StockStreamListener() {}
	StockStreamListener(const StockStreamListener& mm)
	{
		InitialIndexState=mm.InitialIndexState;ContempIndexState=mm.ContempIndexState;
		InitialSFundAState=mm.InitialSFundAState;ContempSFundAState=mm.ContempSFundAState;
		InitialSFundBState=mm.InitialSFundBState;ContempSFundBState=mm.ContempSFundBState;
		MFundState=mm.MFundState;
	}
	StockStreamListener& operator=(const StockStreamListener& mm)
	{
		InitialIndexState=mm.InitialIndexState;ContempIndexState=mm.ContempIndexState;
		InitialSFundAState=mm.InitialSFundAState;ContempSFundAState=mm.ContempSFundAState;
		InitialSFundBState=mm.InitialSFundBState;ContempSFundBState=mm.ContempSFundBState;
		MFundState=mm.MFundState;
		return *this;
	}

	double getInstantPremiumRate();	//use : MFundState , ContempIndexState, ContempSFundAState, ContempSFundBState

	void setInitialIndexState(const mStockState& state){InitialIndexState=state;}
	void setContempIndexState(const mStockState& state){ContempIndexState=state;}

	void setInitialSFundAState(const mSonFundState& state){InitialSFundAState=state;}
	void setContempSFundAState(const mSonFundState& state){ContempSFundAState=state;}

	void setInitialSFundBState(const mSonFundState& state){InitialSFundBState=state;}
	void setContempSFundBState(const mSonFundState& state){ContempSFundBState=state;}

	void setMFundState(const mMotherFundState& state){MFundState=state;}

	mStockState getInitialIndexState(){return InitialIndexState;}
	mStockState getContempIndexState(){return ContempIndexState;}

	mSonFundState getInitialSFundAState() const {return InitialSFundAState;}
	mSonFundState getContempSFundAState() const {return ContempSFundAState;}

	mSonFundState getInitialSFundBState() const {return InitialSFundBState;}
	mSonFundState getContempSFundBState() const {return ContempSFundBState;}

	mMotherFundState getMFundState() const {return MFundState;}

	double getContempPriceA() const {return ContempSFundAState.getPrice();}
	double getContempPriceB() const {return ContempSFundBState.getPrice();}
	double getContempIndexPrice() const { return ContempIndexState.getPrice();}
	double getInitialIndexPrice() const { return InitialIndexState.getPrice();}
};

#endif