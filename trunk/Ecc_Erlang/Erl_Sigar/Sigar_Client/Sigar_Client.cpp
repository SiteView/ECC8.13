// Sigar_Client.cpp : 定义控制台应用程序的入口点。
//

#include <string>
#include "erl_interface.h"
#include "ei.h"
#include "sigar.h"

using namespace std;

#define BUFSIZE 1000

string sigar_ps() {
	string res, tmp;
	int status, i;
    sigar_t *sigar;
    sigar_proc_list_t proclist;

    sigar_open(&sigar);

    status = sigar_proc_list_get(sigar, &proclist);

    if (status != SIGAR_OK) {
        printf("proc_list error: %d (%s)\n",
               status, sigar_strerror(sigar, status));
        exit(1);
    }

	res = "";
    for (i=0; i<proclist.number; i++) {
        sigar_pid_t pid = proclist.data[i];
        sigar_proc_state_t pstate;
        sigar_proc_time_t ptime;

        status = sigar_proc_state_get(sigar, pid, &pstate);
        if (status != SIGAR_OK) {
#ifdef DEBUG
            printf("error: %d (%s) proc_state(%d)\n",
                   status, sigar_strerror(sigar, status), pid);
#endif
            continue;
        }

        status = sigar_proc_time_get(sigar, pid, &ptime);
        if (status != SIGAR_OK) {
#ifdef DEBUG
            printf("error: %d (%s) proc_time(%d)\n",
                   status, sigar_strerror(sigar, status), pid);
#endif
            continue;
        }

		res = res + pstate.name;
		res = res + "=";
		res = res + pstate.name;
		res = res + "$";
	}

    sigar_proc_list_destroy(sigar, &proclist);

    sigar_close(sigar);

   return res;
   //return "sigar_ps";
}

int main(int argc, char* argv[])
{
	int fd;                                  /* fd to Erlang node */

	int loop = 1;                            /* Loop flag */
	int got;                                 /* Result of receive */
	unsigned char buf[BUFSIZE];              /* Buffer for incoming message */
	ErlMessage emsg;                         /* Incoming message */

	ETERM *fromp, *tuplep, *fnp, *resp;
	string res;
	
	int nID = atoi(argv[1]);

	erl_init(NULL, 0);

	if (erl_connect_init(nID, "dragonflowecc", 0) == -1)
		erl_err_quit("erl_connect_init");

	string strErlNode="";
	sprintf((char*)strErlNode.c_str(), "e1@%s", "zjw");

	if ((fd = erl_connect((char*)strErlNode.c_str())) < 0)
		erl_err_quit("erl_connect");
	fprintf(stderr, "Connected to %s\n\r", (char*)strErlNode.c_str());

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
			
			if (strncmp((const char*)(char*)ERL_ATOM_PTR(fnp), "sigar_ps", 8) == 0) {
			res = sigar_ps();
			} 

			resp = erl_format("{cnode, ~s}", res.c_str());
			erl_send(fd, fromp, resp);

			erl_free_term(emsg.from); erl_free_term(emsg.msg);
			erl_free_term(fromp); erl_free_term(tuplep);
			erl_free_term(fnp); erl_free_term(resp);
			//Sleep(3000);
			//loop = 0;
		}
		}
	}

	return 0;
}

