#pragma once
// �����ṩһϵ�е�ʱ��������� �Թ����ʹ��  ���Ǹ��಻Ӧ���ڲ�����ʹ�� �����л�ȡʱ������timer ���ȡ ��Ϊ�������ʱ�������������ڵ�����
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
		��str װ��Ϊtm
		*/
		static tm     GetTmFromStr(string time, string format = "%Y-%m-%d %H:%M:%S");
		/*
		��str ת��Ϊtime_t
		*/
		static time_t GetTimeFromStr(string time, string format = "%Y-%m-%d %H:%M:%S");
		static tm   GetTmTime(time_t t);

	};

}