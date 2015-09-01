/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#include "mMotherFundState.h"

double mMotherFundState::estimateNetValue(double PriceT,double Price0) 
{
	if (abs(Price0)<1e-14)
	{
		EstimatedNetValue=0;
		return 0;
	}
	EstimatedNetValue=getClosingNetValue()*investPct*PriceT/Price0+getClosingNetValue()*(1-investPct) ;
	return EstimatedNetValue;
}