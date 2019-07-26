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

enum  RuntimeStatus {  //ctp runting ��״̬
	rt_uninit,  //��û�г�ʼ��
	rt_inited,//�Ѿ���ʼ����
	rt_start, //���ʼ
	rt_starting,//���ڿ�ʼ
	rt_running, // ��������
	rt_stop,
	rt_stoping,//����ֹͣ
	rt_stoped  // �Ѿ�ֹͣ
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
	map<string, CTraderSpi*> userspimap;  //user��api ��ӳ��
private:
	     static shared_ptr<CtpRuntime> instance;
		map<string, CThostFtdcTraderApi*> userapimap; //user��api��ӳ�� 

		
		vector<Order> vect_orderdelay;
		bool istimethreadruning;
		thread* timemakerthead;// ʱ���߳�ÿ5��ȥˢ��һ�� �˺���Ϣ 
public:
	void Start();
	void Stop();
	void FreshAccount();
	void FreshPostionComb();
	void SendOrder(CThostFtdcInputOrderField orderinput);
	void SendOrderList(list<CThostFtdcInputOrderField> orderlist);
	void SendAction(list<CThostFtdcInputOrderActionField> list_action);


};