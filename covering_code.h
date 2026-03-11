//covering_code.h ~ Implementations of a deterministic covering code generator algorithm by Onat Tevfik Bilgili

#pragma once
#include "sat.h"

bool increment(Assignment &Values);//Considers the values of an assignment as the digits of a binary integer, increments that integer by one and returns true if maximal binary integer with n digits is not reached

bool increase1(std::vector<unsigned int>& numbers, const unsigned int p);//same but with basis p instead of 2

typedef std::vector<Assignment> Code;

unsigned int distance(const Assignment& asgn1, const Assignment& asgn2);//Hamming distance of two assignments

bool is_covered(const Code& cover, const Assignment& asgn, const unsigned int& r);

//First we will write the algorithm for covering codes of length n / 6, radius at most r / 6
Code small_cover(const unsigned int n, const unsigned int r);//returns a covering code of length 6 and radius r using Lemma 5
