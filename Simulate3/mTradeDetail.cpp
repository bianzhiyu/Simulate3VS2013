/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#include "mTradeDetail.h"

void inputRawData(VectorTradeDetail& stockstream,char* inFileName)
{
	std::ifstream fin;
	fin.open(inFileName);
	
	std::string str;
	std::getline(fin, str);	// headline of table
	
	int comma=0;
	std::string atp;

	while (std::getline(fin,str))
	{
		//RawMaterial,row 0-48
		if (str.length()==0)  continue;
		mTradeDetail tp;
		while (str.length()>0)
		{
			comma = str.find(",");
			if (comma!=-1)
			{
				atp = str.substr(0, comma);
				tp.RawMaterial.push_back(atp);
				str.erase(0, comma + 1);
			}
			else
			{
				tp.RawMaterial.push_back(str);
				str="";
			}
		}

		//row 1 : Index
		tp.Index=mTime::stringtoint(tp.RawMaterial[InputFormat::RowIndex]);
		//row 2 : contemporary Price 
		tp.Price=mTime::stringtodouble(tp.RawMaterial[InputFormat::RowContempPrice]);
		//row 5 : TotalTurnover
		tp.TotalTurnover=mTime::stringtoint(tp.RawMaterial[InputFormat::RowTotalTurnover]);
		//row 29: Time
		tp.RawMaterial[InputFormat::RowTime][13]='0';		//set the last digit=0, making the step = 10s
		tp.Time.transfer(tp.RawMaterial[29]);

		stockstream.push_back(tp);
	}

	fin.close();
}

void mTradeDetail::printcout()
{
	std::cout<<Index<<" "
		<<TotalTurnover<<" "
		<<Time.toString()<<" "
		<<Price<<std::endl;
}

mStockState mTradeDetail::toStockState() const
{
	mStockState mss(Index,Time,Price,
		mTime::stringtodouble(RawMaterial[InputFormat::RowClosingPrice]),
		mTime::stringtodouble(RawMaterial[InputFormat::RowOpenPrice])
		);
	return mss;
}
mSonFundState mTradeDetail::toSonFundState() const
{
	mSonFundState msfs(Index,Time,Price,
		mTime::stringtodouble(RawMaterial[InputFormat::RowClosingPrice]),
		mTime::stringtodouble(RawMaterial[InputFormat::RowOpenPrice])
		);
	return msfs;
}
mETFState mTradeDetail::toETFState () const
{
	mETFState mes(Index,Time,Price,
		mTime::stringtodouble(RawMaterial[InputFormat::RowClosingPrice]),
		mTime::stringtodouble(RawMaterial[InputFormat::RowOpenPrice])
		);
	return mes;
}


std::ostream& operator  << (std::ostream &osm, const mTradeDetail& mTD)
{
	osm<<mTD.Index<<" "
		<<mTD.Price<<" "
		<<mTD.TotalTurnover<<" "
		<<mTD.Time.toString(mTime::StandardFormat);
	return osm;
}

void showVectorTradeDetailToCout(const VectorTradeDetail& stockstream)
{
	std::cout << std::endl;
	for (auto i = stockstream.begin(); i != stockstream.end(); i++)
		std::cout << (*i) << std::endl;
}