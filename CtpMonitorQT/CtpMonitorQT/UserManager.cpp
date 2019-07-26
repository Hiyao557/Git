#include "UserManager.h"
#include "json.hpp"
#include <string>  
#include <fstream>  
#include <sstream> 
#include <direct.h>
#include <io.h>
#include "TimeTool.h"
using namespace HxTool;
using namespace nlohmann;
using namespace std;
using namespace Monitor;
shared_ptr<UserManager> UserManager::usermanager = nullptr;

Monitor::UserManager::UserManager()
{
	std::ifstream t("monitorconfig.json");
	std::stringstream buffer;
	buffer << t.rdbuf();
	t.close();
	std::string contents(buffer.str()); //采用json 格式 简单一点   //去除掉\n 换行符号
	//for (auto it = contents.begin(); it != contents.end(); ++it)
	//{
	//	if (*it == '\n')
	//	{
	//		contents.erase(it);
	//	}
	//}
	  json j2 = json::parse(contents);
	  auto users = j2["users"];
	 
	  for(auto user: users) 
	  {
		  CtpUser *ctpuser = new CtpUser();
		  ctpuser->address = user["address"].get<string>();
		  ctpuser->brokerid = user["brokerid"].get<string>();
		  ctpuser->userid = user["userid"].get<string>();
		  ctpuser->password = user["password"].get<string>();
		  ctpuser->username = user["username"].get<string>();
		  if (user.count("authorcode") > 0) {
			  ctpuser->authorcode = user["authorcode"].get<string>();
		  }
		  if (user.count("productinfo") > 0) {
			  ctpuser->productinfo = user["productinfo"].get<string>();
		  }
		  if (user.count("appid") > 0) {
			  ctpuser->appid = user["appid"].get<string>();
		  }
		  mapuser.insert(pair<string, CtpUser*>(ctpuser->userid,ctpuser));
	  
	  }



	  }

void Monitor::UserManager::UpdateUser(string userid, CtpUser& user)
{
	//memcpy(this->mapuser[userid],&user,sizeof(CtpUser));

	// 写日志 

	json j;
	j["userid"] = userid;
	j["username"] = user.username;
	j["dynicright"] = user.dynicright;
	j["margin"] = user.margin;
	j["time"] = user.updatetime;
	if (0 != _mkdir("accountlog") && (errno != EEXIST)) {
		return;
	}

	string date = TimeTool::GetStrCurrentTime("%Y%m%d");
	this->lock.lock();
	ofstream fout("./accountlog/"+date+".json",ios::app);     //创建一个data.txt的文件
	if (fout.is_open()) {

		fout << j << endl;  //将变量的值写入文件
		fout.close();                  //关闭文件
	     
	}
	this->lock.unlock();
	
}

void Monitor::UserManager::SetMonitorSelectStatus(string usreid, bool flag)
{
	if (this->mapuser.count(usreid) > 0) {
		this->mapuser[usreid]->monitorselected = flag;
	}
}

void Monitor::UserManager::SetTradeSelectStatus(string userid, bool flag)
{
	if (this->mapuser.count(userid) > 0) {
		this->mapuser[userid]->tradeseletcted = flag;
	}
}

list<string> Monitor::UserManager::GetMonitorSelectAccountID()
{
	list<string> monitoraccountlist;
	for (auto user : this->mapuser)
	{
		if (user.second->monitorselected) {
			monitoraccountlist.push_back(user.first);
	 }
	  }
	return monitoraccountlist;
}

bool Monitor::UserManager::IsMonitorSelect(string userid)
{
	for (auto user : this->mapuser)
	{
		if (user.second->userid.compare(userid)==0&&user.second->monitorselected) {
			return true;

		}
	}
	return false;
}

list<string> Monitor::UserManager::GetTradeSelectStatus()
{
	list<string> tradeselectlist;
	for (auto user : this->mapuser)
	{
		if (user.second->tradeseletcted) {
			tradeselectlist.push_back(user.first);
		}
	}
	return tradeselectlist;
}

shared_ptr<UserManager> Monitor::UserManager::GetInstance()
{
	if (usermanager == nullptr) {
		usermanager=make_shared<UserManager>();
	}
	return usermanager;
}

map<string,CtpUser*> Monitor::UserManager::GetUserMap()
{
	
	return mapuser;
}

CtpUser* Monitor::UserManager::GetUser(string userid)
{
	return mapuser[userid];
}


Monitor::UserManager::~UserManager()
{
	//
	for (auto it : mapuser) {

		delete it.second;
	}

}
