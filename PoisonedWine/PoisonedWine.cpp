
// MyGame.cpp: 定义应用程序的类行为。
//
#pragma once
#include "pch.h"
#include "framework.h"
#include "PoisonedWine.h"
#include "PoisonedWineDlg.h"
#include <fstream>
#include<iostream>
#include <ctime>
#include<bitset>
#include<iomanip>
 
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyGameApp

BEGIN_MESSAGE_MAP(CMyGameApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyGameApp 构造

CMyGameApp::CMyGameApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMyGameApp 对象

CMyGameApp theApp;


// CMyGameApp 初始化
CWinThread* filethread = NULL;
bool gameend = false;
bool binaryend = false;
int arr[10] = { 0 };
void CMyGameApp::toBinary(int num)
{
	for (int i = 0; i < 10; i++)
		arr[i] = 0;
	int index = 9;
	while (num)
	{
		arr[index] = num % 2;
		num = num / 2;
		index--;
	}
}
UINT CMyGameApp::savedata(LPVOID p)/////////////////////////////////////保存数据线程函数
{
	
	CTime startime = CTime::GetCurrentTime();//程序开始时间
	ofstream file("tempstep.txt", ios::out | ios::app);
	file << "      程序启动时间：" << startime.GetYear() << "年" << startime.GetMonth() << "月" << startime.GetDay() << "日"
		<< "    " << startime.GetHour() << "时" << startime.GetMinute() << "分" << startime.GetSecond() << "秒" << endl;
	file.close();

	std::vector<std::vector<int>>binaryarr;

	std::vector<int>B[10];
	for (int i = 0; i < 10; i++)
	{
		binaryarr.push_back(B[i]);
	}
	//写入产生二进制数
	remove("Aa二进制数据aA.txt");
	ofstream file0("Aa二进制数据aA.txt", ios::out | ios::app);
	bool endfile = false;
	while (!gameend)//游戏没结束 线程一直存活
	{
		if (!endfile)//数据不存在  则写入数据
		{
			for (int i = 1; i < 1001; i++)
			{
				toBinary(i);
				for(int k = 0; k < 10; k++)
				{
					if (arr[k] == 1)
					{
						binaryarr[(int)(9 - k)].push_back(i);
					}
				}
			}
			file0 << "\t\t\t\t\t\t\t\t《十个奴隶寻找毒酒》" << endl;
			for (int i = 0; i < binaryarr.size(); i++)
			{
				file0 << "第【" << i + 1 << "】位奴隶：\n";
				int num = 0;
				for (int k = 0; k < binaryarr[i].size(); k++)
				{
					num++;
					file0 <<setw(3)<<setfill('0')<<binaryarr[i][k]<<"【"<<bitset<10>(binaryarr[i][k] )<<"】" ;
					if (num == 120)file0 << endl;
					else file0<< "\t";
				}
				file0 << endl<<endl;
			}
			file0 << "\t\t\t\t\t\t\t\t《八个奴隶寻找毒酒》" << endl;
			for (int i = 0; i < binaryarr.size()-2; i++)
			{
				file0 << "第【" << i + 1 << "】位奴隶：\n";
				int num = 0;
				for (int k = 0; k < binaryarr[i].size(); k++)
				{
					if (binaryarr[i][k] > 250)
					{
						break;
					}
					num++;
					file0 << setw(3) << setfill('0') << binaryarr[i][k] << "【" << bitset<10>(binaryarr[i][k]) << "】";
					if (num == 120)file0 << endl;
					else file0 << "\t";
				}
				file0 << endl << endl;
			}
			file0.close();
			endfile = true;
		}

	}
	//程序关闭  记录结束时间以及重写数据
	CTime nowtime = CTime::GetCurrentTime();
	ofstream fileend("tempstep.txt", ios::out | ios::app);
	fileend << "      程序关闭时间：" << nowtime.GetYear() << "年" << nowtime.GetMonth() << "月" << nowtime.GetDay() << "日"
		<< "    " << nowtime.GetHour() << "时" << nowtime.GetMinute() << "分" << nowtime.GetSecond() << "秒" << endl;
	CTimeSpan t = nowtime - startime;
	fileend << "                        本次程序运行时长：" <<t.GetMinutes()<< "分" <<t.GetSeconds()<< "秒" << endl<<"                        内存最高使用率："<< MAXpercent_memory << "%" <<endl
		<<"                        内存最低使用率："<< Minpercent_memory <<"%"<<endl<<"                        CPU最高使用率："<< MAXcpu_memory << "%" <<endl<<"                        CPU最低使用率："<< Mincpu_memory << "%" << endl <<endl<<endl;
	string h;
	ifstream ff("Aa程序运行记录aA.txt", ios::in);
	while (getline(ff, h)){
		fileend << h<<endl;
	}
	ff.close();
	fileend.close();
	std::remove("Aa程序运行记录aA.txt");
	int k = rename("tempstep.txt", "Aa程序运行记录aA.txt");
	return 0;
}
BOOL CMyGameApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的CMyGameApp::InitInstance()
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	//// GDI+ 初始化
	Status s = GdiplusStartup(&m_tokenGdiplus, &input, &output);

	AfxBeginThread(savedata, NULL);//////////////////////////////////////////////////////////////////////////////////////////保存程序数据的线程

	AfxEnableControlContainer();
	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CMyGameDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif
	gameend = true;
	Sleep(200);
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}


