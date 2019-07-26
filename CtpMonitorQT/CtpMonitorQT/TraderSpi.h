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
		///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
		virtual void OnFrontConnected();
		virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///��¼������Ӧ
		virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///Ͷ���߽�����ȷ����Ӧ
		virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///�����ѯ��Լ��Ӧ
		virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		//�����ѯ��֤����Ӧ��
		virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
		virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///�����ѯ�ʽ��˻���Ӧ
		virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///�����ѯͶ���ֲ߳���Ӧ
		virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		///����¼��������Ӧ
		virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///ִ������¼��������Ӧ
		virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///ѯ��¼��������Ӧ
		virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///����¼��������Ӧ
		virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///��������������Ӧ
		virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///ִ���������������Ӧ
		virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///���۲���������Ӧ
		virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///����Ӧ��
		virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
		virtual void OnFrontDisconnected(int nReason);

		///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
		virtual void OnHeartBeatWarning(int nTimeLapse);

		///����֪ͨ
		virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

		///ִ������֪ͨ
		virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder);

		///ѯ��֪ͨ
		virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

		///����֪ͨ
		virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote);

		///�ɽ�֪ͨ
		virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

		///�����ѯ������Ӧ
		virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID);

		///�����ѯ������Ӧ
		virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);

	     virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
		
	 void ReqQryInstrumentCommissionRate();
		static bool CTP_IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
		static bool CTP_IsFlowControl(int iResult);
		void  setTdApi(CThostFtdcTraderApi* tdapi);
		int     FRONT_ID;    //ǰ�ñ��
		int   SESSION_ID;    //�Ự���
		int g_iMarket;
		void ReqQryTradingAccount();
		void FllowTrade(CThostFtdcTradeField pTrade,int multi=1); //���ٽ���
		void FllowOrder(CThostFtdcOrderField pOrder, int multi = 1); //���ҵ�
		void SendOrder(CThostFtdcInputOrderField order);
		void SendAction(CThostFtdcInputOrderActionField action);
		map<string, CThostFtdcInstrumentField> instrumentmap;
		void ReqQryInvestorPositionCombineDetail();
	private:
		///�û���¼����
		void ReqUserLogin();
		///Ͷ���߽�����ȷ��
		void ReqSettlementInfoConfirm();
		///�����ѯ��Լ
		void ReqQryInstrument();
		///�����ѯ�ʽ��˻�
		///�����ѯͶ���ֲ߳�
		void ReqAuthenticate();
		void ReqQryInvestorPosition();
		void  ReqQryInvestor(); //��ѯͶ����
		void ReqQryInvestorPositionDetail();
		void ReqQryOrder();
		void ReqQryTrade();
		// �Ƿ��յ��ɹ�����Ӧ
		bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
		int FRONTID;
		int  LIMIT_PRICE;    // �۸�
		char  DIRECTION;    // ��������
														// �Ự����
		
		char   ORDER_REF[1024];    //��������
		string    BROKER_ID;                // ���͹�˾����
		string   INVESTOR_ID;           // Ͷ���ߴ���
		string     PASSWORD;        // �û����룬
		string INSTRUMENT_ID;
		int iRequestID;
		CThostFtdcTraderApi* tdapi;
		int g_iOrderRef;
		bool isErrPassword;//����Ƿ�Ϊ�������ر�
	
		// �Ƿ��ҵı����ر�
		// �Ƿ��ҵ�ִ������ر�
		// �Ƿ��ҵı���
		// �Ƿ����ڽ��׵ı���
		// �Ƿ�δ������ִ������
		// �Ƿ�δ�����ı���
        

	};

}
