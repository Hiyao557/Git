#include "TimeTool.h"
#include <ctime>  
#include <string>  
#include <sstream>
using namespace std;
string HxTool::TimeTool::GetStrCurrentTime(string format)
{
	std::string stime;
	std::stringstream strtime;
	char tAll[255];
	time_t currenttimet = std::time(0);
	std::strftime(tAll, sizeof(tAll), format.c_str(), std::localtime(&currenttimet));
	strtime << tAll;
	stime = strtime.str();
	return stime;
}

tm HxTool::TimeTool::GetTmCurrentTime()
{
	time_t timep = std::time(0);
	tm t = *localtime(&timep);
	return tm();
}

string HxTool::TimeTool::GetStrTime(time_t t, string format)
{
	std::string stime;
	std::stringstream strtime;
	char tAll[255];
	std::strftime(tAll, sizeof(tAll), format.c_str(), std::localtime(&t));
	strtime << tAll;
	stime = strtime.str();
	return stime;
}

tm HxTool::TimeTool::GetTmFromStr(string time, string format)
{
	struct tm tm1;
	time_t time1;
	format = format.replace(format.find("Y"), 1, "d");
	format = format.replace(format.find("m"), 1, "d");
	format = format.replace(format.find("H"), 1, "d");
	format = format.replace(format.find("M"), 1, "d");
	format = format.replace(format.find("S"), 1, "d");
	//将formt 里面的字母全部替换成d
	int i = sscanf(time.c_str(), format.c_str(),
		&(tm1.tm_year),
		&(tm1.tm_mon),
		&(tm1.tm_mday),
		&(tm1.tm_hour),
		&(tm1.tm_min),
		&(tm1.tm_sec),
		&(tm1.tm_wday),
		&(tm1.tm_yday));
	tm1.tm_year -= 1900;
	tm1.tm_mon--;
	tm1.tm_isdst = -1;
	time1 = mktime(&tm1);
	//需要实现
	return tm1;
}

time_t HxTool::TimeTool::GetTimeFromStr(string time, string format)
{
	struct tm tm1;
	time_t time1;
	format = format.replace(format.find("Y"), 1, "d");
	format = format.replace(format.find("m"), 1, "d");
	format = format.replace(format.find("H"), 1, "d");
	format = format.replace(format.find("M"), 1, "d");
	format = format.replace(format.find("S"), 1, "d");


	int i = sscanf(time.c_str(), format.c_str(),
		&(tm1.tm_year),
		&(tm1.tm_mon),
		&(tm1.tm_mday),
		&(tm1.tm_hour),
		&(tm1.tm_min),
		&(tm1.tm_sec),
		&(tm1.tm_wday),
		&(tm1.tm_yday));

	tm1.tm_year -= 1900;
	tm1.tm_mon--;
	tm1.tm_isdst = -1;
	time1 = mktime(&tm1);

	return time1;
}

tm HxTool::TimeTool::GetTmTime(time_t t)
{

	tm t1 = *localtime(&t);
	return t1;
}
