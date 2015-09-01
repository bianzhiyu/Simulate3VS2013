/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#include "mPositionState.h"

mPositionState::mPositionState()
{
	for (int i=0;i<8;i++)
		CashFlow[i]=0;
	for (int i=0;i<4;i++)
		PositionM[i]=0;
	PositionA[0]=PositionA[1]=PositionB[0]=PositionB[1]=0;
}
mPositionState::mPositionState(const mPositionState& ma)
{
	for (int i=0;i<8;i++)
		CashFlow[i]=ma.CashFlow[i];
	for (int i=0;i<4;i++)
		PositionM[i]=ma.PositionM[i];
	PositionA[0]=ma.PositionA[0];
	PositionA[1]=ma.PositionA[1];
	PositionB[0]=ma.PositionB[0];
	PositionB[1]=ma.PositionB[1];
}
mPositionState& mPositionState::operator =(const mPositionState&ma)
{
	for (int i=0;i<8;i++)
		CashFlow[i]=ma.CashFlow[i];
	for (int i=0;i<4;i++)
		PositionM[i]=ma.PositionM[i];
	PositionA[0]=ma.PositionA[0];
	PositionA[1]=ma.PositionA[1];
	PositionB[0]=ma.PositionB[0];
	PositionB[1]=ma.PositionB[1];

	return *this;
}

void mPositionState::setAllPosition(const llint pm[4], const llint pa[2],const llint pb[2],const double cf[8])
{
	for (int i=0;i<8;i++)
		CashFlow[i]=cf[i];
	for (int i=0;i<4;i++)
		PositionM[i]=pm[i];
	PositionA[0]=pa[0];
	PositionA[1]=pa[1];
	PositionB[0]=pb[0];
	PositionB[1]=pb[1];
}
void mPositionState::setPositionM(const llint pm[4])
{
	for (int i=0;i<4;i++)
		PositionM[i]=pm[i];
}
void mPositionState::setPositionM(llint m0,llint m1,llint m2,llint m3)
{
	PositionM[0]=m0;
	PositionM[1]=m1;
	PositionM[2]=m2;
	PositionM[3]=m3;
}
void mPositionState::setPositionA(const llint pa[2])
{
	PositionA[0]=pa[0];
	PositionA[1]=pa[1];
}
void mPositionState::setPositionA(llint a0,llint a1)
{
	PositionA[0]=a0;
	PositionA[1]=a1;
}
void mPositionState::setPositionB(const llint pb[2])
{
	PositionB[0]=pb[0];
	PositionB[1]=pb[1];
}
void mPositionState::setPositionB(llint b0,llint b1)
{
	PositionB[0]=b0;
	PositionB[1]=b1;
}
void mPositionState::setCashFlow(const double cf[8])
{
	for (int i=0;i<8;i++)
		CashFlow[i]=cf[i];
}
void mPositionState::setCashFlow(double c0,double c1,double c2,double c3,double c4,double c5,double c6,double c7)
{
	CashFlow[0]=c0;CashFlow[1]=c1;CashFlow[2]=c2;CashFlow[3]=c3;
	CashFlow[4]=c4;CashFlow[5]=c5;CashFlow[6]=c6;CashFlow[7]=c7;
}

double mPositionState::getCashFlow(int i) const
{
	if (i<0) i=0;
	if (i>7) i=7;
	return CashFlow[i];
}
llint mPositionState::getPositionA(int i) const
{
	if (i<0) i=0;
	if (i>1) i=1;
	return PositionA[i];
}
llint mPositionState::getPositionB(int i) const
{
	if (i<0) i=0;
	if (i>1) i=1;
	return PositionB[i];
}
llint mPositionState::getPositionM(int i) const
{
	if (i<0) i=0;
	if (i>3) i=3;
	return PositionM[i];
}

void mPositionState::setCashFlow(int i,double d)
{
	if (i<0) i=0;
	if (i>7) i=7;
	CashFlow[i]=d;
}
void mPositionState::setPositionM(int i,llint l)
{
	if (i<0) i=0;
	if (i>3) i=3;
	PositionM[i]=l;
}

void mPositionState::showPosition(std::ostream& osm) const
{
	//osm<<"Position:\n";
	for (int i=0;i<4;i++)
		osm<<"M"<<i<<"= "<< PositionM[i]<<"\t";
	osm<<"\nA0"<<"= "<<PositionA[0]
	<<"\tA1= "<<PositionA[1]
	<<"\nB0= "<<PositionB[0]
	<<"\tB1= "<<PositionB[1]
	<<std::endl;
	//osm<<"CashFlow:\n";
	for (int i=0;i<8;i++)
		osm<<"C"<<i<<"= "<<CashFlow[i]<<"\t";
}