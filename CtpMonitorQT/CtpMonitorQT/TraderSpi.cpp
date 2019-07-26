#include <iostream>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "TraderSpi.h"
#include <set>
#include "LOGGER.h"
#include "CtpRuntime.h"
//#include "CTPTimer.h"
#include <sstream>
#include <ctime>  
#include "UserManager.h"
#include "TimeTool.h"
#include "json.hpp"
#include <fstream>
using namespace HxTool;
using namespace std;
using namespace CTP;
using namespace CTPTOOL;
using namespace Monitor;
using namespace nlohmann;
// ���ò���
HxEventEngine CTraderSpi::event;

CTraderSpi::CTraderSpi() {
	
}
CTraderSpi::CTraderSpi(string BROKER_ID, string INVESTOR_ID, string PASSWORD) {
	this->BROKER_ID = BROKER_ID;
	this->INVESTOR_ID = INVESTOR_ID;
	this->PASSWORD = PASSWORD;
	this->g_iMarket = 0;
}
void CTraderSpi::setTdApi(CThostFtdcTraderApi* tdapi) {
	this->tdapi = tdapi;

}
bool CTraderSpi::CTP_IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo) {

	if (pRspInfo == NULL) {
		return false;
	}
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
	{
		LOGGER::CTP_Log("--->>> ErrorID= %d, ErrorMsg = %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
	}
	return bResult;

}


bool CTraderSpi::CTP_IsFlowControl(int iResult) {

	return ((iResult == -2) || (iResult == -3));
}
void CTraderSpi::OnFrontConnected()
{   

	string authorcode = UserManager::GetInstance()->GetUserMap()[this->INVESTOR_ID]->authorcode;

	if (authorcode.length() == 0) {
		ReqUserLogin();
	}
	else {  //���authorcode ��Ϊ����ôҪ���пͻ�����֤

		ReqAuthenticate();

	}
}
void CTP::CTraderSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField * pRspAuthenticateField, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo == NULL || pRspInfo->ErrorID == 0) {
		this->ReqUserLogin();
	}
	else {
 
		LOGGER::CTP_Log("%s",pRspInfo->ErrorMsg);
		Sleep(10000);
		this->ReqAuthenticate();
	}

}

void CTraderSpi::ReqUserLogin()
{
    CThostFtdcReqUserLoginField req;
    ::memset(&req, 0, sizeof(req));
    strcpy_s(req.BrokerID, BROKER_ID.c_str());
    strcpy_s(req.UserID,   INVESTOR_ID.c_str());
    strcpy_s(req.Password, PASSWORD.c_str());
	strcpy(req.UserProductInfo, "HX-v01");
	while (true) {
		int iResult = this->tdapi->ReqUserLogin(&req, ++iRequestID);
		if (!CTP_IsFlowControl(iResult))
		{
			//LOGGER::CTP_Log("--->>> Send Login Request: %s\n", ((iResult == 0) ? "Success" : "Failure"));
			break;
		}
		else {
		//	LOGGER::CTP_Log("--->>> ReqUserLogin %d Under Flow Control\n", iResult);
			Sleep(1000);

		}
	}
    
}
void CTP::CTraderSpi::ReqAuthenticate()
{
	CThostFtdcReqAuthenticateField reqauthor;
	memset(&reqauthor, 0, sizeof(CThostFtdcReqAuthenticateField));
	string authorcode = UserManager::GetInstance()->GetUserMap()[this->INVESTOR_ID]->authorcode;
	string appid = UserManager::GetInstance()->GetUserMap()[this->INVESTOR_ID]->appid;
	strcpy(reqauthor.AuthCode, authorcode.c_str());  //��֤��
	strcpy(reqauthor.AppID, appid.c_str());
	strcpy(reqauthor.UserProductInfo, "HX-v01");
	strcpy(reqauthor.BrokerID, BROKER_ID.c_str());
	strcpy(reqauthor.UserID, INVESTOR_ID.c_str());
	int i = 0;
	do {
		i = this->tdapi->ReqAuthenticate(&reqauthor, iRequestID++);
		Sleep(1000);
	} while (i != 0);


}
void CTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

	if (pRspInfo->ErrorID == 3) {

	}
    LOGGER::CTP_Log("--->>>OnRspUserLogin\n");
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {


		//time_t dcetime = pRspUserLogin->DCETime;
		/*LOGGER::CTP_Log("%s\n", pRspUserLogin->CZCETime);
		LOGGER::CTP_Log("%s\n",pRspUserLogin->LoginTime);
        LOGGER::CTP_Log("--->>> TradingDay  = %s\n"
                "--->>> LoginTime   = %s\n"
                "--->>> BrokerID    = %s\n"
                "--->>> UserID      = %s\n"
                "--->>> SystemName  = %s\n"
                "--->>> FrontID     = %d\n"
                "--->>> SessionID   = %d\n"
                "--->>> MaxOrderRef = %s\n",
                pRspUserLogin->TradingDay,
                pRspUserLogin->LoginTime,
                pRspUserLogin->BrokerID,
                pRspUserLogin->UserID,
                pRspUserLogin->SystemName,
                pRspUserLogin->FrontID,
                pRspUserLogin->SessionID,
                pRspUserLogin->MaxOrderRef);*/

	
        FRONT_ID     = pRspUserLogin->FrontID;
        SESSION_ID     = pRspUserLogin->SessionID;
        g_iOrderRef = atoi(pRspUserLogin->MaxOrderRef);
        g_iOrderRef++;
        sprintf_s(ORDER_REF, "%d", g_iOrderRef);    

		CtpUser* user = UserManager::GetInstance()->GetUser(this->INVESTOR_ID);
		user->connectstatus = true;
		eventstruct eventdata;
		memset(&eventdata, 0, sizeof(eventstruct));
		eventdata.dropable = false;
		eventdata.message = user->userid;
		eventdata.type = eventtype::accountchange;
		event(eventdata);
        ReqSettlementInfoConfirm();
	}
	else 
	{   
		Sleep(1000);//����ر��д��� ��Ϣһ�������µ�¼
		ReqUserLogin();
	}
}

