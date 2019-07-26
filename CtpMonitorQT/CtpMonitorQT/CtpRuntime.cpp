#include "CtpRuntime.h"
#include <direct.h>
#include <io.h>
#include "UserManager.h"
#include <string>
#include <ctime>
#include <random>
using namespace Monitor;
using namespace std;
using namespace CTP;
using std::default_random_engine;
using std::normal_distribution;

shared_ptr<CtpRuntime> CtpRuntime::instance = nullptr;

void CtpRuntime::Start()
{
	
	map<string, CtpUser*> vectoruser = UserManager::GetInstance()->GetUserMap();
	for (auto it: vectoruser) {
		auto ctpuser = it.second;
		string path = "trader\\" + ctpuser->userid+"\\";
		if (0 != _mkdir("trader") && (errno != EEXIST)) {
			continue;
		}
		if ((0 != _mkdir(path.c_str())) && (errno != EEXIST))
		{
			continue;
		}
		CThostFtdcTraderApi* pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi(path.c_str());            // 创建UserApi
		CTraderSpi*  pUserSpi = new CTraderSpi((char*)ctpuser->brokerid.c_str(),ctpuser->userid, ctpuser->password);
		((CTraderSpi*)pUserSpi)->setTdApi(pTraderApi);
		pTraderApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);            // 注册事件类
		pTraderApi->SubscribePublicTopic(THOST_TERT_QUICK);                // 注册公有流
		pTraderApi->SubscribePrivateTopic(THOST_TERT_QUICK);                // 注册私有流
		pTraderApi->RegisterFront((char*)(ctpuser->address.c_str()));
		pTraderApi->Init();
		userapimap.insert(std::pair<string, CThostFtdcTraderApi*>(ctpuser->userid, pTraderApi));
		userspimap.insert(std::pair<string, CTraderSpi*>(ctpuser->userid,pUserSpi));
	}
	this->timemakerthead = new thread(&CtpRuntime::TimeMaker, this);

	// 开启一条线程 每个5秒重新刷新一次


}


void CtpRuntime::TimeMaker() {
	istimethreadruning = true;

	while (this->istimethreadruning == true) {
		time_t timep;
		time(&timep);
		//timep = timep 
		tm t = *localtime(&timep);
		this_thread::sleep_for(std::chrono::seconds(30));
		if (t.tm_hour > 15 && t.tm_hour < 21)
			continue;
		if (t.tm_hour > 3 && t.tm_hour < 9)
			continue;
		for (auto it = userspimap.begin(); it != userspimap.end(); it++) {
			it->second->ReqQryTradingAccount();
		}
	


	}
// 来看看主账号是否有下单 如果有下单 跟随
		/** if (OrderFllow::GetInstance()->HasTrade()) {
		auto trader=OrderFllow::GetInstance()->PoPTrade();
		for (auto it = userspimap.begin(); it != userspimap.end(); it++) {
			CtpUser user = UserManager::GetInstance()->GetUserMap()[it->first];
			 //if (user.ismain)
				continue;
			//	it->second->FllowTrade(trader, user.multi);
			}
		}
		if (OrderFllow::GetInstance()->HasOrder()) {
			auto order = OrderFllow::GetInstance()->PoPOrder();
			int a = 1;
				for (auto it = userspimap.begin(); it != userspimap.end(); it++) {
					CtpUser user = UserManager::GetInstance()->GetUserMap()[it->first];
					if (user.ismain)
						continue;
					if (UserManager::GetInstance()->followdelay == 0) {  //如果要求零延时
						it->second->FllowOrder(order, user.multi);  //直接下单
					}else{   //如果有延时
						Order order1;
						memset(&order1, 0, sizeof(Order));
						memcpy(&order1.order, &order, sizeof(CThostFtdcOrderField));
						if (UserManager::GetInstance()->israndom) {
							default_random_engine e;
							uniform_real_distribution<double> u(0, UserManager::GetInstance()->followdelay*a);
						//	normal_distribution<> n(UserManager::GetInstance()->followdelay*a, 1.5);
							int j = u(e);
							order1.excutetime = std::time(0) + UserManager::GetInstance()->followdelay*j;
						}
						else {
							order1.excutetime = std::time(0) + UserManager::GetInstance()->followdelay*a;
						}
						a++;
						order1.userid = user.userid;
						this->vect_orderdelay.push_back(order1);
				}
			}

		}
		for (auto it = this->vect_orderdelay.begin(); it != vect_orderdelay.end();) {
			if (it->excutetime < std::time(0)) { //他的执行时间小于单前时间 执行
				CtpUser user = UserManager::GetInstance()->GetUserMap()[it->userid];
				this->userspimap[it->userid]->FllowOrder(it->order, user.multi);
				it = this->vect_orderdelay.erase(it);
			}
			else {
				++it;
			}

		}
	}**/
}






shared_ptr<CtpRuntime> CtpRuntime::GetInstance() {

	if (instance == nullptr) {
		instance = make_shared<CtpRuntime>();
	}
	return instance;

}
void CtpRuntime::Stop()
{
	this->istimethreadruning = false;
	this_thread::sleep_for(std::chrono::seconds(1));
	for (auto it = userapimap.begin(); it != userapimap.end(); it++) {

		it->second->RegisterSpi(NULL);
		it->second->Release();
	}
	for (auto it = userspimap.begin(); it != userspimap.end(); it++)
	{
		delete it->second;

	}
	//delete this->timemakerthead;
}
void CtpRuntime::FreshAccount()
{
	list<string> selectedids = UserManager::GetInstance()->GetMonitorSelectAccountID();

	for (string userid : selectedids) {
		//strcpy(orderinput.)
		this->userspimap[userid]->ReqQryTradingAccount();
	}
}
void CtpRuntime::FreshPostionComb()
{
	list<string> selectedids = UserManager::GetInstance()->GetMonitorSelectAccountID();

	for (string userid : selectedids) {
		//strcpy(orderinput.)
		this->userspimap[userid]->ReqQryInvestorPositionCombineDetail();
	}

}

void CtpRuntime::SendOrder(CThostFtdcInputOrderField orderinput)
{
	// 下单
list<string> selectedids=UserManager::GetInstance()->GetTradeSelectStatus();

for (string userid : selectedids) {
	//strcpy(orderinput.)
	this->userspimap[userid]->SendOrder(orderinput);

}
}

void CtpRuntime::SendOrderList(list<CThostFtdcInputOrderField> orderlist)
{
	// 下单
	list<string> selectedids = UserManager::GetInstance()->GetTradeSelectStatus();

	for (auto orderinput : orderlist) {
		for (string userid : selectedids) {
			//strcpy(orderinput.)
			this->userspimap[userid]->SendOrder(orderinput);

		}

	}




}





void CtpRuntime::SendAction(list<CThostFtdcInputOrderActionField> list_action)
{

	for (auto action : list_action) {

		this->userspimap[action.UserID]->SendAction(action);

	}


}
