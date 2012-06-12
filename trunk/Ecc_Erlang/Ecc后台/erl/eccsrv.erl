-module(eccsrv). 
-export([start/0, ecc_server/0, stop/0, test/2, callmonitor/2]). 

ecc_server() -> 
receive 
stop -> 
io:format("Ecc server has stoped!~n", []); 
{PID, Mid, NodeID, Queuename, Queueaddr} -> 
io:format("Call monitor:~w,NodeID:~w,Queuename:~w,Queueaddr:~w~n", [Mid, NodeID, Queuename, Queueaddr]), 
callc:run(Mid, NodeID, Queuename, Queueaddr),
PID ! {self(), received, Mid}, 
ecc_server() 
end. 

start() -> 
register(ecc_server, spawn(eccsrv, ecc_server, [])). 

stop() -> 
ecc_server ! stop. 

test(Mid, NodeID) ->
callc:run(Mid, NodeID).

callmonitor(Mid, NodeID)->
ecc_server ! {self(), Mid, NodeID}.