void CTraderSpi::ReqSettlementInfoConfirm()
{
    CThostFtdcSettlementInfoConfirmField req;
    memset(&req, 0, sizeof(req));
    strcpy_s(req.BrokerID, BROKER_ID.c_str());
    strcpy_s(req.InvestorID, INVESTOR_ID.c_str());
	while (true) {
		int iResult = this->tdapi->ReqSettlementInfoConfirm(&req, ++iRequestID);
		if (!CTP_IsFlowControl(iResult))
		{
			LOGGER::CTP_Log("--->>> Send Req for Settlement Confirm %s\n", ((iResult == 0) ? "Success" : "Failure"));
			break;
		}
		else {

		//	LOGGER::CTP_Log("--->>> ReqSettlementInfoConfirm %d Under Flow Control\n", iResult);
			Sleep(1000);
		}

	}
}

void CTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

	//LOGGER::CTP_Log("--->>> OnRspSettlementInfoConfirm \n");
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {        
     //   ReqQryInstrument();
		ReqQryInvestor();
    }
}

void CTraderSpi::ReqQryInstrument()
{
	
		CThostFtdcQryInstrumentField req;
		memset(&req, 0, sizeof(req));
		while (true)
		{
			int iResult = this->tdapi->ReqQryInstrument(&req, ++iRequestID);

			if (!CTP_IsFlowControl(iResult))
			{
				LOGGER::CTP_Log("--->>> Send ReqQryInstrument %s  %s\n", req.InstrumentID, ((iResult == 0) ? "Success" : "Failure"));
				break;
			}
			else
			{
		//		LOGGER::CTP_Log("--->>> ReqQryInstrument %d Under Flow Control\n", iResult);
				Sleep(1000);
			}

		}

	//}
		

	}
    // while

	
void CTraderSpi::ReqQryInstrumentCommissionRate()
{

	CThostFtdcQryInstrumentCommissionRateField req1;
	memset(&req1, 0, sizeof(req1));
	strcpy_s(req1.InstrumentID, "a1811");
	strcpy_s(req1.BrokerID, BROKER_ID.c_str());
	strcpy_s(req1.InvestorID, INVESTOR_ID.c_str());
	while (true) {
		int iResult = this->tdapi->ReqQryInstrumentCommissionRate(&req1, ++iRequestID);
		if (!CTP_IsFlowControl(iResult))
		{
			LOGGER::CTP_Log("--->>> Send Req for  reqinstrumentcommissionrate %s\n", ((iResult == 0) ? "Success" : "Failure"));
			break;
		}
		else {

		//	LOGGER::CTP_Log("--->>>�� reqinstrumentcommissionrate %d Under Flow Control\n", iResult);

			Sleep(1000);
		}

	}
}




void CTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
   //LOGGER::CTP_Log("--->>> OnRspQryInstrument \n");
    if (!IsErrorRspInfo(pRspInfo))
    {
     //   pInstrument->

        if (NULL != pInstrument)
        {
			if(pInstrument->IsTrading)
			this->instrumentmap[pInstrument->InstrumentID] = *pInstrument;

         	
        }
        ///�����ѯ��Լ
      
    }
	if (bIsLast&&this->g_iMarket==0) {

	//	LOGGER::CTP_Log("�ռ�Ʒ����Ϣ��� \n");
	  
		eventstruct eventdata;
		eventdata.dropable = false;
		eventdata.message = this->INVESTOR_ID;
		eventdata.type = eventtype::instrumentchange;
		event(eventdata);
		
		this->ReqQryOrder();

	}

}




void CTraderSpi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {





}


void CTraderSpi::ReqQryTradingAccount()
{
    CThostFtdcQryTradingAccountField req;
    memset(&req, 0, sizeof(req));
    strcpy_s(req.BrokerID, BROKER_ID.c_str());
    strcpy_s(req.InvestorID, INVESTOR_ID.c_str());
    while (true)
    {
        int iResult = this->tdapi->ReqQryTradingAccount(&req, ++iRequestID);
        if (!CTP_IsFlowControl(iResult))
        {
            LOGGER::CTP_Log("--->>> ReqQryTradingAccount %s\n", ((iResult == 0) ? "Success" : "Failure"));
            break;
        }
        else
        {
         //   LOGGER::CTP_Log("--->>> ReqQryTradingAccount:Under Flow Control\n");
            Sleep(1000);
        }
    } // while
	
	
	
}

