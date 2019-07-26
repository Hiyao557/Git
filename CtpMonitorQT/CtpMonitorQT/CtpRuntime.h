#pragma once
#include <map>
#include "ThostFtdcTraderApi.h"
#include "TraderSpi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include "TraderSpi.h"
#include <list>
using namespace CTP;
using namespace std;

enum  RuntimeStatus {  //ctp runting 的状态
	rt_uninit,  //还没有初始化
	rt_inited,//已经初始化了
	rt_start, //命令开始
	rt_starting,//正在开始
	rt_running, // 正在运行
	rt_stop,
	rt_stoping,//正在停止
	rt_stoped  // 已经停止
};
struct Order {

	time_t excutetime;  //
	CThostFtdcOrderField order;
	string userid;
};
class CtpRuntime {
public:
	void TimeMaker();
	static shared_ptr<CtpRuntime> GetInstance();
	map<string, CTraderSpi*> userspimap;  //user和api 的映射
private:
	     static shared_ptr<CtpRuntime> instance;
		map<string, CThostFtdcTraderApi*> userapimap; //user和api的映射 

		
		vector<Order> vect_orderdelay;
		bool istimethreadruning;
		thread* timemakerthead;// 时间线程每5秒去刷新一次 账号信息 
public:
	void Start();
	void Stop();
	void FreshAccount();
	void FreshPostionComb();
	void SendOrder(CThostFtdcInputOrderField orderinput);
	void SendOrderList(list<CThostFtdcInputOrderField> orderlist);
	void SendAction(list<CThostFtdcInputOrderActionField> list_action);


};