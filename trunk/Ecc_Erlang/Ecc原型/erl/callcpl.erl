-module(callcpl).
-export([run/1]).

start(0) ->
    io:format("call finished! ~n");
start(X) ->
    spawn(complex3, foo, [X, X]),
    start(X-1).

run(X) ->
start(X).
