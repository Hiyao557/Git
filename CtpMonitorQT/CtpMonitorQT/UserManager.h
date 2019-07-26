#pragma once
#include<vector>
#include <memory>
#include<map>
#include<mutex>
#include<list>
#include "ThostFtdcTraderApi.h"
using namespace std;

namespace Monitor {
	///
	struct CtpUser {
		string userid;
		string username;
		string usercname; //中文名称
		string address;
		string password;
		string brokerid;
		string updatetime;
		string authorcode;
		string productinfo;
		string appid;
		float staticright; //静态权益
		float dynicright; //动态权益
		float margin;   //保证金占用
		float deposti; //入金金额
		float  withdraw; //出金金额
		float postionprofit; //持仓盈亏
		float closeprofit; //平仓盈亏
		float availablemoney; //可用资金
		float  riskrate;  //风险度
		bool  connectstatus;//连接状态
		bool monitorselected; //监控状态是否选择了
		bool tradeseletcted; //交易是否选择了
		
		list<CThostFtdcOrderField> orderlist; //单子状态
		list<CThostFtdcInvestorPositionDetailField> postionlist; //持仓状态
		list<CThostFtdcTradeField> tradelist; //成交单列表
		list<CThostFtdcInvestorPositionCombineDetailField> postioncom;//组合持仓明细

	public:CtpUser() {
			userid = "";
			address = "";
			password = "";
			brokerid = "";
			updatetime = "";
			username= "";
			authorcode = "";
			productinfo = "";
			appid = "";
			staticright = 0;
			dynicright = 0;
			margin = 0;
			postionprofit = 0;
			closeprofit = 0;
			availablemoney = 0;
			deposti = 0;
			withdraw = 0;
			riskrate = 0;
			connectstatus = false;
			monitorselected = false;
			tradeseletcted = false;

		};
	};

	 class UserManager {
		 friend class shared_ptr<UserManager>;
	 private:
		 map<string,CtpUser*> mapuser;
		 static shared_ptr<UserManager> usermanager;
		 std::mutex lock;
	 public :
		 UserManager();
		void  UpdateUser(string userid, CtpUser& user);

		void SetMonitorSelectStatus(string usreid, bool flag);
		void SetTradeSelectStatus(string userid, bool flag);
		list<string> GetMonitorSelectAccountID();
		bool IsMonitorSelect(string userid);
		list<string> GetTradeSelectStatus();
		 static shared_ptr<UserManager> GetInstance();
		 map<string, CtpUser*> GetUserMap();
		 CtpUser* GetUser(string userid);
		 virtual ~UserManager();
	};

}