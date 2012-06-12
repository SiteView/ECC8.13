-module(loadc).
-export([startc/1]).

startc(X) ->
    case erl_ddll:load_driver(".", startc) of
        ok -> ok;
        {error, already_loaded} -> ok;
        _ -> exit({error, could_not_load_driver})
    end,
    Port = open_port({spawn, startc}, []),
    Port ! {self(), {command, encode(X)}},
    receive
        {Port, {data, Data}} ->
        %io:format("~w~n", [decode(Data)])
        decode(Data)
    end.

encode(Z) -> integer_to_list(Z).

decode(String) -> list_to_atom(String).