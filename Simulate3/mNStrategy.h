/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
/*
* describe strategy,record
*/
#pragma once
#ifndef __MNSTRATEGY
#define __MNSTRATEGY

#include "mTime.h"
#include "mOperation.h"

namespace TradeDirectionNsp
{
	const int NoneAction=0;
	const int redeemMotherFund=1;
	const int buyMotherFund=2;
}

/*class mNStrategy: public mOperation,  double ReturnRate, Profit,Cost;
*/
class mNStrategy: public mOperation 
{
public:
	double ReturnRate, Profit,Cost;
public:
	mNStrategy():mOperation(),ReturnRate(0),Profit(0),Cost(0)	{}
	mNStrategy(const mOperation& opr,double returnrate):mOperation(opr),ReturnRate(returnrate){}
	mNStrategy(const mOperation& opr,double returnrate,double profit,double cost):
		mOperation(opr),ReturnRate(returnrate),Profit(profit),Cost(cost){}
	mNStrategy(const mNStrategy&mm):mOperation(mm)
	{
		ReturnRate=mm.ReturnRate;
		Profit=mm.Profit;
		Cost=mm.Cost;
	}
	mNStrategy& operator = (const mNStrategy& mm)
	{
		this->mOperation::operator=(mm);
		ReturnRate=mm.ReturnRate;
		Profit=mm.Profit;
		Cost=mm.Cost;
		return *this;
	}

	void setProfit(double d) {Profit=d;}
	double getProfit() const {return Profit;}

	void setCost(double d) {Cost=d;}
	double getCost() const {return Cost;}

	double getNetProfit() const  {return Profit-Cost;}

	double getReturnRate() const {return ReturnRate;}
	void setReturnRate(double d){ ReturnRate=d;};

	void setOperation(const mOperation& mm) {this->mOperation::operator=(mm);}

	void setAll(const mOperation& mm,double returnrate,double profit,double cost)
	{
		this->mOperation::operator=(mm);
		ReturnRate=returnrate;Profit=profit;Cost=cost;
	}
	
	friend std::ostream& operator << (std::ostream& osm, const mNStrategy& NS);
};

typedef std::vector<mNStrategy> VectorStrategy;

std::ostream& operator << (std::ostream& osm, const mNStrategy& NS);

#endif