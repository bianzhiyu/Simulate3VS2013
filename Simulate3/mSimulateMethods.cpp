/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/31 , 19:35
*/
#include "mSimulateMethods.h"

long long minim(long long l1, long long l2)
{
	if (l1 < l2)	return l1;
	return l2;
}

/* This simulation function below only act in two ways:
* 1: premium arbitrage:
*		buy FoFs(MotherFund), sell PartA, PartB
* 2: discount arbitrage:
*		redeem (sell) FoFs, buy PartA, PartB
* characters:
* 1:	in one day, only one kind of these two actions (but FoFs and redeem FoFs) will be performed (but can be performed more than once)
* 2:	the Method below taking volume limit into consideration : 10% turnovers happening in the last 5min
* In order to record turnover, define a queue class
* 3:	if premium arbitrage is activated
*		amount of capital will be recalculated at 14:59:50,
*		in order to match the shares of AB parts bought this day more accurately
*/
void SimulateOneDay2(const mAsset& InitialAsset,
	const VectorTradeDetail& SFAStream,
	const VectorTradeDetail& SFBStream,
	const VectorTradeDetail& IndexStream,
	VectorStrategy & StrategyStreamAB,
	VectorStrategy & StrategyStreamM,
	mAsset& TerminalAsset
	)
{
	if ((SFAStream.size() == 0) || (SFBStream.size() == 0) || (IndexStream.size() == 0))
	{
		TerminalAsset = InitialAsset;
		return;
	}

	mAsset tmpAssetState(InitialAsset);

	//Strategy stream for today
	VectorStrategy tmpStrategyStreamAB, tmpStrategyStreamM;

	mTime openMarketTime, closeMarketTime;// Time at which market is opened / closed
	openMarketTime = SFAStream[0].Time;
	if (SFBStream[0].Time>openMarketTime) openMarketTime = SFBStream[0].Time;
	if (IndexStream[0].Time>openMarketTime) openMarketTime = IndexStream[0].Time;
	closeMarketTime = SFAStream[SFAStream.size() - 1].Time;
	if (SFBStream[SFBStream.size() - 1].Time<closeMarketTime) closeMarketTime = SFBStream[SFBStream.size() - 1].Time;
	if (IndexStream[IndexStream.size() - 1].Time<closeMarketTime) closeMarketTime = IndexStream[IndexStream.size() - 1].Time;

	//Some important time node
	//mTime StartActionTime("20150826143000"), EndActionTime("20150826150000"); //set action time window
	mTime StartActionTime, EndActionTime;
	StartActionTime=SFAStream[0].getTime();
	StartActionTime.setHour(14);
	StartActionTime.setMinute(30);
	StartActionTime.setSecond(0);
	EndActionTime = StartActionTime;
	EndActionTime.setHour(15);
	EndActionTime.setMinute(0);
	//time for rearrange capital for FoFs  if premium arbitrage is activated
	mTime TimeForrearrange_buyFoFs(StartActionTime);
	TimeForrearrange_buyFoFs.setHour(14);
	TimeForrearrange_buyFoFs.setMinute(59);
	TimeForrearrange_buyFoFs.setSecond(50);
	bool isRearranged = false;

	StockStreamListener SSL;
	//The Listener is the bridge between input port and inner datastructure
	// it receives data from the input port, transforms data form, and sends data to inner datastructure
	SSL.setInitialIndexState(IndexStream[0].toStockState());
	SSL.setMFundState(InitialAsset.MotherFund);
	SSL.setInitialSFundAState(InitialAsset.PartA);
	SSL.setInitialSFundBState(InitialAsset.PartB);

	unsigned int pointA = 0, pointB = 0, pointI = 0;	//to get the latest info of stocks in simulation

	int TradeDir = TradeDirectionNsp::NoneAction;

	double PositiveThreshold = 0.05, NegativeThreshold = -0.05;

	mTradeDetailQueue CacheA, CacheB;	//To get latest turnover for a while
	const int CacheTimeSpan = 60 * 5;

	for (mTime iTime = openMarketTime; !(iTime>closeMarketTime); iTime = iTime + 10)
	{
		while ((pointA<SFAStream.size() - 1) && (SFAStream[pointA + 1].Time<=iTime)) pointA++;
		while ((pointB<SFBStream.size() - 1) && (SFBStream[pointB + 1].Time<=iTime)) pointB++;
		while ((pointI<IndexStream.size() - 1) && (IndexStream[pointI + 1].Time<=iTime)) pointI++;

		//Listener Working : receive data, transform form
		SSL.setContempIndexState(IndexStream[pointI].toStockState());
		SSL.setContempSFundAState(SFAStream[pointA].toSonFundState());
		SSL.setContempSFundBState(SFBStream[pointB].toSonFundState());

		//Update Situation, the price A B in tmpAssetState influence calculation with Operation
		//Should separate information of A,B by comparing Index 
		tmpAssetState.setPartA(SSL.getContempSFundAState());
		tmpAssetState.setPartB(SSL.getContempSFundBState());
		tmpAssetState.estimateNetValueOfMotherFund(SSL.ContempIndexState.getPrice(), SSL.InitialIndexState.getPrice());

		//update CacheA,CacheB to get the latest turnover
		//Should separate information of A,B by comparing Index 
		CacheA.pushin(SFAStream[pointA]);
		CacheB.pushin(SFBStream[pointB]);
		//delete info out of date
		CacheA.filter(iTime - CacheTimeSpan, iTime);
		CacheB.filter(iTime - CacheTimeSpan, iTime);

		//Suppose 10% others Trading Volume is the max Volume limit
		int MaxShareLimitA = (CacheA.getMaxTotalTurnover() - CacheA.getMinTotalTurnover()) / 10 + 10;
		int MaxShareLimitB = (CacheB.getMaxTotalTurnover() - CacheB.getMinTotalTurnover()) / 10 + 10;

		if ((iTime<StartActionTime) || (iTime>EndActionTime)) continue;	//only act in the last 30min

		//Blow is the decision-maker
		if ((SSL.getInstantPremiumRate()>PositiveThreshold) && (TradeDir != TradeDirectionNsp::redeemMotherFund))
			//Premium Arbitrage is activated
			//buy FoFs(MotherFund), sell PartA, PartB
		{
			long long int share = minim(tmpAssetState.getPositionA(0), tmpAssetState.getPositionB(0));
			double returnrate = SSL.getInstantPremiumRate();
			//the way to calculate cost is needed
			//profit will be sure only after closing market,

			//Volume Control
			if (share > MaxShareLimitA) share = MaxShareLimitA;
			if (share > MaxShareLimitB) share = MaxShareLimitB;

			share = (share / 100) * 100;

			if (share>0)
			{
				TradeDir = TradeDirectionNsp::buyMotherFund;

				mOperation oprA, oprB, oprM;
				oprA.setTime(iTime);
				oprA.setOperationCategory(mOperationCategory::sellPartA);
				oprA.setOperatedObjectCategory(mObjectCategory::PartA);
				oprA.setOperatedObjectIndex(tmpAssetState.getIndexA());
				oprA.setStructuredFundStateCopy((mStructuredFundState)tmpAssetState);
				oprA.setOperationAmoutLlint(share);

				mNStrategy ts(oprA, returnrate, 0, 0);
				tmpStrategyStreamAB.push_back(ts);
				tmpAssetState = oprA.ActOn(tmpAssetState);

				oprB.setTime(iTime);
				oprB.setOperationCategory(mOperationCategory::sellPartB);
				oprB.setOperatedObjectCategory(mObjectCategory::PartB);
				oprB.setOperatedObjectIndex(tmpAssetState.getIndexB());
				oprB.setStructuredFundStateCopy((mStructuredFundState)tmpAssetState);
				oprB.setOperationAmoutLlint(share);

				ts.setAll(oprB, returnrate, 0, 0);
				tmpStrategyStreamAB.push_back(ts);
				tmpAssetState = oprB.ActOn(tmpAssetState);

				oprM.setTime(iTime);
				oprM.setOperationCategory(mOperationCategory::buyMotherFundInOpenMarket);
				oprM.setOperatedObjectCategory(mObjectCategory::MotherFund);
				oprM.setOperatedObjectIndex(tmpAssetState.getIndexM());
				oprM.setStructuredFundStateCopy((mStructuredFundState)tmpAssetState);
				oprM.setOperationAmoutDouble(2*share*tmpAssetState.getEstimatedNetValueOfMotherFund());
				oprM.setOperationAmoutLlint(2*share);

				ts.setAll(oprM, returnrate, 0, 0);
				tmpStrategyStreamM.push_back(ts);
				tmpAssetState = oprM.ActOn(tmpAssetState);
			}
		}
		if ((SSL.getInstantPremiumRate()<NegativeThreshold) && (TradeDir != TradeDirectionNsp::buyMotherFund))
			//Discount Arbitrage is activated
			//redeem (sell) FoFs, buy PartA, PartB
		{
			long long int share = minim(tmpAssetState.getPositionM(0) / 2,
				(long long)(tmpAssetState.getCashFlow(0) / (SSL.getContempPriceA() + SSL.getContempPriceB()) - 1)
				);
			if (share<0)  share = 0;

			//Volume Control
			if (share > MaxShareLimitA) share = MaxShareLimitA;
			if (share > MaxShareLimitB) share = MaxShareLimitB;

			share = (share / 100) * 100;

			if (share>0)
			{
				TradeDir = TradeDirectionNsp::redeemMotherFund;

				double returnrate = -SSL.getInstantPremiumRate();
				//the way to calculate cost is needed
				//profit can be sure only after closing market,

				mOperation oprA, oprB, oprM;
				oprA.setTime(iTime);
				oprA.setOperationCategory(mOperationCategory::buyPartA);
				oprA.setOperatedObjectCategory(mObjectCategory::PartA);
				oprA.setOperatedObjectIndex(tmpAssetState.getIndexA());
				oprA.setStructuredFundStateCopy((mStructuredFundState)tmpAssetState);
				oprA.setOperationAmoutLlint(share);

				mNStrategy ts(oprA, returnrate, 0, 0);
				tmpStrategyStreamAB.push_back(ts);
				tmpAssetState = oprA.ActOn(tmpAssetState);

				oprB.setTime(iTime);
				oprB.setOperationCategory(mOperationCategory::buyPartB);
				oprB.setOperatedObjectCategory(mObjectCategory::PartB);
				oprB.setOperatedObjectIndex(tmpAssetState.getIndexB());
				oprB.setStructuredFundStateCopy((mStructuredFundState)tmpAssetState);
				oprB.setOperationAmoutLlint(share);

				ts.setAll(oprB, returnrate, 0, 0);
				tmpStrategyStreamAB.push_back(ts);
				tmpAssetState = oprB.ActOn(tmpAssetState);

				oprM.setTime(iTime);
				oprM.setOperationCategory(mOperationCategory::redeemMotherFundInOpenMarket);
				oprM.setOperatedObjectCategory(mObjectCategory::MotherFund);
				oprM.setOperatedObjectIndex(tmpAssetState.getIndexM());
				oprM.setStructuredFundStateCopy((mStructuredFundState)tmpAssetState);
				oprM.setOperationAmoutLlint(2 * share);

				ts.setAll(oprM, returnrate, 0, 0);
				tmpStrategyStreamM.push_back(ts);
				tmpAssetState = oprM.ActOn(tmpAssetState);
			}
		}
		//End of Desicion maker

		//rearrange amount for buying FoFs
		if ((iTime < TimeForrearrange_buyFoFs + 10) && (iTime >= TimeForrearrange_buyFoFs) &&
			(!isRearranged) && (TradeDir == TradeDirectionNsp::buyMotherFund))
		{
			isRearranged = true;	//only rearrange once
			long long expshare = 0;		//expecting shares of buying motherfund 
			VectorStrategy::iterator pt = tmpStrategyStreamM.begin();
			while (pt != tmpStrategyStreamM.end())
			{
				if (pt->getOperationCategory() == mOperationCategory::buyMotherFundInOpenMarket)
				{
					//defreeze cashflow
					tmpAssetState=pt->cancelbuyMotherFundInOpenMarket(tmpAssetState);
					//accumulate share
					expshare += pt->getOperationAmoutLlint();
					// delete operation,
					pt = tmpStrategyStreamM.erase(pt);
				}
				else pt++;
			}
			//re push opreration in tmpStrategyStreamM
			//re act on tmpAssetState
			double tNavM = tmpAssetState.estimateNetValueOfMotherFund(SSL.getContempIndexPrice(), SSL.getInitialIndexPrice());
			double returnrate = SSL.getInstantPremiumRate();
			//***
			long long share = (long long)(tmpAssetState.getCashFlow(0) / tNavM);
			share = share / 100 * 100;
			//if there is enough capital to buy expected shares of FoFs, buy expshare ; else buy max share available
			if (share >= expshare)		share = expshare;
			
			mOperation oprM;
			mNStrategy ts;

			oprM.setTime(iTime);
			oprM.setOperationCategory(mOperationCategory::buyMotherFundInOpenMarket);
			oprM.setOperatedObjectCategory(mObjectCategory::MotherFund);
			oprM.setOperatedObjectIndex(tmpAssetState.getIndexM());
			oprM.setStructuredFundStateCopy((mStructuredFundState)tmpAssetState);
			oprM.setOperationAmoutDouble(share*tNavM);
			oprM.setOperationAmoutLlint(share);

			ts.setAll(oprM, returnrate, 0, 0);
			tmpStrategyStreamM.push_back(ts);			//re push opreration in tmpStrategyStreamM
			tmpAssetState = oprM.ActOn(tmpAssetState);  //re act on tmpAssetState
		}
		//End of rearrange amount for buying FoFs
	}

	/*need to get closing price of motherfund, in order to :
	* 1: calculate all profit, (cost,) real return rate of tmpStrategyStreamHung , here -- before it is poped into tmpStrategyStreamHung !!
	* 2: update the state of fund (closing price of MotherFund)
	* 3: perform all actions in tmpStrategy, whose calculation depends on new closing price  !!
	*/
	//update Closing Price of Mother Fund by hand....!!
	tmpAssetState.updateClosingPriceOfMotherFund(0.847);
	/*
	tmpAssetState.updateClosingPriceOfMotherFund(
		tmpAssetState.estimateNetValueOfMotherFund(SSL.getContempIndexPrice(), SSL.getInitialIndexPrice()
		)
		);
		*/
	
	//output Stategy
	for (auto iss = tmpStrategyStreamAB.begin(); iss != tmpStrategyStreamAB.end(); iss++)
		StrategyStreamAB.push_back(*iss);
	for (auto iss = tmpStrategyStreamM.begin(); iss != tmpStrategyStreamM.end(); iss++)
		StrategyStreamM.push_back(*iss);

	//performed Strategy of FoFs, actually
	for (auto iss = tmpStrategyStreamM.begin(); iss != tmpStrategyStreamM.end(); iss++)
	{
		iss->changeCategoryFromOpenMarketToClose();
		tmpAssetState = (*iss).ActOn(tmpAssetState);
	}

	TerminalAsset = tmpAssetState;	//set Terminal asset;
}