void CTraderSpi::FllowTrade(CThostFtdcTradeField  pTrade,int mulit)
{
	//����һ������ ��8��

	CThostFtdcInputOrderField order;
	(void)memset(&order, 0, sizeof(order));
	strcpy(order.BrokerID, this->BROKER_ID.c_str());
	strcpy(order.InvestorID, this->INVESTOR_ID.c_str());
	strcpy(order.InstrumentID, pTrade.InstrumentID);
	sprintf(order.OrderRef, "%5d%4d",this->g_iOrderRef++,9999);
	///ǿƽԭ��: ��ǿƽ
	order.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///�Զ������־: ��
	order.IsAutoSuspend = 0;
	///�û�ǿ����־: ��
	order.UserForceClose = 0;
	///Ͷ���ױ���ʶ��Ͷ��
	order.CombHedgeFlag[0] = THOST_FTDC_HFEN_Speculation;
	///��������
	order.ContingentCondition = THOST_FTDC_CC_Immediately;
	///�۸�

	double pricetick = this->instrumentmap[pTrade.InstrumentID].PriceTick;
	if (order.Direction == THOST_FTDC_D_Buy) {
		order.LimitPrice = pTrade.Price + pricetick * 5;
	}
	else {

		order.LimitPrice = pTrade.Price - pricetick * 5;
	}

	///����
	order.VolumeTotalOriginal = pTrade.Volume*mulit;
	///�ɽ�������
	order.VolumeCondition = THOST_FTDC_VC_AV;
	///��С�ɽ���
	order.MinVolume = 1;
	///��������
	order.Direction = pTrade.Direction;
	///�෴�ķ���	
	order.TimeCondition = THOST_FTDC_TC_GFD;
	///��������
	order.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	///��������
	order.CombOffsetFlag[0] = pTrade.OffsetFlag;
	///����в�λ��Ϊƽ�ֵ�
	//return order;
	
	while (true)
	{
		int iResult = this->tdapi->ReqOrderInsert(&order, ++iRequestID);
		if (!CTP_IsFlowControl(iResult))
		{
			LOGGER::CTP_Log("--->>> sendorder %s %s\n",INVESTOR_ID.c_str(), ((iResult == 0) ? "Success" : "Failure"));
			break;
		}
		else
		{
			//LOGGER::CTP_Log("--->>> sendorder :Under Flow Control\n");
			Sleep(1000);
		}
	} // while






}
void CTraderSpi::SendOrder(CThostFtdcInputOrderField order)
{
	strcpy(order.BrokerID, this->BROKER_ID.c_str());
	strcpy(order.InvestorID, this->INVESTOR_ID.c_str());
	
	sprintf(order.OrderRef, "%5d%4d", this->g_iOrderRef++, 9999);
	while (true)
	{
		int iResult = this->tdapi->ReqOrderInsert(&order, ++iRequestID);
		if (!CTP_IsFlowControl(iResult))
		{
			LOGGER::CTP_Log("--->>> sendorder %s %s\n", INVESTOR_ID.c_str(), ((iResult == 0) ? "Success" : "Failure"));
			break;
		}
		else
		{
			//	LOGGER::CTP_Log("--->>> sendorder :Under Flow Control\n");
			Sleep(1000);
		}
	} // while
}

void CTraderSpi::SendAction(CThostFtdcInputOrderActionField action)
{
	strcpy(action.BrokerID, this->BROKER_ID.c_str());
	strcpy(action.InvestorID, this->INVESTOR_ID.c_str());

	action.OrderActionRef = this->g_iOrderRef++;
	while (true)
	{
		int iResult = this->tdapi->ReqOrderAction(&action, ++iRequestID);
		if (!CTP_IsFlowControl(iResult))
		{
			LOGGER::CTP_Log("--->>> sendorder %s %s\n", INVESTOR_ID.c_str(), ((iResult == 0) ? "Success" : "Failure"));
			break;
		}
		else
		{
			//	LOGGER::CTP_Log("--->>> sendorder :Under Flow Control\n");
			Sleep(1000);
		}
	} // while
}
void CTP::CTraderSpi::FllowOrder(CThostFtdcOrderField pOrder, int multi)
{
	CThostFtdcInputOrderField order;
	(void)memset(&order, 0, sizeof(order));
	strcpy(order.BrokerID, this->BROKER_ID.c_str());
	strcpy(order.InvestorID, this->INVESTOR_ID.c_str());
	strcpy(order.InstrumentID, pOrder.InstrumentID);
	sprintf(order.OrderRef, "%5d%4d", this->g_iOrderRef++, 9999);
	///ǿƽԭ��: ��ǿƽ
	order.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///�Զ������־: ��
	order.IsAutoSuspend = 0;
	///�û�ǿ����־: ��
	order.UserForceClose = 0;
	///Ͷ���ױ���ʶ��Ͷ��
	order.CombHedgeFlag[0] = THOST_FTDC_HFEN_Speculation;
	///��������
	order.ContingentCondition = THOST_FTDC_CC_Immediately;
	///�۸�

	double pricetick = this->instrumentmap[pOrder.InstrumentID].PriceTick;
	
		order.LimitPrice = pOrder.LimitPrice;


	///����
	order.VolumeTotalOriginal = pOrder.VolumeTotalOriginal*multi;
	///�ɽ�������
	order.VolumeCondition = THOST_FTDC_VC_AV;
	///��С�ɽ���
	order.MinVolume = 1;
	///��������
	order.Direction = pOrder.Direction;
	///�෴�ķ���	
	order.TimeCondition = THOST_FTDC_TC_GFD;
	///��������
	order.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	///��������
	memcpy(order.CombOffsetFlag, pOrder.CombOffsetFlag, sizeof(order.CombOffsetFlag));
	///����в�λ��Ϊƽ�ֵ�

	while (true)
	{
		int iResult = this->tdapi->ReqOrderInsert(&order, ++iRequestID);
		if (!CTP_IsFlowControl(iResult))
		{
			LOGGER::CTP_Log("--->>> sendorder %s %s\n", INVESTOR_ID.c_str(), ((iResult == 0) ? "Success" : "Failure"));
			break;
		}
		else
		{
		//	LOGGER::CTP_Log("--->>> sendorder :Under Flow Control\n");
			Sleep(1000);
		}
	} // while





}



void CTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    
 //    LOGGER::CTP_Log("--->>> OnRspQryTradingAccount \n");
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    { 
  //   /*   LOGGER::CTP_Log("********Account Info***********\n");
		//LOGGER::CTP_Log("���͹�˾����:      %s\n", pTradingAccount->BrokerID);
		//LOGGER::CTP_Log("Ͷ�����ʺ�:        %s\n", pTradingAccount->AccountID);
		//LOGGER::CTP_Log("�ϴ���Ѻ���:      %f\n", pTradingAccount->PreMortgage);
		//LOGGER::CTP_Log("�ϴ����ö��:      %f\n", pTradingAccount->PreCredit);
		//LOGGER::CTP_Log("�ϴδ���:        %f\n", pTradingAccount->PreDeposit);
		//LOGGER::CTP_Log("�ϴν���׼����:    %f\n", pTradingAccount->PreBalance);
		//LOGGER::CTP_Log("�ϴ�ռ�õı�֤��:  %f\n", pTradingAccount->PreMargin);
		//LOGGER::CTP_Log("��Ϣ����:          %f\n", pTradingAccount->InterestBase);
		//LOGGER::CTP_Log("��Ϣ����:          %f\n", pTradingAccount->Interest);
		//LOGGER::CTP_Log("�����:          %f\n", pTradingAccount->Deposit);
		//LOGGER::CTP_Log("������:          %f\n", pTradingAccount->Withdraw);
		//LOGGER::CTP_Log("����ı�֤��:      %f\n", pTradingAccount->FrozenMargin);
		//LOGGER::CTP_Log("������ʽ�:        %f\n", pTradingAccount->FrozenCash);
		//LOGGER::CTP_Log("�����������:      %f\n", pTradingAccount->FrozenCommission);
		//LOGGER::CTP_Log("��ǰ��֤���ܶ�:    %f\n", pTradingAccount->CurrMargin);
		//LOGGER::CTP_Log("�ʽ���:          %f\n", pTradingAccount->CashIn);
		//LOGGER::CTP_Log("������:            %f\n", pTradingAccount->Commission);
		//LOGGER::CTP_Log("ƽ��ӯ��:          %f\n", pTradingAccount->CloseProfit);
		//LOGGER::CTP_Log("�ֲ�ӯ��:          %f\n", pTradingAccount->PositionProfit);
		//LOGGER::CTP_Log("�ڻ�����׼����:    %f\n", pTradingAccount->Balance);
		//LOGGER::CTP_Log("�����ʽ�:          %f\n", pTradingAccount->Available);
		//LOGGER::CTP_Log("��ȡ�ʽ�:          %f\n", pTradingAccount->WithdrawQuota);
		//LOGGER::CTP_Log("����׼����:        %f\n", pTradingAccount->Reserve);
		//LOGGER::CTP_Log("������:            %s\n", pTradingAccount->TradingDay);
		//LOGGER::CTP_Log("������:          %d\n", pTradingAccount->SettlementID);
		//LOGGER::CTP_Log("���ö��:          %f\n", pTradingAccount->Credit);
		//LOGGER::CTP_Log("��Ѻ���:          %f\n", pTradingAccount->Mortgage);
		//LOGGER::CTP_Log("��������֤��:      %f\n", pTradingAccount->ExchangeMargin);
		//LOGGER::CTP_Log("Ͷ���߽��֤��:  %f\n", pTradingAccount->DeliveryMargin);
		//LOGGER::CTP_Log("���������֤��:  %f\n", pTradingAccount->ExchangeDeliveryMargin);
		//LOGGER::CTP_Log("�����ڻ�����׼����:%f\n", pTradingAccount->ReserveBalance)*/;
		

		CtpUser* user = UserManager::GetInstance()->GetUserMap()[pTradingAccount->AccountID];
		//	user.username = "test";
		user->userid = pTradingAccount->AccountID;
		user->connectstatus = true;
		user->dynicright = 10;
		user->margin = pTradingAccount->DeliveryMargin;				///Ͷ���߽��֤��
		user->updatetime = TimeTool::GetStrCurrentTime();			///����ʱ��
		user->availablemoney = pTradingAccount->Available;			///�����ʽ�
		user->staticright = pTradingAccount->PreBalance;			///�ϴν���׼����
		user->dynicright = pTradingAccount->Balance;				///�ڻ�����׼����
		user->margin = pTradingAccount->CurrMargin;					///��ǰ��֤���ܶ�
		user->closeprofit = pTradingAccount->CloseProfit;			//ƽ��ӯ��
		user->postionprofit = pTradingAccount->PositionProfit;		//�ֲ�ӯ��
		
		user->deposti = pTradingAccount->Deposit;					//���
		user->withdraw = pTradingAccount->Withdraw;					//����

		//user->usercname=pTradingAccount->

		UserManager::GetInstance()->UpdateUser(user->userid, *user);
		eventstruct eventdata;
		eventdata.dropable = false;
		eventdata.message = user->userid;
		eventdata.type = eventtype::accountchange;
		event(eventdata);

		  
		if (this->g_iMarket == 0) {
			Sleep(1000);
			this->ReqQryInstrument();
		}

   //     ReqQryInvestorPosition();
    }
}

