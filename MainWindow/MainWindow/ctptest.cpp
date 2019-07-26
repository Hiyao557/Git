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

// ���ӿ�
//#pragma comment (lib, "thostmduserapi.lib")
//#pragma comment (lib, "thosttraderapi.lib")

// ---- ȫ�ֱ��� ---- //
// ��������
TThostFtdcBrokerIDType gBrokerID = "9999";                         // ģ�⾭���̴���
TThostFtdcInvestorIDType gInvesterID = "147553";                      // Ͷ�����˻���
TThostFtdcPasswordType gInvesterPassword = "lijiaqi_557";                     // Ͷ��������

CThostFtdcMdApi *g_pMdUserApi = nullptr;                           // ����ָ��
char gMdFrontAddr[] = "tcp://180.168.146.187:10111";
//char gMdFrontAddr[] = "tcp://180.168.146.187:10101";               // ģ������ǰ�õ�ַ
char *g_pInstrumentID[] = { "TF1909", "zn1908", "cs1909", "CF909" }; // �����Լ�����б��С��ϡ���֣��������ѡһ��
int instrumentNum = 4;                                             // �����Լ��������
//unordered_map<string, TickToKlineHelper> g_KlineHash;              // ��ͬ��Լ��k�ߴ洢��

																   // ���ײ���
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;                    // ����ָ��															   //char gTradeFrontAddr[] = "tcp://180.168.146.187:10130";            // ģ�⽻��ǰ�õ�ַ
char gTradeFrontAddr[] = "tcp://180.168.146.187:10101";
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "zn1908";        // �����׵ĺ�Լ����
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // ��������
TThostFtdcPriceType gLimitPrice = 19295 + 20;                           // ���׼۸�



int main(int argc, char *argv[])
{
	//// �˺�����
	//cout << "�������˺ţ� ";
	//scanf("%s", gInvesterID);
	//cout << "���������룺 ";
	//scanf("%s", gInvesterPassword);

	// ��ʼ�������߳�
	cout << "��ʼ������..." << endl;
	//cout << "g_pMdUserApi before" << g_pMdUserApi << endl;
	g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();   // ��������ʵ��
	//cout << "g_pMdUserApi after" << g_pMdUserApi << endl;
	CThostFtdcMdSpi *pMdUserSpi = new CustomMdSpi;       // ��������ص�ʵ��
	g_pMdUserApi->RegisterSpi(pMdUserSpi);               // ע���¼���
	g_pMdUserApi->RegisterFront(gMdFrontAddr);           // ��������ǰ�õ�ַ
	g_pMdUserApi->Init();                                // ��������



														 // ��ʼ�������߳�
	cout << "��ʼ������..." << endl;
	g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi("\\"); // ��������ʵ��
																	  //CThostFtdcTraderSpi *pTradeSpi = new CustomTradeSpi;
	CustomTradeSpi *pTradeSpi = new CustomTradeSpi;               // �������׻ص�ʵ��
	g_pTradeUserApi->RegisterSpi(pTradeSpi);                      // ע���¼���
	g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // ���Ĺ�����
	g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // ����˽����
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr);              // ���ý���ǰ�õ�ַ
	g_pTradeUserApi->Init();                                      // ��������

	QApplication a(argc, argv);
	MainWindow w = new MainWindow;
	w.sizeHint();

	w.show();
																  // �ȵ��߳��˳�
	/*g_pMdUserApi->Join();
	delete pMdUserSpi;
	g_pMdUserApi->Release();

	g_pTradeUserApi->Join();
	delete pTradeSpi;
	g_pTradeUserApi->Release();*/

	//getchar();

	
	return a.exec();

	// ת������k������
	//TickToKlineHelper tickToKlineHelper;
	//tickToKlineHelper.KLineFromLocalData("market_data.csv", "K_line_data.csv");

	
	
}