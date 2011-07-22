#include "erl_nif.h"
#include "simple.h"

static ERL_NIF_TERM get_params_nif(ErlNifEnv* env, 
				   int argc, 
				   ERL_NIF_TERM argv[])
{
  int args_size;
  int i,j;
  const ERL_NIF_TERM* ent_args;

  if (!enif_get_tuple(env, argv[0], &args_size, &ent_args)) {
    return enif_make_badarg(env);
  }
  int args[args_size];

  for(i = 0; i < args_size; i++){
    enif_get_int(env, ent_args[i], &args[i]);
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

