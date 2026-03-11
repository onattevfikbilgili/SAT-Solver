//local_search.cpp ~ Implementation of local_search.h

#include "local_search.h"
bool clauses_fixed_false(const SAT& formula, const Assignment& Values, const std::vector<bool>& fix_status, const unsigned int& first_wrong_clause, const unsigned int& cls){ //checks whether a clause has been fixed to be false
	for(unsigned int i = first_wrong_clause; i < cls; i++){//iterate over clauses starting from the first clause which was assigned false, number of clausesand the index of the first wrong clause are taken as an input to save time
		unsigned int len = formula.len(i);
		bool cls_fixed_false = true;//clause is initially assumed to be fixed false
		for(unsigned int j = 0; j < len and cls_fixed_false; j++){//iterate over literals
			int literal = formula.get(i,j);//read the j-th literal of the i-th clause
			int var_index = abs(literal) - 1;//variable indices in an Assignment start with 0 and not 1
			bool val1 = fix_status[var_index];
			bool val2 = Values.get(var_index);
			if((literal > 0 and (val2 or not val1)) or (literal < 0 and (not val2 or not val1))){
				cls_fixed_false = false;
			}
		}
		if(cls_fixed_false){return true;}
	}
	return false;
}

bool local_search(const SAT& formula, Assignment& values, const int radius, std::vector<bool>& fix_status){//inputs are the formula, an assignment, a positive intiger valued radius, and an array of length n which saves whether literals have been fixed before or not
	//We will not check if fix_status is of length n in the recursive algorithm to save time,
	unsigned int m = formula.num_cls();
	unsigned int i = first_wrong_clause(formula,values);//pick a clause that is false under assignment or the information that the instance is satisfied
	if(i == m){return true;}//i is m iff formula is satisfied under assignment
	if(radius <= 0){return false;}
	/*
	We dont check for empty clauses, as the algorithm does not erase variables and we will check for empty clauses in the main algorithm
	Instead, we check for clauses, in which all literals have been fixed to the value false
	*/
	if(clauses_fixed_false(formula,values,fix_status,i,m)){return false;}
	
	unsigned int k = formula.len(i);
	for(unsigned int j = 0; j < k; j++){//iterate over literals in this clause
		int literal = formula.get(i,j);
		unsigned int var_index = (unsigned int)(abs(literal) -1);
		if(not fix_status[var_index]){//if the literal has not been fixed before
			//fixing the variable
			bool val = true;
			if(literal < 0){val = false;}
			fix_status[var_index] = true;
			values.set(var_index,val);
			
			//no need to calculate formula after fixing literal, we will fix the literal in the assignment instead
			if(local_search(formula,values, radius - 1,fix_status)){return true;}
			
			//undo the literal fix
			fix_status[var_index] = false;
			values.set(var_index,not val);
		}
	}
	return false;
}
