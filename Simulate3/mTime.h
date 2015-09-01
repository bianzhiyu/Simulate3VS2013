/*
* Author: bianzhiyu
* IDE : VS2013
* Time : 2015 / 8 / 26, 13 : 48
*/
/* 
* define a custom time class: mTime, and some static functions
* mTime is somtimes used as a date.
* basic method:  toString(int Format=mTime::CompactFormat),  transfer(const std::string&), > , + , addDays, minusDays
* Static function:
*   bool isLeapYear(int), int DaysofMonth(int y,int m), mTime StringtoTime(const std::string&)
*   int Stringtoint(const std::string&), double Stringtodouble(const std::string&)
*/
#ifndef __MTIME
#define __MTIME

#include <string>
#include <iostream>

class mTime
{
public:
	//control output form control
	//used in toString(int Format) ,mTime StringtoTime(const string& ss,int Format);
	const static int CompactFormat = 0;
	const static int StandardFormat = 1;
	const static int DateOnlyCompactFormat = 2;
	const static int DateOnlyStandardFormat = 3;
protected:
	int Year, Month, Day, Hour, Minute, Second;
	long long int RawData;
public:
	static bool isLeapYear(int Y);
	static int DaysofMonth(int y, int m);
	static int DaysofMonth(int m);
	static mTime StringtoTime(const std::string& ss);
	/*transfer string to int
    * string can be like: +123, -132, 320
    * if ss is -123.543, numbers after dot will be ignored, including dot.
    */
	static int stringtoint(const std::string& ss);
	/*transfer string to double
    * number can be :
    *  +1, -1 ,1,
    * +1.5,-0.52,123.45
    */
	static double stringtodouble(const std::string& ss);
	//static long long minim(long long, long long);
	/*CompactFormat:
	*transfer a 14-bit-long string to mTime: YYYYMMDDHHMMSS
	* DateOnlyCompactFormat:  YYYYMMDD
	*return 0 means fail to transfer
	*return 1 means succeed to transfer
	*/
	static mTime StringtoTime(const std::string& ss, int Format = mTime::CompactFormat);

	bool isConsistent() const;		//Judge whether RawDate is consistent with other datas
	void updateRawDate();

	mTime()
	{
		Year = Month = Day = Hour = Minute = Second = 0;
		RawData = 0;
	}
	mTime(const mTime&mm)
	{
		Year = mm.Year;	Month = mm.Month;	Day = mm.Day;
		Hour = mm.Hour;	Minute = mm.Minute;	Second = mm.Second;
		RawData = mm.RawData;
	}
	mTime& operator =(const mTime & mm)
	{
		Year = mm.Year;	Month = mm.Month;	Day = mm.Day;
		Hour = mm.Hour;	Minute = mm.Minute;	Second = mm.Second;
		RawData = mm.RawData;
		return *this;
	}
	mTime(const std::string& str);
	mTime(int year, int month, int day, int hour, int minute, int second)
	{
		Year = year;  Month = month;  Day = day;  Hour = hour;  Minute = minute;  Second = second;
		updateRawDate();
	}
	mTime(int year, int month, int day){ Year = year; Month = month; Day = day; Hour = Minute = Second = 0; }

	int getYear() const { return Year; }
	int getMonth() const { return Month; }
	int getDay() const { return Day; }
	int getHour() const { return Hour; }
	int getMinute() const { return Minute; }
	int getSecond() const { return Second; }

	void setYear(int i) { Year = i; updateRawDate(); }
	void setMonth(int i)
	{
		if (i < 1)  i = 1;
		if (i>12) i = 12;
		Month = i;
		updateRawDate();
	}
	void setDay(int i)
	{
		if (i < 1) i = 1;
		if (i>DaysofMonth(Year, Month)) i = DaysofMonth(Year, Month);
		Day = i;
		updateRawDate();
	}
	void setHour(int i)
	{
		if (i < 0) i = 0;
		if (i>59) i = 59;
		Hour = i;
		updateRawDate();
	}
	void setMinute(int i)
	{
		if (i < 0)	i = 0;
		if (i>59)	i = 59;
		Minute = i;
		updateRawDate();
	}
	void setSecond(int i)
	{
		if (i < 0)	i = 0;
		if (i>59)	i = 59;
		Second = i;
		updateRawDate();
	}
	void setDate(int y, int m, int d)
	{
		Year = y;
		if (m < 1)  m = 1;
		if (m>12) m = 12;
		Month = m;
		if (d < 1) d = 1;
		if (d>DaysofMonth(Year, Month)) d = DaysofMonth(Year, Month);
		Day = d;
		updateRawDate();
	}

	operator long long int() const	{ return RawData; }	//it'll be called when meeting enforced type transform
	bool operator > (const mTime&) const;	//A>B means A is later than B
	bool operator == (const mTime&) const;
	bool operator < (const mTime& ot) const { return !((*this>ot) || (*this == ot)); }
	bool operator >= (const mTime& ot) const { return ((*this>ot) || (*this == ot)); }
	bool operator <= (const mTime& ot) const { return !(*this>ot); }

	mTime operator + (int)const;	//plus some time, unit is second, int>0
	mTime operator - (int)const;	//minus some time, unit is second,int >0
	mTime operator + (long long)const;

	mTime& operator += (int i)
	{
		(*this) = this->operator+(i);
		this->updateRawDate();
		return *this;
	}
	mTime& operator -= (int i)
	{
		(*this) = this->operator-(i);
		this->updateRawDate();
		return *this;
	}

	/*CompactFormat:
	*transfer a 14-bit-long string to mTime: YYYYMMDDHHMMSS
	* DateOnlyCompactFormat:  YYYYMMDD
	*return 0 means fail to transfer
	*return 1 means succeed to transfer
	*/
	int transfer(const std::string& ss, int Format = mTime::CompactFormat);

	std::string toString(int Format = mTime::CompactFormat) const;
	//return a 14-bit-long string: YYYYMMDDHHMMSS
	//if MM<10, there will be an extra 0 added, 
	void addDays(int);
	void minusDays(int);

	long long int operator - (const mTime& ot)const;

	friend std::ostream& operator << (std::ostream &osm, mTime);

};

// output toString()
std::ostream& operator << (std::ostream &osm, mTime);

#endif
