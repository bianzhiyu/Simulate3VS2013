/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Time	:	2015/08/27 , 13:36
*/
#include "mTime.h"

int mTime::stringtoint(const std::string& ss)
/*transfer string to int
* string can be like: +123, -132, 320
* if ss is -123.543, numbers after dot will be ignored, including dot.
*/
{
	int start = 0, len = ss.length();
	bool negative = false;
	if (ss[0] == '-')
	{
		negative = true;
		start = 1;
	}
	else if (ss[1] == '+')
	{
		start = 1;
		negative = false;
	}
	int l = start + 1;
	while ((l<len) && (ss[l] >= '0') && (ss[l] <= '9'))
		l++;
	len = l;
	int x = 0;
	for (int i = start; i<len; i++)
		x = x * 10 + (ss[i] - '0');
	if (negative) x = -x;
	return x;
}
double mTime::stringtodouble(const std::string& ss)
/*transfer string to double
* number can be :
*  +1, -1 ,1,
* +1.5,-0.52,123.45
*/
{
	double x = 0;
	bool negative = false;
	int start = 0, l = ss.length() - 1;
	if (ss[0] == '-')
	{
		start = 1;
		negative = true;
	}
	else if (ss[0] == '+')
	{
		start = 1;
		negative = false;
	}
	int dot = ss.find(".");
	if (dot == -1)
	{
		for (int i = start; i != l + 1; i++)
			x = x * 10 + (ss[i] - '0');
	}
	else
	{
		double expe = 1;
		for (int i = start; i != dot; i++)
			x = x * 10 + (ss[i] - '0');
		for (int i = dot + 1; i != l + 1; i++)
		{
			expe /= 10;
			x += expe*(ss[i] - '0');
		}
	}
	if (negative)	x = -x;
	return x;
}

bool mTime::isLeapYear(int Y)
{
	if (Y % 100 == 0)
	{
		if (Y % 400 == 0) return true;
		else return false;
	}
	else if (Y % 4 == 0) return true;
	else return false;
	return false;
}
int mTime::DaysofMonth(int y, int m)
{
	if ((m<0) || (m>12)) return 0;
	switch (m)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:case 12:return 31;
	case 4:case 6:case 9:case 11:return 30;
	default: if (((y % 100 != 0) && (y % 4 == 0)) || ((y % 100 == 0) && (y % 400 == 0))) return 29; else return 28;
	}
	return 0;
}
int mTime::DaysofMonth(int m)
{
	if ((m<0) || (m>12)) return 0;
	switch (m)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:case 12:return 31;
	case 4:case 6:case 9:case 11:return 30;
	default: return 28;
	}
	return 0;
}

