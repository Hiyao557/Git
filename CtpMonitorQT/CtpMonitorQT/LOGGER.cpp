#include "LOGGER.h"
#include <stdarg.h>


using namespace CTPTOOL;
//HxEventEngine LOGGER::hxevent;
shared_ptr<LOGGER> LOGGER::loger = make_shared<LOGGER>();
LOGGER::LOGGER()
{
	logfile = NULL;
	int day = 0;
	memset(buf, 0, sizeof(buf));
}


LOGGER::~LOGGER()
{

	cm.lock();
	if (this->logfile != NULL) {
		fflush(logfile);
		fclose(logfile);
	}
	this->logfile = NULL;
	cm.unlock();
}
void LOGGER::Log(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	this->Log(format, args);
	va_end(args);
}
void LOGGER::Log(const char * format, va_list arg)
{

	cm.lock();
	char LogFilename[64] = { 0 };
	char htime[50];
	char currenttime[50];
	memset(&currenttime, 0, sizeof(currenttime));
	memset(&htime, 0, sizeof(htime));
	tm *p;
	time_t timep;
	time(&timep); /*获得time_t结构的时间，UTC时间*/
	p = localtime(&timep); /*转换为struct tm结构的当地时间*/
	sprintf(htime, "%4d%02d%02d ", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday);
	sprintf(currenttime, "%4d%02d%02d %02d:%02d:%02d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
	sprintf(LogFilename, "ctp_%d_%s.log", strategyid,htime);
	int num;
	//char buf[MAX_LOG_LENGTH];
	//memset(buf, 0, MAX_LOG_LENGTH);
	//FILE * fileLog;
	if (logfile == NULL) {
		logfile = fopen(LogFilename, "a+");
		if (logfile != NULL) {
			memset(buf, 0, sizeof(buf));
			setbuf(logfile, buf);		
		}
		day = p->tm_mday;
	}
	else if(day!=p->tm_mday){//说明日期变化了 应该关闭原来的文件重新打开一个新文件
		if (logfile != NULL) {
			fflush(logfile);
			fclose(logfile);
		}
		logfile = fopen(LogFilename, "a+");
		if (logfile != NULL) {
			memset(buf, 0, sizeof(buf));
			setbuf(logfile, buf);
		}
		day = p->tm_mday;
	}
	num = vsnprintf(buf, MAX_LOG_LENGTH, format, arg);
	eventstruct event;
	memset(&event, 0, sizeof(eventstruct));
	event.type = eventtype::logappend;
	event.message = string(buf);
	hxevent(event);
	if (NULL == logfile)
	{
		printf("%s", buf);
		
	}
	else if (num != fwrite(buf, 1, num, logfile))
	{
		printf("%s", buf);
	}
	cm.unlock();
	//fclose(fileLog);
}
shared_ptr<LOGGER> LOGGER::GetInstance()
{
	//if (LOGGER::loger == nullptr)  //
		//LOGGER::loger = make_shared<LOGGER>();
	return loger;
}
void LOGGER::SetStrategyId(int id) {
	strategyid = id;
}
void LOGGER::CTP_Log(const char * format, ...) {
	

	va_list args;
	va_start(args, format);
	LOGGER::GetInstance()->Log(format, args);
	va_end(args);
	

}