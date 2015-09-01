/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#include "mObjectCategory.h"

bool operator == (int i,const mObjectCategory&mm)
{
	return  i==mm.ObjectCategory;
}

bool operator != (int i,const mObjectCategory&mm)
{
	return  i!=mm.ObjectCategory;
}