//local_search.h ~ Implementation of a local search algortihm by Onat Tevfi Bilgili

#pragma once
#include "sat.h"

bool clauses_fixed_false(const SAT& formula, const Assignment& Values, const std::vector<bool>& fix_satus, const unsigned int& first_wrong_clause, const unsigned int& cls); //checks whether a clause has been fixed to be false

bool local_search(const SAT& formula, Assignment& values, const int radius, std::vector<bool>& fix_status);//inputs are the formula, an assignment, a positive intiger valued radius, and an array of length n which saves whether literals have been fixed before or not
