-module(simple).
-export([get_params/1, init/0]).
-on_load(init/0).

init() ->
    ok = erlang:load_nif("./simple_nif", 0).

get_params(_X) ->
    exit(nif_library_not_loaded).
