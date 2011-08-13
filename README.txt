* simple_nif

.. contents::

** Overview

A simple nif to pass a list (or a tuple) of ints to a C function which returns a record of parameters.

I am releasing the code under the `ISC license`_.

** Setup

The two shell scripts compile.sh and compile_mac.sh are the scripts I've been using to compile smple_nif.c.  n.b.: simple_main.c is just a little main() function to show the functions in simple.c in action.

There are two version of simple_nif.c: one accepts a tuple of ints, the other accepts a list of ints.  Each has a corresponding test script simple_test.erl.  Before you run compile.sh it is necessary to copy or symlink one of the versions from passing_{list,tuple}/ to the top-level directory.

** Usage

*** simple:get_params/1

The nif function get_params takes the ints and returns a record:

::

  -record(params, {sum, mean, quartiles}).

For example:

::

  1> simple:get_params([1,3,5,7,9,8,6,4,2]).
  {params,45,5.0,{2.5,5.0,7.5}}
  2> 

*** simple_test:test/2

The test script simple_test.erl models more closely the usage I have in mind.  The test function, simple_test:test(N, Max), generates an N long list of ints randomly generated in the range 1-Max.  This input list is then split into windows, the size and offset of which are set in simple.hrl (defaults are 10 and 5).  Finally, the window list is mapped using get_params.  There are io:formats all along the way, e.g.:

::

  1> simple_test:test(50,9).
  Input: [2,1,5,1,2,9,4,6,6,6,
          5,1,2,6,1,7,1,6,4,5,
          1,5,8,3,8,4,9,3,3,7,
          1,4,9,1,4,9,4,8,1,2,
          6,9,5,1,1,3,7,8,6,4]
  
  WindowList: [[2,1,5,1,2,9,4,6,6,6],
               [9,4,6,6,6,5,1,2,6,1],
               [5,1,2,6,1,7,1,6,4,5],
               [7,1,6,4,5,1,5,8,3,8],
               [1,5,8,3,8,4,9,3,3,7],
               [4,9,3,3,7,1,4,9,1,4],
               [1,4,9,1,4,9,4,8,1,2],
               [9,4,8,1,2,6,9,5,1,1],
               [6,9,5,1,1,3,7,8,6,4],
               [3,7,8,6,4,0,0,0,0,0]]
  
  {params,42,4.2,{2.0,4.5,6.0}}
  {params,46,4.6,{2.0,5.5,6.0}}
  {params,38,3.8,{1.0,4.5,6.0}}
  {params,48,4.8,{3.0,5.0,7.0}}
  {params,51,5.1,{3.0,4.5,8.0}}
  {params,45,4.5,{3.0,4.0,7.0}}
  {params,43,4.3,{1.0,4.0,8.0}}
  {params,46,4.6,{1.0,4.5,8.0}}
  {params,50,5.0,{3.0,5.5,7.0}}
  {params,28,2.8,{0.0,1.5,6.0}}
  ok
  2>

** The code

# ... working here now ... #




.. ---------- ---------- ----------

.. _`ISC license`: http://en.wikipedia.org/wiki/ISC_license