mTime::mTime(const std::string& ss)
{
	Year = Month = Day = Hour = Minute = Second = 0;
	RawData = 0;
	if (ss.length() != 14) return;
	for (int i = 0; i != 14; i++)
	if ((ss[i]<'0') || (ss[i]>'9')) return;
	Year = (ss[0] - '0') * 1000 + (ss[1] - '0') * 100 + (ss[2] - '0') * 10 + ss[3] - '0';
	Month = (ss[4] - '0') * 10 + ss[5] - '0';
	if ((Month>12) || (Month<1)) return;
	Day = (ss[6] - '0') * 10 + ss[7] - '0';
	if ((Day>mTime::DaysofMonth(Year, Month)) || (Day<1)) return;
	Hour = (ss[8] - '0') * 10 + ss[9] - '0';
	if ((Hour>24) || (Hour<0)) return;
	if (Hour == 24) Hour = 0;
	Minute = (ss[10] - '0') * 10 + ss[11] - '0';
	if ((Minute>60) || (Minute<0)) return;
	if (Minute == 60) Minute = 0;
	Second = (ss[12] - '0') * 10 + ss[13] - '0';
	if ((Second>60) || (Second<0)) return;
	if (Second == 60) Second = 0;
	updateRawDate();
}
bool mTime::isConsistent() const
{
	long long int x = RawData;
	if (x % 100 != Second) return false;
	x = x / 100;
	if (x % 100 != Minute) return false;
	x = x / 100;
	if (x % 100 != Hour) return false;
	x = x / 100;
	if (x % 100 != Day) return false;
	x = x / 100;
	if (x % 100 != Month) return false;
	x = x / 100;
	if (x != Year) return false;
	return true;
}
void mTime::updateRawDate()
{
	RawData = Year;
	RawData = RawData * 100 + Month;
	RawData = RawData * 100 + Day;
	RawData = RawData * 100 + Hour;
	RawData = RawData * 100 + Minute;
	RawData = RawData * 100 + Second;
}
bool mTime::operator > (const mTime& ot) const
{
	if (Year>ot.Year) return true;
	if (Year<ot.Year) return false;

	if (Month>ot.Month) return true;
	if (Month<ot.Month) return false;

	if (Day>ot.Day) return true;
	if (Day<ot.Day) return false;

	if (Hour>ot.Hour) return true;
	if (Hour<ot.Hour) return false;

	if (Minute>ot.Minute) return true;
	if (Minute<ot.Minute) return false;

	if (Second>ot.Second) return true;
	return false;
}
bool mTime::operator == (const mTime&ot) const
{
	return (Year == ot.Year) && (Month == ot.Month) && (Day == ot.Day) && (Hour == ot.Hour) && (Minute == ot.Minute) && (Second == ot.Second);
}
mTime mTime::operator + (int it) const
{
	if (it <= 0) return *this;
	mTime ot(*this);
	ot.Second += it;
	if (ot.Second>59)
	{
		ot.Minute += ot.Second / 60;
		ot.Second %= 60;
	}
	else return ot;
	if (ot.Minute>59)
	{
		ot.Hour += ot.Minute / 60;
		ot.Minute %= 60;
	}
	else return ot;
	if (ot.Hour>23)
	{
		ot.Day += ot.Hour / 24;
		ot.Hour %= 24;
	}
	else return ot;
	while (ot.Day>mTime::DaysofMonth(ot.Year, ot.Month))
	{
		ot.Day -= mTime::DaysofMonth(ot.Year, ot.Month);
		ot.Month++;
		while (ot.Month >= 13)
		{
			ot.Month -= 12;
			ot.Year++;
		}
	}
	ot.updateRawDate();
	return ot;
}
int mTime::transfer(const std::string& ss, int Format)
{
	if (Format == mTime::CompactFormat)
	{
		if (ss.length() != 14) return 0;
		for (int i = 0; i != 14; i++)
		if ((ss[i]<'0') || (ss[i]>'9')) return 0;
		Year = (ss[0] - '0') * 1000 + (ss[1] - '0') * 100 + (ss[2] - '0') * 10 + ss[3] - '0';
		Month = (ss[4] - '0') * 10 + ss[5] - '0';
		if ((Month>12) || (Month<1)) return 0;
		Day = (ss[6] - '0') * 10 + ss[7] - '0';
		if ((Day>mTime::DaysofMonth(Year, Month)) || (Day<1)) return 0;
		Hour = (ss[8] - '0') * 10 + ss[9] - '0';
		if ((Hour>24) || (Hour<0)) return 0;
		if (Hour == 24) Hour = 0;
		Minute = (ss[10] - '0') * 10 + ss[11] - '0';
		if ((Minute>60) || (Minute<0)) return 0;
		if (Minute == 60) Minute = 0;
		Second = (ss[12] - '0') * 10 + ss[13] - '0';
		if ((Second>60) || (Second<0)) return 0;
		if (Second == 60) Second = 0;
		updateRawDate();
	}
	else if (Format == mTime::DateOnlyCompactFormat)
	{
		if (ss.length() != 8) return 0;
		for (int i = 0; i != 8; i++)
		if ((ss[i]<'0') || (ss[i]>'9')) return 0;
		Year = (ss[0] - '0') * 1000 + (ss[1] - '0') * 100 + (ss[2] - '0') * 10 + ss[3] - '0';
		Month = (ss[4] - '0') * 10 + ss[5] - '0';
		if ((Month>12) || (Month<1)) return 0;
		Day = (ss[6] - '0') * 10 + ss[7] - '0';
		if ((Day>mTime::DaysofMonth(Year, Month)) || (Day<1)) return 0;
		Hour = Minute = Second = 0;
		updateRawDate();
	}
	return 1;
}
std::string mTime::toString(int Format) const
{
	std::string str;
	if (Format == mTime::CompactFormat)
	{
		char ch[255];

		sprintf_s(ch, "%d", Year);
		str = ch;

		if (Month<10) sprintf_s(ch, "0%d", Month);
		else sprintf_s(ch, "%d", Month);
		str.append(ch);

		sprintf_s(ch, "%d", Day);
		if (Day<10) str.append("0");
		str.append(ch);

		sprintf_s(ch, "%d", Hour);
		if (Hour<10) str.append("0");
		str.append(ch);

		sprintf_s(ch, "%d", Minute);
		if (Minute<10) str.append("0");
		str.append(ch);

		sprintf_s(ch, "%d", Second);
		if (Second<10) str.append("0");
		str.append(ch);
	}
	else	if (Format == mTime::StandardFormat)
	{
		char ch[255];

		sprintf_s(ch, "%d/", Year);
		str = ch;

		if (Month<10) sprintf_s(ch, "0%d/", Month);
		else sprintf_s(ch, "%d/", Month);
		str.append(ch);

		sprintf_s(ch, "%d , ", Day);
		if (Day<10) str.append("0");
		str.append(ch);

		sprintf_s(ch, "%d:", Hour);
		if (Hour<10) str.append("0");
		str.append(ch);

		sprintf_s(ch, "%d:", Minute);
		if (Minute<10) str.append("0");
		str.append(ch);

		sprintf_s(ch, "%d", Second);
		if (Second<10) str.append("0");
		str.append(ch);
	}
	else	if (Format == mTime::DateOnlyStandardFormat)
	{
		char ch[255];

		sprintf_s(ch, "%d/", Year);
		str = ch;

		if (Month<10) sprintf_s(ch, "0%d/", Month);
		else sprintf_s(ch, "%d/", Month);
		str.append(ch);

		sprintf_s(ch, "%d", Day);
		if (Day<10) str.append("0");
		str.append(ch);
	}
	else if (Format == mTime::DateOnlyCompactFormat)
	{
		char ch[255];

		sprintf_s(ch, "%d", Year);
		str = ch;

		if (Month<10) sprintf_s(ch, "0%d", Month);
		else sprintf_s(ch, "%d", Month);
		str.append(ch);

		sprintf_s(ch, "%d", Day);
		if (Day<10) str.append("0");
		str.append(ch);
	}
	return str;
}
void mTime::addDays(int d)
{
	if (d<0) d = 0;
	Day += d;
	while (Day>DaysofMonth(Year, Month))
	{
		Day -= mTime::DaysofMonth(Year, Month);
		Month++;
		while (Month >= 13)
		{
			Month -= 12;
			Year++;
		}
	}
	updateRawDate();
}
void mTime::minusDays(int d)
{
	if (d<0) d = 0;

	while (d>0)
	{
		if (Day == 1)
		{
			Month--;
			if (Month == 0)
			{
				Month = 12;
				Year--;
			}
			Day = mTime::DaysofMonth(Year, Month);
			d--;
		}
		else
		{
			if (d >= Day - 1)
			{
				d -= Day - 1;
				Day = 1;
			}
			else
			{
				Day -= d;
				d = 0;
			}
		}
	}
	updateRawDate();
}


