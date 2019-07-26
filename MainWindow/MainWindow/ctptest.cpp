#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include "CustomMdSpi.h"
#include "CustomTradeSpi.h"
#include "TickToKlineHelper.h"

#include "MainWindow.h"
#include <QtWidgets/QApplication>

//int main(int argc, char *argv[])
//{
//	QApplication a(argc, argv);
//	MainWindow w = new MainWindow;
//	w.sizeHint();
//	/*w.setMinimumSize(300, 300);
//	w.setMaximumSize(500, 500);*/
//	w.show();
//	return a.exec();
//
//}


using namespace std;

// 链接库
//#pragma comment (lib, "thostmduserapi.lib")
//#pragma comment (lib, "thosttraderapi.lib")

// ---- 全局变量 ---- //
// 公共参数
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "147553";                      // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "lijiaqi_557";                     // 投资者密码

CThostFtdcMdApi *g_pMdUserApi = nullptr;                           // 行情指针
char gMdFrontAddr[] = "tcp://180.168.146.187:10111";
//char gMdFrontAddr[] = "tcp://180.168.146.187:10101";               // 模拟行情前置地址
char *g_pInstrumentID[] = { "TF1909", "zn1908", "cs1909", "CF909" }; // 行情合约代码列表，中、上、大、郑交易所各选一种
int instrumentNum = 4;                                             // 行情合约订阅数量
//unordered_map<string, TickToKlineHelper> g_KlineHash;              // 不同合约的k线存储表

																   // 交易参数
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;                    // 交易指针															   //char gTradeFrontAddr[] = "tcp://180.168.146.187:10130";            // 模拟交易前置地址
char gTradeFrontAddr[] = "tcp://180.168.146.187:10101";
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "zn1908";        // 所交易的合约代码
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // 买卖方向
TThostFtdcPriceType gLimitPrice = 19295 + 20;                           // 交易价格



int main(int argc, char *argv[])
{
	//// 账号密码
	//cout << "请输入账号： ";
	//scanf("%s", gInvesterID);
	//cout << "请输入密码： ";
	//scanf("%s", gInvesterPassword);

	// 初始化行情线程
	cout << "初始化行情..." << endl;
	//cout << "g_pMdUserApi before" << g_pMdUserApi << endl;
	g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();   // 创建行情实例
	//cout << "g_pMdUserApi after" << g_pMdUserApi << endl;
	CThostFtdcMdSpi *pMdUserSpi = new CustomMdSpi;       // 创建行情回调实例
	g_pMdUserApi->RegisterSpi(pMdUserSpi);               // 注册事件类
	g_pMdUserApi->RegisterFront(gMdFrontAddr);           // 设置行情前置地址
	g_pMdUserApi->Init();                                // 连接运行



														 // 初始化交易线程
	cout << "初始化交易..." << endl;
	g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi("\\"); // 创建交易实例
																	  //CThostFtdcTraderSpi *pTradeSpi = new CustomTradeSpi;
	CustomTradeSpi *pTradeSpi = new CustomTradeSpi;               // 创建交易回调实例
	g_pTradeUserApi->RegisterSpi(pTradeSpi);                      // 注册事件类
	g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // 订阅公共流
	g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // 订阅私有流
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr);              // 设置交易前置地址
	g_pTradeUserApi->Init();                                      // 连接运行

	QApplication a(argc, argv);
	MainWindow w = new MainWindow;
	w.sizeHint();

	w.show();
																  // 等到线程退出
	/*g_pMdUserApi->Join();
	delete pMdUserSpi;
	g_pMdUserApi->Release();

	g_pTradeUserApi->Join();
	delete pTradeSpi;
	g_pTradeUserApi->Release();*/

	//getchar();

	
	return a.exec();

	// 转换本地k线数据
	//TickToKlineHelper tickToKlineHelper;
	//tickToKlineHelper.KLineFromLocalData("market_data.csv", "K_line_data.csv");

	
	
}