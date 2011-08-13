-module(simple_test).
-export([test/2]).
-export([get_random_input/2]).

-record(params, {sum, mean, quartiles}).
-define(WINDOW_SIZE, 10).
-define(WINDOW_OFFSET, 5).

test(N, Max) ->
    Input = get_random_input(N, Max),
    io:format("Input: ~p~n~n", [Input]), 
    WindowList = get_window_list(Input, ?WINDOW_SIZE, ?WINDOW_OFFSET),
    io:format("WindowList: ~p~n~n", [WindowList]), 
    ParamsList = lists:map(fun(W) -> simple:get_params(W) end,  WindowList),
    lists:foreach(fun(P) ->
			  case is_record(P, params) of
			      true ->
				  io:format("~p~n", [P]);
			      false ->
				  io:format("~p  <-- ?~n", [P])
			  end
		  end, ParamsList).

get_random_input(0, _) ->
    [];
get_random_input(N, Max) ->
    [random:uniform(Max) | get_random_input(N-1,Max)].

get_window_list(DataList, Size, _Offset) when length(DataList) < Size ->
    [DataList ++ make_list(0, Size - length(DataList))];
get_window_list(DataList, Size, Offset) ->
    [lists:sublist(DataList, Size) | get_window_list(lists:nthtail(Offset, DataList), Size, Offset)].

make_list(_, 0) ->
    [];
make_list(Item, N) ->
    [Item | make_list(Item, N-1)].