std::ostream& operator << (std::ostream &osm, mTime time)
{
	osm << time.toString();
	return osm;
}
mTime mTime::operator + (long long int it)const
{
	if (it <= 0) return *this;
	mTime ot(*this);
	long long int tmp = ot.Second + it;
	//ot.Second+=it;
	if (tmp>59)
	{
		ot.Second = tmp % 60;
		tmp /= 60;
	}
	else
	{
		ot.Second = (int)tmp;
		return ot;
	}
	if (tmp>59)
	{
		//ot.Hour+=ot.Minute/60;
		ot.Minute = (int)(tmp % 60);
		tmp /= 60;
	}
	else
	{
		ot.Minute = (int)tmp;
		return ot;
	}
	if (tmp>23)
	{
		ot.Hour = (int)(tmp % 24);
		tmp /= 24;
	}
	else
	{
		ot.Hour = (int)tmp;
		return ot;
	}
	while (tmp>mTime::DaysofMonth(ot.Year, ot.Month))
	{
		tmp -= mTime::DaysofMonth(ot.Year, ot.Month);
		ot.Month++;
		while (ot.Month >= 13)
		{
			ot.Month -= 12;
			ot.Year++;
		}
	}
	ot.Day = (int)tmp;
	ot.updateRawDate();
	return ot;
}


