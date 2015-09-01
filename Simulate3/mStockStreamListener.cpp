/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#include "mStockStreamListener.h"

double StockStreamListener::getInstantPremiumRate()
{
	double EstimatedNAVM=MFundState.estimateNetValue(ContempIndexState.getPrice(),InitialIndexState.getPrice());
	return (ContempSFundAState.Price+ContempSFundBState.Price-2*EstimatedNAVM)/(2*EstimatedNAVM);
}