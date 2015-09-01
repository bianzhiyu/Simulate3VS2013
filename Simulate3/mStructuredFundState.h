/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#pragma once
#ifndef __MSTRUCTUREDFUNDSTATE
#define __MSTRUCTUREDFUNDSTATE

#include "mTime.h"
#include "mMotherFundState.h"
#include "mSonFundState.h"
#include "mStockState.h"

/*class mStructuredFundState
*public:
*	mTime Time;
*	mMotherFundState MotherFund;
*	mSonFundState PartA,PartB;
*	mStockState TrackIndex;
*/
class mStructuredFundState
{
public:
	mTime Time;
	mMotherFundState MotherFund;
	mSonFundState PartA,PartB;
	mStockState TrackIndex;
public:
	mStructuredFundState(): Time(), MotherFund(), PartA(), PartB(), TrackIndex() {}
	mStructuredFundState(const mStructuredFundState& mm)
	{
		Time=mm.Time;
		MotherFund=mm.MotherFund;
		PartA=mm.PartA;
		PartB=mm.PartB;
		TrackIndex=mm.TrackIndex;
	}
	mStructuredFundState& operator = (const mStructuredFundState& mm)
	{
		Time=mm.Time;
		MotherFund=mm.MotherFund;
		PartA=mm.PartA;
		PartB=mm.PartB;
		TrackIndex=mm.TrackIndex;
		return *this;
	}
	
	void setTime(mTime ot) { Time=ot;}
	mTime getTime() const {return Time;}

	void setMotherFund(const mMotherFundState& mf)  {MotherFund=mf;}
	void setPartA(const mSonFundState& sf) {PartA=sf;}
	void setPartB(const mSonFundState& sf) {PartB=sf;}
	void setTrackIndex(const mStockState& ti) {TrackIndex=ti;}

	mMotherFundState getMotherFund() const {return MotherFund;}
	mSonFundState getPartA() const { return PartA;}
	mSonFundState getPartB() const { return PartB;}
	mStockState getTrackIndex() const {return TrackIndex;}

	int getIndexA() const {return PartA.getIndex();}
	int getIndexB() const {return PartB.getIndex();}
	int getIndexM() const {return MotherFund.getIndex();}

	double gerPriceA() const {return PartA.getPrice();}
	double getPriceB() const {return PartB.getPrice();}
	double getPriceOfTrackIndex() const {return TrackIndex.getPrice();}
	double getClosingPriceOfMotherFund() const {return MotherFund.getClosingPrice();}

	double estimatePremiumRate();
	
	void updateClosingPriceOfMotherFund(double pr) {MotherFund.setClosingPrice(pr);}
	void setClosingPriceOfMotherFund(double pr) {MotherFund.setClosingPrice(pr);}

	void updateAllTime(const mTime& ot); 
		/* update time of : 
		*		mAsset (inheritated from mStructuredFundState)
		*		time in property :
		*			MotherFund,PartA,PartB,TrackIndex						
		* Attention: be careful with positions when update time
		* 	This function will forcibly rewrite all time
		*/

	double estimateNetValueOfMotherFund(double ContempIndexPrice, double ClosingIndexPrice)
	{
		return MotherFund.estimateNetValue(ContempIndexPrice, ClosingIndexPrice);
	}

	double getEstimatedNetValueOfMotherFund() const
	{
		return MotherFund.getEstimatedNetValue();
	}
};

#endif