long long int mTime::operator - (const mTime& ot)const
{
	if (*this<ot) return -(ot - *this);
	if (*this == ot) return 0;
	long long int ans = 0;
	mTime op1(*this), op2(ot);
	while (op2 + 86400 <= op1)
	{
		ans += 86400;
		op2.addDays(1);
	}
	if (op2.Day == op1.Day)
		ans += (op1.Hour * 3600 + op1.Minute * 60 + op1.Second) - (op2.Hour * 3600 + op2.Minute * 60 + op2.Second);
	else
		ans += (op1.Hour * 3600 + op1.Minute * 60 + op1.Second) - (op2.Hour * 3600 + op2.Minute * 60 + op2.Second) + 86400;
	return ans;
}

mTime mTime::StringtoTime(const std::string& ss, int Format)
{
	mTime ans;

	if (Format == mTime::CompactFormat)
	{
		if (ss.length() != 14) return ans;
		for (int i = 0; i != 14; i++)
		if ((ss[i]<'0') || (ss[i]>'9')) return ans;
		ans.Year = (ss[0] - '0') * 1000 + (ss[1] - '0') * 100 + (ss[2] - '0') * 10 + ss[3] - '0';
		ans.Month = (ss[4] - '0') * 10 + ss[5] - '0';
		if ((ans.Month>12) || (ans.Month<1))
		{
			ans.Month = 1;
			return ans;
		}
		ans.Day = (ss[6] - '0') * 10 + ss[7] - '0';
		if ((ans.Day>mTime::DaysofMonth(ans.Year, ans.Month)) || (ans.Day<1))
		{
			ans.Day = 1;
			return ans;
		}
		ans.Hour = (ss[8] - '0') * 10 + ss[9] - '0';
		if ((ans.Hour>24) || (ans.Hour<0))
		{
			ans.Hour = 0;
			return ans;
		}
		if (ans.Hour == 24) ans.Hour = 0;
		ans.Minute = (ss[10] - '0') * 10 + ss[11] - '0';
		if ((ans.Minute>60) || (ans.Minute<0))
		{
			ans.Minute = 0;
			return ans;
		}
		if (ans.Minute == 60) ans.Minute = 0;

		ans.Second = (ss[12] - '0') * 10 + ss[13] - '0';
		if ((ans.Second>60) || (ans.Second<0))
		{
			ans.Second = 0;
			return ans;
		}
		if (ans.Second == 60) ans.Second = 0;

		ans.updateRawDate();
	}
	else if (Format == mTime::DateOnlyCompactFormat)
	{
		if (ss.length() != 8) return ans;
		for (int i = 0; i != 8; i++)
		if ((ss[i]<'0') || (ss[i]>'9')) return ans;
		ans.Year = (ss[0] - '0') * 1000 + (ss[1] - '0') * 100 + (ss[2] - '0') * 10 + ss[3] - '0';
		ans.Month = (ss[4] - '0') * 10 + ss[5] - '0';
		if ((ans.Month>12) || (ans.Month<1))
		{
			ans.Month = 1;
			return ans;
		}
		ans.Day = (ss[6] - '0') * 10 + ss[7] - '0';
		if ((ans.Day>mTime::DaysofMonth(ans.Year, ans.Month)) || (ans.Day<1))
		{
			ans.Day = 1;
			return ans;
		}
		ans.Hour = 0;
		ans.Minute = 0;
		ans.Second = 0;
		ans.updateRawDate();
	}

	return ans;
}

mTime mTime::operator - (int i)const
{
	if (i < 1) return *this;
	mTime tmp(*this);
	while (i >= 86400)
	{
		i -= 86400;
		tmp.minusDays(1);
	}
	while (i >= 3600)
	{
		i -= 3600;
		tmp.Hour--;
		if (tmp.Hour == -1)
		{
			tmp.Hour = 23;
			tmp.minusDays(1);
		}
	}
	while (i >= 60)
	{
		i -= 60;
		tmp.Minute--;
		if (tmp.Minute == -1)
		{
			tmp.Minute = 59;
			tmp.Hour--;
			if (tmp.Hour == -1)
			{
				tmp.Hour = 23;
				tmp.minusDays(1);
			}
		}
	}
	while (i > 0)
	{
		i--;
		tmp.Second--;
		if (tmp.Second == -1)
		{
			tmp.Second = 59;
			tmp.Minute--;
			if (tmp.Minute == -1)
			{
				tmp.Minute = 59;
				tmp.Hour--;
				if (tmp.Hour == -1)
				{
					tmp.Hour = 23;
					tmp.minusDays(1);
				}
			}

		}
	}
	tmp.updateRawDate();
	return tmp;
}
