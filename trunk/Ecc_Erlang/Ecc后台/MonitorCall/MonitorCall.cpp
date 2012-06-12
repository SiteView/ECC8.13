// MonitorCall.cpp : 定义控制台应用程序的入口点。
//

#include "MonitorCall.h"
#include "Monitor.h"
#include "MonitorExecutant.h"
#include "LoadConfig.h"
#include "erl_interface.h"
#include "ei.h"

#define BUFSIZE 1000

CString g_strRootPath="D:\\v70";
string	g_ServerHost="localhost";
std::string g_RefreshQueueName="";
std::string g_QueueAddr="";
Option *g_pOption=NULL;
int m_nSockfd;

int Univ::seid(1);
int Univ::msappend(1000);
int Univ::pluscount(0);
bool Univ::enablemass(false);

Util *putil;

BOOL isInt(CString   m_str)   
{   
	try   
    {   
		int k = atoi(m_str);   
		CString   strTemp;   
        strTemp.Format("%d",k);   
        if(m_str!=strTemp)   
			return   FALSE;   
	}   
	catch(...)   
	{   
		return   FALSE;   
	}   
	return   TRUE;   
}

int ExecuteMonitroByID(string strMonitorID, bool bRefresh = false, bool bInit = false)
{
	SetSvdbAddrByFile("mc.config");

	putil=new Util();

	BOOL isRefresh=FALSE;

	g_strRootPath=putil->GetRootPath();

	try{

			MonitorExecutant *pt=new MonitorExecutant();
			Option *popt=new Option;
			if(popt==NULL)
			{
				putil->ErrorLog("Create Option object failed");
				return 1;
			}
			//load 设置文件 mc.config
			popt->LoadOption();
			g_ServerHost=popt->m_ServerAddress;

			pt->m_pOption=popt;
			g_pOption=popt;

			LoadConfig lc; // monitor device group file
			lc.m_pOption=popt;

			lc.LoadAll();

			Monitor *pM=new Monitor();
			if(!lc.CreateSingleMonitor(pM,strMonitorID))
			{
				puts("Create Monitor failed");
				delete pM;
				return -1;
			}
			pM->m_isRefresh = bRefresh;
			pt->SetMonitor(pM);

			if(bInit)
				pt->Init();
			
			pt->ExecuteMonitor();
			delete pM;

		}catch(MSException &e)
		{
			putil->ErrorLog(e.GetDescription());
			return -1;
		}

		if( Univ::enablemass && putil!=NULL )
		{	
			std::list<SingelRecord> listrcd;
			int count(0);
			if( (count=putil->AppendThenClearAllRecords(listrcd))>0 )
				cout<<"AppendMass "<<count<<" records done,"<<" slept "<<Univ::msappend<<" ms."<<endl;
			else if(count<0)
				cout<<"AppendMassRecord failed!"<<endl;
		}
		Sleep(3000);
		return 1;
}

int WaitForCall(int nID)
{
	int fd;                                  /* fd to Erlang node */

	int loop = 1;                            /* Loop flag */
	int got;                                 /* Result of receive */
	unsigned char buf[BUFSIZE];              /* Buffer for incoming message */
	ErlMessage emsg;                         /* Incoming message */

	ETERM *fromp, *tuplep, *fnp, *argp1, *argp2, *argp3, *resp;
	int res;
	
	erl_init(NULL, 0);

	if (erl_connect_init(nID, "dragonflowecc", 0) == -1)
		erl_err_quit("erl_connect_init");

	CString strErlNode="";
	TCHAR szHostName[20];   
	DWORD dwSize   =   20;   
	GetComputerName(szHostName, &dwSize);   

	strErlNode.Format("e1@%s", szHostName);
	strErlNode.MakeLower();

	if ((fd = erl_connect((LPSTR)(LPCTSTR)strErlNode)) < 0)
		erl_err_quit("erl_connect");
	fprintf(stderr, "Connected to %s\n\r", (LPSTR)(LPCTSTR)strErlNode);

	while (loop) {

		got = erl_receive_msg(fd, buf, BUFSIZE, &emsg);
		if (got == ERL_TICK) {
		/* ignore */
		} else if (got == ERL_ERROR) {
		loop = 0;
		} else {

		if (emsg.type == ERL_REG_SEND) {
			fromp = erl_element(2, emsg.msg);
			tuplep = erl_element(3, emsg.msg);
			fnp = erl_element(1, tuplep);
			argp1 = erl_element(2, tuplep);
			argp2 = erl_element(3, tuplep);
			argp3 = erl_element(4, tuplep);	

			ETERM *arr[2];
			arr[0] = erl_mk_atom("cnode");
			arr[1] = erl_mk_atom("ok");
			resp = erl_mk_tuple(arr, 2);
			erl_send(fd, fromp, resp);
			erl_free_term(resp);
			
			if (strncmp((const char*)(char*)ERL_ATOM_PTR(fnp), "mid", 3) == 0) 
			{
				g_RefreshQueueName = (char*)ERL_ATOM_PTR(argp2);
				g_QueueAddr = (char*)ERL_ATOM_PTR(argp3);
				if(g_RefreshQueueName.length() == 0)
					res = ExecuteMonitroByID((char*)ERL_ATOM_PTR(argp1), false, true);
				else
					res = ExecuteMonitroByID((char*)ERL_ATOM_PTR(argp1), true);
				//{
				//	char buf[256]={0};
				//	sprintf(buf,"Refresh end");
				//	::PushMessage(g_RefreshQueueName,"Refresh_END",buf,strlen(buf)+1,"default",g_QueueAddr);
				//}
			}
			
			resp = erl_format("{cnode, ~i}", res);
			erl_send(fd, fromp, resp);

			erl_free_term(emsg.from); erl_free_term(emsg.msg);
			erl_free_term(fromp); erl_free_term(tuplep);
			erl_free_term(fnp); erl_free_term(argp1);
			erl_free_term(argp2);erl_free_term(argp3);
			erl_free_term(resp);
			Sleep(3000);
			loop = 0;
		}
		}
	}
	return res;
}

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		puts("Parameter error");
		putil->ErrorLog("Parameter error");
		return -1;
	}
	
	printf("\n Process arg %d: ",argc);
	for(int i=0; i<=argc-1; ++i)
		printf("%s  ",argv[i]);
	printf("\n");

	if(isInt(argv[1]))
		return WaitForCall(atoi(argv[1]));
	else
		return ExecuteMonitroByID(argv[1], true);
}

