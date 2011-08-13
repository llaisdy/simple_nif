#include "erl_nif.h"
#include "simple.h"

static ERL_NIF_TERM get_params_nif(ErlNifEnv* env,
				   int argc, 
				   ERL_NIF_TERM argv[])
{
  ERL_NIF_TERM list = argv[0];
  unsigned int args_size;
  ERL_NIF_TERM head, tail;
  int i = 0;
  int j;

  if (!enif_get_list_length(env, list, &args_size)) {
    return enif_make_badarg(env);    
  }

  int args[args_size];

  while(enif_get_list_cell(env, list, &head, &tail)) {
    if(!enif_get_int(env, head, &args[i])) {
      return enif_make_badarg(env);    
    }
    i++;
    list = tail;
  }

  params_t params = get_params(args, args_size);

  ERL_NIF_TERM record_name = enif_make_atom(env, "params\0");
  ERL_NIF_TERM sum = enif_make_int(env, params.sum);
  ERL_NIF_TERM mean = enif_make_double(env, params.mean);

  ERL_NIF_TERM ent_quartiles_array[3];
  for (j = 0; j < 3; j++) {
    ent_quartiles_array[j] = enif_make_double(env, params.quartiles[j]);
  }
  ERL_NIF_TERM quartiles = enif_make_tuple_from_array(env, ent_quartiles_array, 3);

  return enif_make_tuple4(env, record_name, sum, mean, quartiles);
}

static ErlNifFunc nif_funcs[] = {
  {"get_params", 1, get_params_nif} // see note below
};
// eoia:326 has ... &get_params_nif
// doesn't seem to make any difference

ERL_NIF_INIT(simple, nif_funcs, NULL, NULL, NULL, NULL)

