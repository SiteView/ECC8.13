-module(complex3).
-export([foo/2, bar/2, call_foo/3, call_bar/3, loop/0]).

call_foo(X, Pid, C_NODE) ->
    call_cnode({foo, X}, Pid, C_NODE).
call_bar(Y, Pid, C_NODE) ->
    call_cnode({bar, Y}, Pid, C_NODE).
    
call_cnode(Msg, Pid, C_NODE) ->
    {any, complex5:startc(C_NODE)} ! {call, self(), Msg},
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

foo(X, C_NODE) ->
Pid = spawn(complex3, loop, []),
spawn(complex3, call_foo, [X, Pid, C_NODE]).

bar(Y, C_NODE) ->
Pid = spawn(complex3, loop, []),
spawn(complex3, call_bar, [Y, Pid, C_NODE]).