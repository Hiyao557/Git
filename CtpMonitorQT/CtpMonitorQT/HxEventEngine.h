#pragma once
#include <deque>
#include <thread>
#include<vector>
#include <mutex>
using namespace std;
namespace CTPTOOL {
	enum  eventtype {
		login = 0,
		logappend = 1,
		pricechange = 2,
		accountchange = 3,
		tradelistchange = 4,
		ordelistchange = 5,
		postionchange = 6,
		tick = 7,
		draw = 8,
		bar = 9,//bar�������¼�
		strategystoped = 10,//����ֹͣ�¼�
		mtorderchange = 11,//mtorder �����˱��
		strategystart = 12,  //���������¼�
		instrumentchange=13,
		postioncomchange=14
			
	};

	 enum  HxDealerStatus {
		unstart,
		start,
		starting,
		running,
		stop,
		stoping,
		stoped

	};

	 struct  eventstruct {
		eventtype type;
		string message;
		bool dropable;
		unsigned char data[1000];
	};
	 class  HxDealer {

	public :
		virtual ~HxDealer();
		HxDealer();
	protected :
		virtual void OnHxEvent(eventstruct event) = 0;
		friend class HxEventEngine;
		

	private:
		HxDealerStatus status;
		
		void putEvent(eventstruct event);
		thread* t;
		std::mutex cm;

	
		void eventloop();
		void start();
		
		deque<eventstruct> eventlist;

	};
	 class  HxEventEngine
	{
		//ȫ���¼�����
	public:
		HxEventEngine();		
		void virtual Adddealer(HxDealer * dealer) final;
		void virtual Movedealer(HxDealer * dealer) final;
		void virtual MoveAlldealer() final;
		void virtual operator()(eventstruct event) ;
		virtual ~HxEventEngine();
		static bool stop;
	private :
		std::mutex cm;
		vector<HxDealer *> dealerlist;
	};

}