void CTraderSpi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	CtpUser* user = UserManager::GetInstance()->GetUser(this->INVESTOR_ID);
	if (pInvestorPositionDetail == NULL)
	{
	}
	else {
		
		user->postionlist.push_back(*pInvestorPositionDetail);
	}
	if (bIsLast&&g_iMarket==0) {
		user->postioncom.clear();
		this->ReqQryInvestorPositionCombineDetail();
		//g_iMarket = 1;


  }
}
void CTP::CTraderSpi::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField * pInvestorPositionCombineDetail, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	if (pInvestorPositionCombineDetail == NULL)
	{
	}
	else {
		if (pInvestorPositionCombineDetail->LegID ==0 ) {
			CtpUser* user = UserManager::GetInstance()->GetUser(this->INVESTOR_ID);
			user->postioncom.push_back(*pInvestorPositionCombineDetail);
		}
	}
	if (bIsLast) {
		CtpUser* user = UserManager::GetInstance()->GetUser(this->INVESTOR_ID);
		eventstruct eventdata;
		eventdata.dropable = false;
		eventdata.message = user->userid;
		eventdata.type = eventtype::postioncomchange;
		event(eventdata);
	}

	if (bIsLast&&g_iMarket == 0) {
		g_iMarket = 1;
	}
}
void CTP::CTraderSpi::OnRspQryInvestor(CThostFtdcInvestorField * pInvestor, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	if (pInvestor == NULL)
	{
	}
	else {
		CtpUser* user = UserManager::GetInstance()->GetUser(this->INVESTOR_ID);
		user->usercname = pInvestor->InvestorName;
	}
	if (bIsLast&&g_iMarket == 0) {

		this->ReqQryTradingAccount();
	}



}
;
void CTraderSpi::ReqQryOrder() {

	CThostFtdcQryOrderField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID.c_str());
	strcpy_s(req.InvestorID, INVESTOR_ID.c_str());
	strcpy_s(req.InstrumentID, INSTRUMENT_ID.c_str());

	while (true)
	{

		int iResult = this->tdapi->ReqQryOrder(&req, ++iRequestID);
		if (!CTP_IsFlowControl(iResult))
		{
			LOGGER::CTP_Log("--->>> ReqQryOrder %s\n", ((iResult == 0) ? "Success" : "Failure"));

			break;
		}
		else
		{
		//	LOGGER::CTP_Log("--->>> ReqQryOrder: Under Flow Control\n");
			Sleep(1000);
		}

	}

}

void CTraderSpi::ReqQryTrade(){

	CThostFtdcQryTradeField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID.c_str());
	strcpy_s(req.InvestorID, INVESTOR_ID.c_str());
	strcpy_s(req.InstrumentID, INSTRUMENT_ID.c_str());

	while (true)
	{
		int iResult = this->tdapi->ReqQryTrade(&req, ++iRequestID);
		if (!CTP_IsFlowControl(iResult))
		{
			LOGGER::CTP_Log("--->>> ReqQryTrade %s %s\n",INVESTOR_ID.c_str(),((iResult == 0) ? "Success" : "Failure"));

			break;
		}
		else
		{
		//	LOGGER::CTP_Log("--->>> ReqQryTrade: Under Flow Control\n");
			Sleep(1000);
		}

	}

}

void CTraderSpi::ReqQryInvestorPosition()
{
    CThostFtdcQryInvestorPositionField req;
    memset(&req, 0, sizeof(req));
    strcpy_s(req.BrokerID, BROKER_ID.c_str());
    strcpy_s(req.InvestorID, INVESTOR_ID.c_str());
    strcpy_s(req.InstrumentID, INSTRUMENT_ID.c_str());
    while (true)
    {
        int iResult = this->tdapi->ReqQryInvestorPosition(&req, ++iRequestID);
        if (!CTP_IsFlowControl(iResult))
        {
            LOGGER::CTP_Log("--->>> ReqQryInvestorPosition %s\n", ((iResult == 0) ? "Success" : "Failure"));
            
            break;
        }
        else
        {
          //  LOGGER::CTP_Log("--->>> ReqQryInvestorPosition: Under Flow Control\n");
            Sleep(1000);
       }
    } // while
}

void CTP::CTraderSpi::ReqQryInvestor()
{


	CThostFtdcQryInvestorField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID.c_str());
	strcpy_s(req.InvestorID, INVESTOR_ID.c_str());
	while (true)
	{
		int iResult = this->tdapi->ReqQryInvestor(&req, ++iRequestID);
		if (!CTP_IsFlowControl(iResult))
		{
			LOGGER::CTP_Log("--->>> ReqQryInvestor %s\n", ((iResult == 0) ? "Success" : "Failure"));

			break;
		}
		else
		{
			//LOGGER::CTP_Log("--->>> ReqQryInvestorPositionDetail: Under Flow Control\n");
			Sleep(1000);
		}

	};
}

void CTP::CTraderSpi::ReqQryInvestorPositionDetail()
{
	CThostFtdcQryInvestorPositionDetailField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID.c_str());
	strcpy_s(req.InvestorID, INVESTOR_ID.c_str());
	while (true)
	{
	int iResult=this->tdapi->ReqQryInvestorPositionDetail(&req, ++iRequestID);
	if (!CTP_IsFlowControl(iResult))
	{
		LOGGER::CTP_Log("--->>> ReqQryInvestorPositionDetail %s\n", ((iResult == 0) ? "Success" : "Failure"));

		break;
	}
	else
	{
		//LOGGER::CTP_Log("--->>> ReqQryInvestorPositionDetail: Under Flow Control\n");
		Sleep(1000);
	}

	}
}

void CTP::CTraderSpi::ReqQryInvestorPositionCombineDetail()
{

	CtpUser* user = UserManager::GetInstance()->GetUser(this->INVESTOR_ID);
	user->postioncom.clear();
	CThostFtdcQryInvestorPositionCombineDetailField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID.c_str());
	strcpy_s(req.InvestorID, INVESTOR_ID.c_str());
	while (true)
	{
		int iResult = this->tdapi->ReqQryInvestorPositionCombineDetail(&req, ++iRequestID);
		if (!CTP_IsFlowControl(iResult))
		{
			LOGGER::CTP_Log("--->>> ReqQryInvestorPositionCombineDetail %s\n", ((iResult == 0) ? "Success" : "Failure"));

			break;
		}
		else
		{
			//LOGGER::CTP_Log("--->>> ReqQryInvestorPositionDetail: Under Flow Control\n");
			Sleep(1000);
		}

	}
}


void CTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	//
	if (!IsErrorRspInfo(pRspInfo)) {


	}
	if (bIsLast && this->g_iMarket==0) {
		ReqQryOrder();
		}

		//CTP_OnRspQryInvestorPosition(pInvestorPosition,pRspInfo,nRequestID,bIsLast);    
		

	
}

void CTraderSpi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData,CThostFtdcRspInfoField *pRspInfo,int nRequestID){

    int i=0;

    if (pDepthMarketData == NULL)
    {
        return;
    }

     LOGGER::CTP_Log("///InstrumentID     :%s\n"
            "///LastPrice        :%f\n"
            "///AskPrice1        :%f\n"
            "///BidPrice1        :%f\n"
            "///AskVolume1       :%d\n"
            "///BidVolume1       :%d\n"
            "///UpdateTime       :%s\n",
            pDepthMarketData->InstrumentID,
            pDepthMarketData->LastPrice,
            pDepthMarketData->AskPrice1,
            pDepthMarketData->BidPrice1,
            pDepthMarketData->AskVolume1,
            pDepthMarketData->BidVolume1,
            pDepthMarketData->UpdateTime);
    
}

void CTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	LOGGER::CTP_Log("--->>> OnRspOrderInsert   %s\n",string(pRspInfo->ErrorMsg).c_str());
	if (IsErrorRspInfo(pRspInfo)) {
		LOGGER::CTP_Log("InstrumentID:%s orderref %s requestid %d limitprice:%f volume:%d",
			pInputOrder->InstrumentID,
			pInputOrder->OrderRef,
			pInputOrder->RequestID,
			pInputOrder->LimitPrice,
			pInputOrder->VolumeTotalOriginal);

	}
  //  CTP_OnRspOrderInsert(pInputOrder, pRspInfo, nRequestID, bIsLast);
}

void CTraderSpi::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    //���ִ��������ȷ���򲻻����ûص�
    
   LOGGER::CTP_Log("--->>> OnRspExecOrderInsert \n");
    IsErrorRspInfo(pRspInfo);
}

void CTraderSpi::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    //���ѯ����ȷ���򲻻����ûص�    
    LOGGER::CTP_Log("--->>> OnRspForQuoteInsert \n");
    IsErrorRspInfo(pRspInfo);
}

void CTraderSpi::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    //���������ȷ���򲻻����ûص�
    
    LOGGER::CTP_Log("--->>> OnRspQuoteInsert \n");
    IsErrorRspInfo(pRspInfo);
}

void CTraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	LOGGER::CTP_Log("--->>> OnRspQuoteInsert \n");
	IsErrorRspInfo(pRspInfo);
//    CTP_OnRspOrderAction(pInputOrderAction,pRspInfo,nRequestID,bIsLast);
}

void CTraderSpi::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInpuExectOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

    //��ȷ�ĳ����������������ûص�
}

void CTraderSpi::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInpuQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    //��ȷ�ĳ����������������ûص�
}
void CTraderSpi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	
	CtpUser* user = UserManager::GetInstance()->GetUser(this->INVESTOR_ID);
	if (pTrade == NULL)
	{
	}
	else {

		user->tradelist.push_back(*pTrade);
	}
	if (bIsLast&&g_iMarket==0) {
		user->postionlist.clear();
		this->ReqQryInvestorPositionDetail();
	}

}
///����֪ͨ
void CTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
  //���Ȳ鿴 ��һ������� OrderLocalID �ټӵ�order list����ȥ 
	


	CtpUser* user = UserManager::GetInstance()->GetUser(this->INVESTOR_ID);

	//user->orderlist.push_back(*pOrder);
	bool flag = true;
	list<CThostFtdcOrderField>::iterator it;
	for (it = user->orderlist.begin(); it != user->orderlist.end(); ++it)
	{
		if ((it->FrontID == pOrder->FrontID) && (it->SessionID == pOrder->SessionID) && (strcmp(it->OrderRef, pOrder->OrderRef) == 0))
		{
			flag = false;
			*it = *pOrder;
		}
	}

	if (flag)
		user->orderlist.push_back(*pOrder);
	//�������userid �ǲ��Ǳ�ѡ�е�
	if(UserManager::GetInstance()->IsMonitorSelect(user->userid)) {
		eventstruct eventdata;
		memset(&eventdata, 0, sizeof(eventstruct));
		eventdata.dropable = false;
		eventdata.message = user->userid;
		eventdata.type = eventtype::ordelistchange;
		event(eventdata);
	}

}

//ִ������֪ͨ
void CTraderSpi::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder)
{
}

//ѯ��֪ͨ
void CTraderSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)

{
    
    //�������н���ѯ��֪ͨͨ���ýӿڷ��أ�ֻ�������̿ͻ������յ���֪ͨ
}

//����֪ͨ
void CTraderSpi::OnRtnQuote(CThostFtdcQuoteField *pQuote)
{
}

