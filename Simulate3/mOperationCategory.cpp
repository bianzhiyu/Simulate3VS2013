/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#include "mOperationCategory.h"

bool operator ==(int i, const mOperationCategory&mm)
{
	return i==mm.OperationCategory;
}
bool operator !=(int i, const mOperationCategory&mm)
{
	return i!=mm.OperationCategory;
}