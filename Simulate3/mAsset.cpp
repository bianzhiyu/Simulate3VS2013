/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#include "mAsset.h"

mAsset::mAsset() 
	: mStructuredFundState(), mPositionState()
{}
mAsset::mAsset(const mAsset& ma)
	: mStructuredFundState((mStructuredFundState)ma), mPositionState((mPositionState)ma)
{}
mAsset& mAsset::operator =(const mAsset& ma)
{
	this->mStructuredFundState::operator=((mStructuredFundState)ma);
	this->mPositionState::operator=((mPositionState)ma);

	return *this;
}

void mAsset::updatePositionForNewDay()
{
	CashFlow[0]+=CashFlow[1];
	for (int i=1;i<7;i++)
		CashFlow[i]=CashFlow[i+1];
	CashFlow[7]=0;

	
	PositionM[0]+=PositionM[1];
	for (int i=1;i<3;i++)
		PositionM[i]=PositionM[i+1];
	PositionM[3]=0;

	PositionA[0]+=PositionA[1];
	PositionA[1]=0;

	PositionB[0]+=PositionB[1];
	PositionB[1]=0;
}

double mAsset::getTotalCapital() const
{
	double C=0;
	for (int i=0;i<8;i++)
		C+=CashFlow[i];
	C+=(PositionM[0]+PositionM[1]+PositionM[2]+PositionM[3])*MotherFund.getClosingPrice();
	C+=(PositionA[0]+PositionA[1])*PartA.getPrice();
	C+=(PositionB[0]+PositionB[1])*PartB.getPrice();
	return C;
}

void mAsset::showAsset(std::ostream& osm) const
{
	this->showPosition(osm);
	osm<<"\nTotalCapital= "<<getTotalCapital();
}