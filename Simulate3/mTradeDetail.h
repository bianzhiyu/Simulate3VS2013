/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#pragma once
#ifndef __mDATASTRUCTURE
#define __mDATASTRUCTURE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "mTime.h"
#include "mStockState.h"
#include "mSonFundState.h"
#include "mMotherFundState.h"
#include "mETFState.h"

namespace InputFormat
{
	const static int RowNum=49;
	const int RowIndex=1;
	const int RowContempPrice=2;
	const int RowClosingPrice=3;
	const int RowOpenPrice=4;
	const int RowTotalTurnover=5;
	const int RowTime=29;
}
//start from row 0

typedef std::vector<std::string> vectorstring;

/*class mTradeDetail
*public:
*const static int RowNum=49;
*vectorstring RawMaterial;
*
*int Index;
*int TotalTurnover;
*mTime Time;
*double Price;
*/
class mTradeDetail
{
public:
	vectorstring RawMaterial;

	int Index;
	int TotalTurnover;
	mTime Time;
	double Price;
public:
	mTradeDetail()	
	{
		Index=TotalTurnover=0;
		Price=0;
	}
	mTradeDetail(const mTradeDetail& mm)
	{
		Index=mm.Index;
		TotalTurnover=mm.TotalTurnover;
		Time=mm.Time;
		Price=mm.Price;
		for (unsigned int i=0;i<mm.RawMaterial.size();i++)
			RawMaterial.push_back(mm.RawMaterial[i]);
	}
	mTradeDetail& operator=(const mTradeDetail& mm)
	{
		Index=mm.Index;
		TotalTurnover=mm.TotalTurnover;
		Time=mm.Time;
		Price=mm.Price;
		RawMaterial.clear();
		for (unsigned int i=0;i<mm.RawMaterial.size();i++)
			RawMaterial.push_back(mm.RawMaterial[i]);
		return *this;
	}

	void printcout();

	mTime getTime() const	{		return Time;	}

	int getTotalTurnover() const { return TotalTurnover; }

	mStockState toStockState() const;
	mSonFundState toSonFundState() const;
	mMotherFundState toMotherFundSate() const;
	mETFState toETFState() const;

	friend std::ostream& operator  << (std::ostream &osm, const mTradeDetail& mTD);
};

typedef std::vector<mTradeDetail> VectorTradeDetail;

void inputRawData(VectorTradeDetail& stockstream,char* inFileName);
/*inFile format:
* First line:  headline
* next line to the end line:
*    (first row of each line if row 0)
*    row 1 : Index, row 2 : contemporary Price , row 5 : TotalTurnover, row 29: Time
*/

std::ostream& operator  << (std::ostream &osm, const mTradeDetail& mTD);

void showVectorTradeDetailToCout(const VectorTradeDetail& stockstream);
//row 1 : Index, row 2 : contemporary Price , row 5 : TotalTurnover, row 29: Time

#endif