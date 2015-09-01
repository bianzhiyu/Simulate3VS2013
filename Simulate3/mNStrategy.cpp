/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#include "mNStrategy.h"

std::ostream& operator << (std::ostream& osm, const mNStrategy & NS)
{
	osm<<(mOperation)(NS)<<"\nReturnRate= "<<NS.getReturnRate();
	return osm;
}