/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#pragma once
#ifndef __mPositionState
#define __mPositionState

#include <iostream>

typedef long long int llint;

/*
*long long PositionM[4],PositionA[2],PositionB[2];
*double CashFlow[8];
*/
class mPositionState
{
public:
	llint PositionM[4],PositionA[2],PositionB[2];
	double CashFlow[8];
public:
	mPositionState();
	mPositionState(const mPositionState&);
	mPositionState& operator =(const mPositionState&);

	void setAllPosition(const llint pm[4], const llint pa[2],const llint pb[2],const double cf[8]);
	void setPositionM(const llint pm[4]);
	void setPositionM(llint m0,llint m1,llint m2,llint m3);
	void setPositionA(const llint pa[2]);
	void setPositionA(llint a0,llint a1);
	void setPositionB(const llint pb[2]);
	void setPositionB(llint b0,llint b1);
	void setCashFlow(const double cf[8]);
	void setCashFlow(double c0,double c1,double c2,double c3,double c4,double c5,double c6,double c7);

	double getCashFlow(int i) const;  //CashFlow[i]
	llint getPositionA(int i) const;	//Position?[i]
	llint getPositionB(int i) const;
	llint getPositionM(int i) const;

	void setCashFlow(int i,double d);	//CashFlow[i]=d
	void setPositionM(int i,llint l);	//CashFlow[i]=l

	void showPosition(std::ostream& osm=std::cout) const;

};

#endif