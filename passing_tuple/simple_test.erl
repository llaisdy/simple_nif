-module(simple_test).
-export([test/2]).
-export([get_random_input/2]).

-record(params, {sum, mean, quartiles}).

test(N, Max) ->
    Input = get_random_input(N, Max),
    io:format("Input: ~p~n~n", [Input]), 
    WindowList = getWindowList(Input, 10, 5),
    io:format("WindowList: ~p~n~n", [WindowList]), 
    ParamsList = lists:map(fun(W) ->
				   Tup = list_to_tuple(W),
				   simple:get_params(Tup)
			   end,
			   WindowList),
    ParamsList.

get_random_input(0, _Max) ->
    [];
get_random_input(N, Max) ->
    [random:uniform(Max) | get_random_input(N-1,Max)].

getWindowList(DataList, Size, _Offset) when length(DataList) < Size ->
    [DataList ++ makeList(0, Size - length(DataList))];

getWindowList(DataList, Size, Offset) ->
    [lists:sublist(DataList, Size) | getWindowList(lists:nthtail(Offset, DataList), Size, Offset)].

makeList(_Item, 0) ->
    [];
makeList(Item, N) ->
    [Item | makeList(Item, N-1)].
