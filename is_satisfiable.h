//is_satisfiable.h ~ An Implementation of a SAT-solver algorithm by Onat Tevfik Bilgili
#pragma once

#include "sat.h"
#include "covering_code.h"
#include "local_search.h"

bool small_sat(const SAT& formula);//function for solving SAT problems with less than 7 variables

bool is_satisfiable(const SAT& formula);//the main algorithm for solving SAT problems using Lemma 6 and Theorem 1
