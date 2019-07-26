#include "HxEventEngine.h"

                       //包含头文件
#include<stdlib.h>
using namespace CTPTOOL;
void  HxDealer::putEvent(eventstruct event) {
	
	if (this->status==HxDealerStatus::unstart)
		this->start();
	cm.lock();
	this->eventlist.push_back(event);
	cm.unlock();
}
HxDealer::HxDealer() {
	this->status = HxDealerStatus::unstart;
	t = NULL;

}

	HxDealer::~HxDealer() {
		if (this->status == HxDealerStatus::running) {
			this->status = HxDealerStatus::stop;
			while (this->status != HxDealerStatus::stoped) {
				std::this_thread::yield();

			}
		}
		if (t != NULL)//把线程停下来 这个地方还需要完善
		{
			if (t->joinable())
				t->join();
			delete t;
			t = NULL;
		}
//		delete t;
		

	}
void HxDealer::start() {
	if (this->status==HxDealerStatus::unstart) {
		t = new thread(&HxDealer::eventloop,this);
		this->status = HxDealerStatus::running;
	
	}

}
void HxDealer::eventloop() {
	
	while (true) {  
		if (this->status== HxDealerStatus::stop) {
			this->status = HxDealerStatus::stoped;
			break;
		}
		if (eventlist.empty()) {  //增加判断是否是empty 在有值的情况下加快速度　
			std::this_thread::yield();
		}
		eventstruct event;
		bool has = false;
		cm.lock();
		if (!eventlist.empty()) {
			 event = this->eventlist.front();
			eventlist.pop_front();
			if (eventlist.size() > 10 && event.dropable)
			{
				int j = 0;
			}else
			{
				has = true;//减少锁时间
			
			}
		}
		cm.unlock();

		try {
			if (has) {
				this->OnHxEvent(event);
				has = false;
			}
		}
		catch (double) {

		}
		
	}
}

bool HxEventEngine::stop = false;
HxEventEngine::HxEventEngine()
{


	
}
void HxEventEngine::Adddealer(HxDealer* dealer) {
	cm.lock();
	this->dealerlist.push_back(dealer);
	cm.unlock();
}
void HxEventEngine::Movedealer(HxDealer* dealer) {
	cm.lock();
	vector<HxDealer * >::iterator it;
	for (it = this->dealerlist.begin(); it != this->dealerlist.end();) {

		if (*it == dealer) {
			//dealer->stop = true;
			it=this->dealerlist.erase(it);
		}
		else
			++it;
	}
	cm.unlock();
}


void HxEventEngine::MoveAlldealer() {
	cm.lock();
	this->dealerlist.clear();
	cm.unlock();
}
void HxEventEngine::operator()(eventstruct event) {

	if (stop)
		return;
	cm.lock();
	vector<HxDealer * >::iterator it;
	for ( it = this->dealerlist.begin(); it != this->dealerlist.end(); ++it) {
	 (*it)->putEvent(event);
	}
	cm.unlock();
}
HxEventEngine::~HxEventEngine() {
	
}

