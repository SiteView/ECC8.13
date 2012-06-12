-module(complex5).
-export([start/0, stop/0, init/0]).
-export([foo/1, bar/1, startc/1]).

start() ->
    case erl_ddll:load_driver(".", example_drv) of
        ok -> ok;
        {error, already_loaded} -> ok;
        _ -> exit({error, could_not_load_driver})
    end,
    spawn(?MODULE, init, []).

init() ->
    register(complex, self()),
    Port = open_port({spawn, example_drv}, []),
    loop(Port).

stop() ->
    complex ! stop.

foo(X) ->
    call_port({foo, X}).
bar(Y) ->
    call_port({bar, Y}).
startc(Z) ->
    start_node({startc, Z}).

call_port(Msg) ->
    complex ! {call, self(), Msg},
    receive
        {complex, Result} ->
            io:format("~w~n", [Result])
    end.

start_node(Msg) ->
    complex ! {call, self(), Msg},
    receive
        {complex, Result} ->
            %io:format("~w~n", [Result])
            Result
    end.
    
loop(Port) ->
    receive
        {call, Caller, Msg} ->
            Port ! {self(), {command, encode(Msg)}},
            receive
                {Port, {data, Data}} ->
                    Caller ! {complex, decode(Data)}
            end,
            loop(Port);
        stop ->
            Port ! {self(), close},
            receive
                {Port, closed} ->
                    exit(normal)
            end;
        {'EXIT', Port, Reason} ->
            io:format("~p ~n", [Reason]),
            exit(port_terminated)
    end.

encode({foo, X}) -> [1, X];
encode({bar, Y}) -> [2, Y];
encode({startc, Z}) -> [3, Z].

decode(String) -> list_to_atom(String).
