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
		string usercname; //��������
		string address;
		string password;
		string brokerid;
		string updatetime;
		string authorcode;
		string productinfo;
		string appid;
		float staticright; //��̬Ȩ��
		float dynicright; //��̬Ȩ��
		float margin;   //��֤��ռ��
		float deposti; //�����
		float  withdraw; //������
		float postionprofit; //�ֲ�ӯ��
		float closeprofit; //ƽ��ӯ��
		float availablemoney; //�����ʽ�
		float  riskrate;  //���ն�
		bool  connectstatus;//����״̬
		bool monitorselected; //���״̬�Ƿ�ѡ����
		bool tradeseletcted; //�����Ƿ�ѡ����
		
		list<CThostFtdcOrderField> orderlist; //����״̬
		list<CThostFtdcInvestorPositionDetailField> postionlist; //�ֲ�״̬
		list<CThostFtdcTradeField> tradelist; //�ɽ����б�
		list<CThostFtdcInvestorPositionCombineDetailField> postioncom;//��ϳֲ���ϸ

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