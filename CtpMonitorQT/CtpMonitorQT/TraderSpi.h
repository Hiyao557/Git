#pragma once
#include "ThostFtdcTraderApi.h"
#include<string>
#include "HxEventEngine.h"
#include <map>
using namespace std;
using namespace CTPTOOL;
namespace CTP {
	class CTraderSpi : public CThostFtdcTraderSpi
	{

	public :

		static HxEventEngine event;
	public:
		CTraderSpi();
		CTraderSpi(string BROKER_ID, string INVESTOR_ID, string PASSWORD);
		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		virtual void OnFrontConnected();
		virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///登录请求响应
		virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///投资者结算结果确认响应
		virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询合约响应
		virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		//请求查询保证金率应答
		virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
		virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询资金账户响应
		virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资者持仓响应
		virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///报单录入请求响应
		virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///执行宣告录入请求响应
		virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///询价录入请求响应
		virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///报价录入请求响应
		virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///报单操作请求响应
		virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///执行宣告操作请求响应
		virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///报价操作请求响应
		virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///错误应答
		virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
		virtual void OnFrontDisconnected(int nReason);

		///心跳超时警告。当长时间未收到报文时，该方法被调用。
		virtual void OnHeartBeatWarning(int nTimeLapse);

		///报单通知
		virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

		///执行宣告通知
		virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder);

		///询价通知
		virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

		///报价通知
		virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote);

		///成交通知
		virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

		///请求查询行情响应
		virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID);

		///请求查询报单响应
		virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);

	     virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
		
	 void ReqQryInstrumentCommissionRate();
		static bool CTP_IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
		static bool CTP_IsFlowControl(int iResult);
		void  setTdApi(CThostFtdcTraderApi* tdapi);
		int     FRONT_ID;    //前置编号
		int   SESSION_ID;    //会话编号
		int g_iMarket;
		void ReqQryTradingAccount();
		void FllowTrade(CThostFtdcTradeField pTrade,int multi=1); //跟踪交易
		void FllowOrder(CThostFtdcOrderField pOrder, int multi = 1); //跟挂单
		void SendOrder(CThostFtdcInputOrderField order);
		void SendAction(CThostFtdcInputOrderActionField action);
		map<string, CThostFtdcInstrumentField> instrumentmap;
		void ReqQryInvestorPositionCombineDetail();
	private:
		///用户登录请求
		void ReqUserLogin();
		///投资者结算结果确认
		void ReqSettlementInfoConfirm();
		///请求查询合约
		void ReqQryInstrument();
		///请求查询资金账户
		///请求查询投资者持仓
		void ReqAuthenticate();
		void ReqQryInvestorPosition();
		void  ReqQryInvestor(); //查询投资者
		void ReqQryInvestorPositionDetail();
		void ReqQryOrder();
		void ReqQryTrade();
		// 是否收到成功的响应
		bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
		int FRONTID;
		int  LIMIT_PRICE;    // 价格
		char  DIRECTION;    // 买卖方向
														// 会话参数
		
		char   ORDER_REF[1024];    //报单引用
		string    BROKER_ID;                // 经纪公司代码
		string   INVESTOR_ID;           // 投资者代码
		string     PASSWORD;        // 用户密码，
		string INSTRUMENT_ID;
		int iRequestID;
		CThostFtdcTraderApi* tdapi;
		int g_iOrderRef;
		bool isErrPassword;//标记是否为密码错误回报
	
		// 是否我的报单回报
		// 是否我的执行宣告回报
		// 是否我的报价
		// 是否正在交易的报单
		// 是否未撤销的执行宣告
		// 是否未撤销的报价
        

	};

}
