#pragma once
// 该类提供一系列的时间操作函数 以供框架使用  但是该类不应当在策略中使用 策略中获取时间必须从timer 里获取 因为策略里的时间依赖策略所在的容器
//
#include <string>
using namespace std;
namespace HxTool {
	class  TimeTool {

	public:
		static string GetStrCurrentTime(string format = "%Y-%m-%d %H:%M:%S");
		static tm  GetTmCurrentTime();
		static string GetStrTime(time_t t, string format = "%Y-%m-%d %H:%M:%S");
		/*
		将str 装换为tm
		*/
		static tm     GetTmFromStr(string time, string format = "%Y-%m-%d %H:%M:%S");
		/*
		将str 转换为time_t
		*/
		static time_t GetTimeFromStr(string time, string format = "%Y-%m-%d %H:%M:%S");
		static tm   GetTmTime(time_t t);

	};

}