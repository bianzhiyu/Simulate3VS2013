/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/31 , 19:35
*/
/*
*Head Files: Controlling files, Data structure files, Processing files
*	Controlling files: 
*		AbsoluteVariety.h   (not included in this version)
*	Date structure fiels:
*		mTime.h		:Custom Common Library
*		mQueue.h	:Custom Common Library
*		mTradeDetail.h	:	Input Date
*		mStockState.h
*		mETFState.h
*		mMotherFundState.h
*		mSonFundState.h
*		mObjectCategory.h
*		mOperationCategory.h
*		mOperation.h
*		mStructuredFundState.h
*		mPositionState.h
*		mAsset.h
*		mNStrategy.h
*		mStockStreamListener.h
*	Pocessing files:
*		mSimulateMethods.h	:	real simulation
*/
/*settings:
*1:	core.cpp, setInitialAsset: almost all
*2:	core.cpp, main:	three input file name
*3: mSimulateMethod.cpp, SimulateOneDay2 line290:net value of FoFs today 
*4: mSimulateMethod.cpp, SimulateOneDay2 line84: threshold of premium rate to trade
*/
#include <iostream>
#include <iomanip>
#include <string>

#include "mTime.h"
#include "mTradeDetail.h"
#include "mSonFundState.h"
#include "mMotherFundState.h"
#include "mAsset.h"
#include "mNStrategy.h"
#include "mSimulateMethods.h"

void setInitialAsset(mAsset& ma)
{
	mTime InitTime;
	InitTime.transfer("20150826090000");
	ma.setTime(InitTime);

	mMotherFundState InitMF;
	/*mStockState::
	* void setAll(int ind, const mTime& ot, double p, double closingprice)
	* void setAll(int ind, const mTime& ot, double p, double closingprice,double openingprice)
	* void setAll(int ind, const mTime& ot, double p, double preclosingprice, double closingprice, double openingprice)
	*/
	InitMF.setAll(161812, InitTime, 0.865, 0.865);
	InitMF.setinvestPct(0.95);
	ma.setMotherFund(InitMF);

	mSonFundState InitPA;
	InitPA.setAll(150018, InitTime, 0.924, 0.924);
	ma.setPartA(InitPA);

	mSonFundState PB;
	PB.setAll(150019, InitTime, 0.986, 0.986);
	ma.setPartB(PB);

	mStockState Ind;
	Ind.setAll(399330, InitTime, 3504.36, 3492.09, 3504.36);
	ma.setTrackIndex(Ind);

	ma.setCashFlow(0,0,0,0,0,0,0,0);
	ma.setPositionA(50000,0);	
	ma.setPositionB(50000,0);
	ma.setPositionM(0,0,0,0);
}

void PrintResult(const VectorStrategy&StrategyStreamAB,
				 const VectorStrategy&StrategyStreamM,
				 const mAsset& InitAsset,
				 const mAsset& TerminalAsset
				 )
{
	using std::cout;
	using std::endl;
	using std::ofstream;

	ofstream outfile("Result.txt");

	outfile.setf(std::ios::fixed);			//set output format of double : fixed number
	outfile << std::setprecision(6);			//set precision : 6-digit : *.??????

	outfile << "InitialAsset:\n";
	InitAsset.showAsset(outfile);
	outfile << "\n----------------------------\n";;

	outfile << "TerminalAsset:\n";
	TerminalAsset.showAsset(outfile);
	outfile << "\n----------------------------\n";

	outfile << "StrategyStreamAB:\n";
	outfile << "StrategyStreamAB.size() = " << StrategyStreamAB.size() << "\n\n";	
	for (auto i = StrategyStreamAB.begin(); i != StrategyStreamAB.end(); i++)
		outfile << (*i) << endl << endl;
	outfile << "----------------------------\n";

	outfile << "StrategyStreamM:\n";
	outfile << "StrategyStreamM.size() = " << StrategyStreamM.size() << "\n\n";		
	for (auto i = StrategyStreamM.begin(); i != StrategyStreamM.end(); i++)
		outfile << (*i) << endl << endl;
	outfile << "----------------------------\n";

	outfile.close();
}

int main(int argc,char *argv)
{
	VectorTradeDetail DataSFundA,DataSFundB,DataIndex;		//A:sz150018, B:sz150019, M:161812, Index:sz399330
	
	inputRawData(DataSFundA, "sz150018.csv");
	inputRawData(DataSFundB, "sz150019.csv");
	inputRawData(DataIndex, "sz399330.csv");

	mAsset InitAsset;		//Initial state
	setInitialAsset(InitAsset);

	mAsset TerminalAsset;  //save AssetState after one-day action
	VectorStrategy StrategyStreamAB,StrategyStreamM;
		//StrategyStreamAB:  operations on AB
		//StrategyStreamM:     operations on FoFs

	//update position of mAsset at 00:00:00  !!
	SimulateOneDay2(InitAsset, DataSFundA, DataSFundB, DataIndex, StrategyStreamAB, StrategyStreamM, TerminalAsset);
	//update closing price of mAsset at closing market !!

	PrintResult(StrategyStreamAB, StrategyStreamM, InitAsset, TerminalAsset);
	
	system("pause");
	return 0;
}