///�ɽ�֪ͨ
void CTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{   
	json j;
	j["instrumentid"] = pTrade->InstrumentID;

	j["orderref"] = pTrade->OrderRef;

	j["userid"] = pTrade->UserID;

	j["direction"] = pTrade->Direction;

	j["offsetflag"] = pTrade->OffsetFlag;

	j["price"] = pTrade->Price;

	j["volume"] = pTrade->Volume;

	j["tradedate"] = pTrade->TradeDate;

	j["tradetime"] = pTrade->TradeTime;

	ofstream fout("./accountlog/" +string(pTrade->UserID)+ "trade.json", ios::app);     //����һ��data.txt���ļ�
	if (fout.is_open()) {

		fout << j << endl;  //��������ֵд���ļ�
		fout.close();                  //�ر��ļ�

	}
	CtpUser* user = UserManager::GetInstance()->GetUser(this->INVESTOR_ID);
	TThostFtdcDirectionType tradedirection = pTrade->Direction;//�ɽ����ķ���
	user->tradelist.push_back(*pTrade);

	if (pTrade->OffsetFlag == THOST_FTDC_OF_Open && (pTrade->TradeSource == THOST_FTDC_TSRC_NORMAL || pTrade->TradeSource == '\0')) {//���������Ʒ�ɽ���ô������Ҫ�޸ĵ�
		CThostFtdcInvestorPositionDetailField postiondetail;
		memset(&postiondetail, 0, sizeof(CThostFtdcInvestorPositionDetailField));
		memcpy(postiondetail.BrokerID, pTrade->BrokerID, sizeof(CThostFtdcInvestorPositionDetailField::BrokerID));
		postiondetail.Volume = pTrade->Volume;
		postiondetail.OpenPrice = pTrade->Price;
		postiondetail.Direction = pTrade->Direction;
		postiondetail.HedgeFlag = pTrade->HedgeFlag;
		memcpy(postiondetail.ExchangeID, pTrade->ExchangeID, sizeof(CThostFtdcInvestorPositionDetailField::ExchangeID));
		memcpy(postiondetail.TradingDay, pTrade->TradingDay, sizeof(TThostFtdcDateType));
		memcpy(postiondetail.InstrumentID, pTrade->InstrumentID, sizeof(CThostFtdcInvestorPositionDetailField::InstrumentID));
		memcpy(postiondetail.OpenDate, pTrade->TradeDate, sizeof(CThostFtdcTradeField::TradeDate));
		memcpy(postiondetail.TradeID, pTrade->TradeID, sizeof(CThostFtdcInvestorPositionDetailField::TradeID));
		postiondetail.TradeType = pTrade->TradeType;
		//postiondetail.
	user->postionlist.push_back(postiondetail);

	}
	else if (pTrade->OffsetFlag == THOST_FTDC_OF_Close)
	{//�޸���Ӧ���ӵĳֲ���
		
		int direction = 1;
		if (pTrade->Direction == THOST_FTDC_D_Buy) {
			//�����
			direction = -1;
		}
		list<CThostFtdcInvestorPositionDetailField>::iterator it;
		int tempv = pTrade->Volume;

		for (it = user->postionlist.begin(); it != user->postionlist.end(); it++)
		{
			if (it->Direction == tradedirection || strcmp(it->InstrumentID, pTrade->InstrumentID) != 0)//����ֲֵķ����trade�ķ�����ͬ����instrumentid��ͬ���Ե�
				continue;
			//if(i)
			if (it->Volume >= it->CloseVolume + tempv)
			{
				it->CloseAmount += tempv*pTrade->Price;
				it->CloseVolume += tempv;
				it->CloseProfitByTrade += (tempv*pTrade->Price - it->OpenPrice*tempv)*direction;
				CThostFtdcInvestorPositionDetailField closepostion;
				memcpy(&closepostion, &(*it), sizeof(CThostFtdcInvestorPositionDetailField));
				closepostion.Volume = tempv;
				closepostion.CloseVolume = tempv;
				break;
			}
			else
			{
				//todo:���ﻹ��Ҫ��ϸ����
				int temp = it->Volume - it->CloseVolume;
				it->CloseAmount += temp*pTrade->Price;
				it->CloseVolume += temp;
				tempv = tempv - temp;
				CThostFtdcInvestorPositionDetailField closepostion;
				memcpy(&closepostion, &(*it), sizeof(CThostFtdcInvestorPositionDetailField));
				closepostion.Volume = temp;
				closepostion.CloseVolume = temp;
			//	closepostion.CloseProfitByTrade = direction* (temp*pTrade->Price - it->OpenPrice*temp)*multi;

			}
		}
	}

	else if (pTrade->OffsetFlag == THOST_FTDC_OF_CloseYesterday)
	{//�޸���Ӧ���ӵĳֲ���

		int direction = 1;
		if (pTrade->Direction == THOST_FTDC_D_Buy) {
			//�����
			direction = -1;
		}
		list<CThostFtdcInvestorPositionDetailField>::iterator it;
		int tempv = pTrade->Volume;
		for (it = user->postionlist.begin(); it != user->postionlist.end(); it++)
		{
			if (it->Direction == tradedirection || strcmp(it->InstrumentID, pTrade->InstrumentID) != 0)//����ֲֵķ����trade�ķ�����ͬ���Ե�
				continue;
			if (strcmp(it->TradingDay, pTrade->TradingDay) == 0) //���trading day ���˵��postion�ǽ����
				continue;
			if (it->Volume >= it->CloseVolume + tempv)
			{
				it->CloseAmount += tempv*pTrade->Price;
				it->CloseVolume += tempv;
				it->CloseProfitByTrade += (tempv*pTrade->Price - it->OpenPrice*tempv)*direction;
				CThostFtdcInvestorPositionDetailField closepostion;
				memcpy(&closepostion, &(*it), sizeof(CThostFtdcInvestorPositionDetailField));
				closepostion.Volume = tempv;
				closepostion.CloseVolume = tempv;
				//�����
				//closepostion.CloseProfitByTrade = (tempv*pTrade->Price - it->OpenPrice*tempv)*multi*direction;
				break;
			}
			else
			{
				//todo:���ﻹ��Ҫ��ϸ����
				int temp = it->Volume - it->CloseVolume;
				it->CloseAmount += temp*pTrade->Price;
				it->CloseVolume += temp;
			//	it->CloseProfitByTrade += (temp*pTrade->Price - it->OpenPrice*pTrade->Volume)*multi*direction;
				tempv = tempv - temp;
				CThostFtdcInvestorPositionDetailField closepostion;
				memcpy(&closepostion, &(*it), sizeof(CThostFtdcInvestorPositionDetailField));
				closepostion.Volume = temp;
				closepostion.CloseVolume = temp;
			//	closepostion.CloseProfitByTrade = (temp*pTrade->Price - it->OpenPrice*temp)*multi*direction;
			}

		}
	}
	else if (pTrade->OffsetFlag == THOST_FTDC_OF_CloseToday)
	{//�޸���Ӧ���ӵĳֲ���
		int direction = 1;
		if (pTrade->Direction == THOST_FTDC_D_Buy) {
			//�����
			direction = -1;
		}
		list<CThostFtdcInvestorPositionDetailField>::iterator it;
		int tempv = pTrade->Volume;
		for (it = user->postionlist.begin(); it != user->postionlist.end(); it++)
		{
			if (it->Direction == tradedirection || strcmp(it->InstrumentID, pTrade->InstrumentID) != 0)//����ֲֵķ����trade�ķ�����ͬ���Ե�
				continue;
			if (strcmp(it->TradingDay, pTrade->TradingDay) != 0) //���trading day �����˵��postion�������
				continue;

			if (it->Volume >= it->CloseVolume + tempv)
			{
			//	it->CloseAmount += tempv*pTrade->Price*multi;
				it->CloseVolume += tempv;
			//	it->CloseProfitByTrade += (tempv*pTrade->Price - it->OpenPrice*tempv)*multi*direction;
				CThostFtdcInvestorPositionDetailField closepostion;
				memcpy(&closepostion, &(*it), sizeof(CThostFtdcInvestorPositionDetailField));
				closepostion.Volume = tempv;
				closepostion.CloseVolume = tempv;
			//	closepostion.CloseProfitByTrade = (tempv*pTrade->Price - it->OpenPrice*tempv)*multi*direction;
				break;
			}
			else
			{
				//todo:���ﻹ��Ҫ��ϸ����
				int temp = it->Volume - it->CloseVolume;
				//it->CloseAmount += temp*pTrade->Price*multi;
				it->CloseVolume += temp;
				//it->CloseProfitByTrade += (temp*pTrade->Price*multi - it->OpenPrice*pTrade->Volume*multi)*direction;
				tempv = tempv - temp;
				CThostFtdcInvestorPositionDetailField closepostion;
				memcpy(&closepostion, &(*it), sizeof(CThostFtdcInvestorPositionDetailField));
				closepostion.Volume = temp;
				closepostion.CloseVolume = temp;
				//closepostion.CloseProfitByTrade = (temp*pTrade->Price - it->OpenPrice*temp)*multi*direction;
			}

		}
	}


	//����ȫ�պϵĳֲֵ������  
	//�����λ����
	//  this->inverstpositiondetaillist

	//���õ��Ӵӳֲ��б���ɾ���� 


	list<CThostFtdcInvestorPositionDetailField>::iterator it1;
	for (it1 = user->postionlist.begin(); it1 != user->postionlist.end();)
	{
		if (it1->Volume == it1->CloseVolume)
		{
			it1 = user->postionlist.erase(it1);

		}
		else {
			it1++;
		}
	}

	if (UserManager::GetInstance()->IsMonitorSelect(user->userid)) {
		eventstruct eventdata;
		memset(&eventdata, 0, sizeof(eventstruct));
		eventdata.dropable = false;
		eventdata.message = user->userid;
		eventdata.type = eventtype::tradelistchange;
		event(eventdata);
	}

}
void CTraderSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{

	//LOGGER::CTP_Log("--->>> OnRtnInstrumentStatus  = %c \n", pInstrumentStatus->EnterReason);
}
void CTraderSpi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField * pInstrumentCommissionRate, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{

	LOGGER::CTP_Log("--->>> OnRspQryInstrumentCommissionRate= %s  %f ,%f\n", pInstrumentCommissionRate->InstrumentID,pInstrumentCommissionRate->OpenRatioByMoney,pInstrumentCommissionRate->OpenRatioByVolume);

}
void CTraderSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	CtpUser* user = UserManager::GetInstance()->GetUser(this->INVESTOR_ID);
	if (pOrder == NULL)
	{
	}
	else {
		user->orderlist.push_back(*pOrder);
	}
	if (bIsLast&&this->g_iMarket==0) {
		user->tradelist.clear();
		ReqQryTrade();
	}

}


void CTraderSpi:: OnFrontDisconnected(int nReason)
{ 
	//INVESTOR_ID
	this->g_iMarket = 0;
	CtpUser* user=UserManager::GetInstance()->GetUser(this->INVESTOR_ID);
	user->orderlist.clear();
	user->tradelist.clear();
	user->postioncom.clear();
	user->postionlist.clear();
	user->connectstatus = false;
	eventstruct eventdata;
	memset(&eventdata, 0, sizeof(eventstruct));
	eventdata.dropable = false;
	eventdata.message = user->userid;
	eventdata.type = eventtype::accountchange;
	event(eventdata);

   LOGGER::CTP_Log("--->>> OnFrontDisconnected Reason = %d \n", nReason);
}
        
void CTraderSpi::OnHeartBeatWarning(int nTimeLapse)
{
   LOGGER::CTP_Log("--->>> OnHeartBeatWarning nTimeLapse = %d \n", nTimeLapse);
}

void CTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  //  CTP_OnRspError(pRspInfo,nRequestID,bIsLast);
}

bool CTraderSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
   

	return CTP_IsErrorRspInfo(pRspInfo);
}
