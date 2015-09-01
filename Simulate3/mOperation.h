/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 20:26
*/
/*
* describe operation
*/
#pragma once
#ifndef __MOPERATIONCLASS
#define __MOPERATIONCLASS

#include <vector>

#include "mTime.h"
#include "mAsset.h"
#include "mStockState.h"
#include "mStructuredFundState.h"
#include "mOperationCategory.h"

class mOperation
{
public:
	mTime Time;
	mOperationCategory OperationCategory;
	mObjectCategory OperatedObjectCategory;
	int OperatedObjectIndex;

	mStructuredFundState StructuredFundStateCopy;

	int OperationAmoutInt;
	double OperationAmoutDouble;
	long long int OperationAmoutLlint;
public:
	mOperation():Time(),OperationCategory(0),  OperatedObjectCategory(0),OperatedObjectIndex(0),
					StructuredFundStateCopy(),
					OperationAmoutInt(0),OperationAmoutDouble(0), OperationAmoutLlint(0)
	{}
	mOperation(const mOperation& opr)
	{
		Time=opr.Time;
		OperationCategory=opr.OperationCategory;
		OperatedObjectCategory=opr.OperatedObjectCategory;
		OperatedObjectIndex=opr.OperatedObjectIndex;
		StructuredFundStateCopy=opr.StructuredFundStateCopy;
		OperationAmoutInt=opr.OperationAmoutInt;
		OperationAmoutDouble=opr.OperationAmoutDouble;
		OperationAmoutLlint=opr.OperationAmoutLlint;
	}
	mOperation& operator = (const mOperation& opr)
	{
		Time=opr.Time;
		OperationCategory=opr.OperationCategory;
		OperatedObjectCategory=opr.OperatedObjectCategory;
		OperatedObjectIndex=opr.OperatedObjectIndex;
		StructuredFundStateCopy=opr.StructuredFundStateCopy;
		OperationAmoutInt=opr.OperationAmoutInt;
		OperationAmoutDouble=opr.OperationAmoutDouble;
		OperationAmoutLlint=opr.OperationAmoutLlint;
		return *this;
	}

private:
	mAsset buyPartA(const mAsset&) const;
	mAsset buyPartB(const mAsset&) const;
	mAsset sellPartA(const mAsset&) const;
	mAsset sellPartB(const mAsset&) const;
	//These four functions below should be deserted
	mAsset buyMotherFund(const mAsset&) const;
	mAsset redeemMotherFund(const mAsset&, int Daysdelay = 2) const;
	//the fund of redeemed MotherFund will be available after Daysdelay , assuming 2;
	mAsset splitMotherFund(const mAsset&) const;		//Real split action will be done after market is closed
	mAsset combinePartAB(const mAsset&) const;	//Real combination action will be done after market is closed
	//These four functions above should be deserted

	mAsset buyMotherFundInClosingMarket(const mAsset&) const;
	mAsset redeemMotherFundInClosingMarket(const mAsset&, int Daysdelay = 2) const;
	mAsset buyMotherFundInOpenMarket(const mAsset&) const;
	mAsset redeemMotherFundInOpenMarket(const mAsset&, int Daysdelay = 2) const;
	mAsset splitMotherFundInOpenMarket(const mAsset&) const;
	mAsset splitMotherFundInClosingMarket(const mAsset&) const;
	mAsset combinePartABInOpenMarket(const mAsset&) const;
	mAsset combinePartABInClosingMarket(const mAsset&) const;

public:
	mAsset ActOn(const mAsset&) const;

	mAsset cancelbuyMotherFundInOpenMarket(const mAsset&) const;

	void setOperation(const mOperation& opr) 	{		*this=opr;	}
	void setTime(const mTime& ot) {Time=ot;}
	void setOperationCategory(int i) {OperationCategory=i;}
	void setOperationCategory(mOperationCategory i) {OperationCategory=i;}
	void setOperatedObjectCategory(int i) {OperatedObjectCategory=i;}
	void setOperatedObjectCategory(mObjectCategory i) {OperatedObjectCategory=i;}
	void setOperatedObjectIndex(int i) {OperatedObjectIndex=i;}

	void setStructuredFundStateCopy(const mStructuredFundState& osf) {StructuredFundStateCopy=osf;}
	
	void setOperationAmoutInt(int i) {OperationAmoutInt=i;}
	void setOperationAmoutDouble(double d) {OperationAmoutDouble=d;}
	void setOperationAmoutLlint(long long int i) {OperationAmoutLlint=i;}

	mTime getTime() const  {return Time;}
	mOperationCategory getOperationCategory()  const {return OperationCategory;}
	mObjectCategory getOperatedObjectCategory() const {return OperatedObjectCategory;}
	int getOperatedObjectIndex() const { return OperatedObjectIndex;}

	mStructuredFundState getStructuredFundStateCopy() const {return StructuredFundStateCopy;}

	int getOperationAmoutInt() const {return OperationAmoutInt;}
	double getOperationAmoutDouble() const {OperationAmoutDouble;}
	long long int getOperationAmoutLlint() const {return OperationAmoutLlint;}

	void changeCategoryFromOpenMarketToClose();

	friend std::ostream& operator << (std::ostream& osm, const mOperation &ope);
};

std::ostream& operator << (std::ostream& osm, const mOperation &ope); 

#endif