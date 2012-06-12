-module(callc).
-export([run/4, call_mid/5, loop/0, test/3]).

call_mid(Mid, Pid, C_NODE, Queuename, Queueaddr) ->
    call_cnode({mid, Mid, Queuename, Queueaddr}, Pid, C_NODE).

test(Mid, Queuename, Queueaddr) ->
    {any, c1@zjw} ! {call, self(), {mid, Mid, Queuename, Queueaddr}}.
    
call_cnode(Msg, Pid, C_NODE) ->
    {any, loadc:startc(C_NODE)} ! {call, self(), Msg},
    Pid!{self(), start},
    receive
    go ->
    	%io:format("call_node received ~n", []),
    	call_cnode(Msg, Pid, C_NODE);
    {cnode, ok} ->
    	Pid!stop,
    	call_cnode(Msg, Pid, C_NODE);
    {cnode, Result} ->
        io:format("~w~n", [Result])         	
    end.

loop()->
	receive
	{Caller, start} ->
		%io:format("loop received ~n", []),
		sleep(1),
		Caller!go,
		loop();
         stop ->
         	exit(normal)
         end.

sleep(X)->
wait(X*10000000).

wait(0)->
ok;
wait(X) ->
wait(X-1).

run(Mid, C_NODE, Queuename, Queueaddr) ->
Pid = spawn(callc, loop, []),
spawn(callc, call_mid, [Mid, Pid, C_NODE, Queuename, Queueaddr]).
