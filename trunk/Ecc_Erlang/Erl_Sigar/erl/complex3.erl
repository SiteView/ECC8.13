-module(complex3).
-export([foo/1, bar/1, sigar_ps/0]).

foo(X) ->
    call_cnode({foo, X}).
bar(Y) ->
    call_cnode({bar, Y}).

sigar_ps() ->
    call_cnode({sigar_ps}).

call_cnode(Msg) ->
    {any, c1@zuik} ! {call, self(), Msg},
    %{any, c1@zjw} ! {call, self(), Msg},
    receive
        {cnode, Result} ->
            Result
    end.
