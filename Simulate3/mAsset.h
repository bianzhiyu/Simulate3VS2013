/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#pragma once
#ifndef __MASSET
#define __MASSET

#include "mTime.h"
#include "mStructuredFundState.h"
#include "mPositionState.h"

typedef long long int llint;

/*
* aim to describe one asset, inheritating: public mStructuredFundState, public mPositionState
*/
class mAsset : public mStructuredFundState, public mPositionState
{
public:
	mAsset();
	mAsset(const mAsset&);
	mAsset& operator =(const mAsset&);

	void updatePositionForNewDay();  //Only update Positions

	void showAsset(std::ostream& osm=std::cout) const;

	double getTotalCapital() const;
};

#endif