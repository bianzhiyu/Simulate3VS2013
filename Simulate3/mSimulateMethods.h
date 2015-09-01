/*
Author : bianzhiyu@126.com
IDE    : VS2013
Time   : 2015/8/27 15:36
*/
#pragma once
#ifndef __mSimulateMethods
#define __mSimulateMethods

#include "mTradeDetail.h"
#include "mAsset.h"
#include "mNStrategy.h"
#include "mStockStreamListener.h"
#include "mQueue.h"

//#define DeBug

/* This simulation function below only act in two ways:
* 1: premium arbitrage:
*		buy FoFs(MotherFund), sell PartA, PartB
* 2: discount arbitrage:
*		redeem (sell) FoFs, buy PartA, PartB
*  And in one day, only one kind of these two action will be performed (but can be performed more than once)
*/
void SimulateOneDay(const mAsset& InitialAsset,
	const VectorTradeDetail& SFAStream,
	const VectorTradeDetail& SFBStream,
	const VectorTradeDetail& IndexStream,
	VectorStrategy & StrategyStreamInstant,
	VectorStrategy & StrategyStreamHung,
	mAsset& TerminalAsset
	);

/*Save Stock State , and:
* Time filter, getMaxTotalTurnover, getMinTotalTurnover
*/
class mTradeDetailQueue :public mclstd::mQueue<mTradeDetail>
{
public:
	mTradeDetailQueue() :mQueue(){}
	mTradeDetailQueue(const mTradeDetailQueue& mm) :mQueue<mTradeDetail>(mm) {}
	mTradeDetailQueue& operator=(const mTradeDetailQueue& mm)
	{
		this->mQueue<mTradeDetail>::operator=(mm);
		return *this;
	}
	~mTradeDetailQueue()
	{
		mQueue<mTradeDetail>::~mQueue();
	}

	void filter(mTime StartTime, mTime EndTime)
	{
		if (Size < 1) return;
		mNode<mTradeDetail> * pt = &Head;
		while (pt->Next)
		{
			mNode<mTradeDetail> * pt2 = pt->Next;
			if ((pt2->Cont.getTime()<StartTime) || (pt2->Cont.getTime()>EndTime))
			{
				pt->Next = pt2->Next;
				delete pt2;
				Size--;
			}
			else pt = pt->Next;
		}
		Tail = &Head;
		while (Tail->Next)		Tail = Tail->Next;
	}
	int getMaxTotalTurnover() const
	{
		if (Size < 1)  return 0;
		mNode<mTradeDetail> * pt = Head.Next;
		int d = pt->Cont.getTotalTurnover();
		while (pt->Next)
		{
			pt = pt->Next;
			if (pt->Cont.getTotalTurnover()>d)	d = pt->Cont.getTotalTurnover();
		}
		return d;
	}
	int getMinTotalTurnover() const
	{
		if (Size < 1)  return 0;
		mNode<mTradeDetail> * pt = Head.Next;
		int d = pt->Cont.getTotalTurnover();
		while (pt->Next)
		{
			pt = pt->Next;
			if (pt->Cont.getTotalTurnover()<d)	d = pt->Cont.getTotalTurnover();
		}
		return d;
	}
};

void SimulateOneDay2(const mAsset& InitialAsset,
	const VectorTradeDetail& SFAStream,
	const VectorTradeDetail& SFBStream,
	const VectorTradeDetail& IndexStream,
	VectorStrategy & StrategyStreamInstant,
	VectorStrategy & StrategyStreamHung,
	mAsset& TerminalAsset
	);

#endif 