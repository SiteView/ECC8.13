// cclient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "erl_interface.h"
#include "ei.h"

#define BUFSIZE 1000

int my_listen(int port);

int foo(int x) {
  Sleep(3000);
  return x+1;
}

int bar(int y) {
  Sleep(3000);
  return y*2;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int fd;                                  /* fd to Erlang node */

	int loop = 1;                            /* Loop flag */
	int got;                                 /* Result of receive */
	unsigned char buf[BUFSIZE];              /* Buffer for incoming message */
	ErlMessage emsg;                         /* Incoming message */

	ETERM *fromp, *tuplep, *fnp, *argp, *resp;
	int res;
	
	int nID = atoi(argv[1]);

	erl_init(NULL, 0);

	if (erl_connect_init(nID, "dragonflowecc", 0) == -1)
		erl_err_quit("erl_connect_init");

	CString strErlNode=_T("");
	TCHAR szHostName[20];   
	DWORD dwSize   =   20;   
	GetComputerName(szHostName, &dwSize);   

	strErlNode.Format("e1@%s", szHostName);
	strErlNode.MakeLower();

	if ((fd = erl_connect((LPSTR)(LPCTSTR)strErlNode)) < 0)
		erl_err_quit("erl_connect");
	fprintf(stderr, "Connected to e1@zjw\n\r");

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
			argp = erl_element(2, tuplep);
			
			ETERM *arr[2];
			arr[0] = erl_mk_atom("cnode");
			arr[1] = erl_mk_atom("ok");
			resp = erl_mk_tuple(arr, 2);
			erl_send(fd, fromp, resp);
			erl_free_term(resp);

			if (strncmp((const char*)(char*)ERL_ATOM_PTR(fnp), "foo", 3) == 0) {
			res = foo(ERL_INT_VALUE(argp));
			} else if (strncmp((const char*)(char*)ERL_ATOM_PTR(fnp), "bar", 3) == 0) {
			res = bar(ERL_INT_VALUE(argp));
			}

			resp = erl_format("{cnode, ~i}", res);
			erl_send(fd, fromp, resp);

			erl_free_term(emsg.from); erl_free_term(emsg.msg);
			erl_free_term(fromp); erl_free_term(tuplep);
			erl_free_term(fnp); erl_free_term(argp);
			erl_free_term(resp);
			Sleep(3000);
			loop = 0;
		}
		}
	}

	return 0;
}

