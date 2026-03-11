//is_satisfiable.cpp ~ implementation of is_satisfiable.h
#include "is_satisfiable.h"

bool small_sat(const SAT& formula, const unsigned int r){//function for solving SAT problems with less than 7 variables
	std::vector<bool> fix_status(6,false);//saves the information, whether given literals have been fixed before
	Code cover = small_cover(6,r);
	for(Assignment asgn : cover){
		if(local_search(formula,asgn,r,fix_status)){
			return true;
		}
	}
	return false;
}

bool is_satisfiable(const SAT& formula){//the main algorithm for solving SAT problems using Lemma 6 and Theorem 1
	
	if(empty_clauses(formula)){return false;}//instances with empty clauses allways false
	
	unsigned int org_num_var = formula.num_var();//Number of variables which is not necessarily divisible by 6
	
	if(org_num_var < 7){return small_sat(formula,2);}//Easier to solve if there are less then 7 variables
	
	unsigned int m = formula.num_cls();
	if(m == 0){return true;}//Empty Instance allways true
	
	unsigned int k = formula.get_k();//maximal clause length
	if(k == 0){return false;}//Empty Clause allways false, we now instance has clauses because of line 19
	
	unsigned int num_var = (org_num_var / 6) * 6;//if number of variables is not divisible by 6 we make increase it to make it so
	if(num_var != org_num_var){num_var = ((num_var/6) + 1) * 6;}
	
	std::vector<bool> fix_status(num_var,false);//saves the information, whether given literals have been fixed before
	
	//Generate covering code of length ~num_var~ using Lemma 6 and local search
	
	double rho = 1 / (k + 1); //calculate normalised radius from the algorithm
	unsigned int small_radius = (unsigned int)(rho * (double)(num_var/6));
	Code smallcover = small_cover(num_var / 6, small_radius);//Construct a covering code of length ~num_var~ / 6 and raius rho * ~num_var~ / d using Lemma 5
	unsigned int small_cover_size = smallcover.size();
	//Generate bigger covering code
	std::vector<unsigned int> counter(6,0);
	bool not_yet = true;//have not yet tested for all assignments in the bigger covering code of length n
	
	//Create an Assignment which will be owerwritten in our Algorithm
	std::vector<bool> vars(num_var,false);
	Assignment candidate(vars);
	while(not_yet){
		//find new center in the cover
		for(unsigned int i = 0; i < 6;i++){
			for(unsigned int j = 0; j < (num_var / 6); j++){
				unsigned int digit = i * (num_var / 6) + j;
				bool value = smallcover[counter[i]].get(j);
				candidate.set(digit,value);
			}
		}
		
		//local search
		unsigned int big_radius = small_radius *6;
		if(local_search(formula,candidate,big_radius,fix_status)){return true;}//there is a satisfying assignment within big_radius distance of candidate
		
		//move to the next candidate
		not_yet = increase1(counter,small_cover_size);
	}
	
	return false;
}
