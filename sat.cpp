//sat.cpp ~ Implementation of sat.h
#include "sat.h"

//Functions of class SAT
//getters
unsigned int SAT::num_var() const {return _num_var;}
unsigned int SAT::num_cls() const {return _num_cls;}
unsigned int SAT::len(unsigned int x) const {return instance[x].size();}//returns the size of the x-th clause
std::vector<int> SAT::get_cls(unsigned int x) const {return instance[x];}
int SAT::get(unsigned int x,unsigned int y) const {return instance[x][y];}
unsigned int SAT::get_k() const{
	unsigned int k = 0;
	for(unsigned int i = 0; i < _num_var; i++){
		unsigned int k_ = instance[i].size();
		if(k < k_){k = k_;}
	}
	return k;
}

//constructor
SAT::SAT(unsigned int n, std::vector<std::vector<int>> inst){
	_num_var = n;
	_num_cls = inst.size();
	instance = inst;
}

//print
void SAT::print(){
	std::cout << _num_var << " variables, " << _num_cls << " clauses\n";
	for(int i = 0; i < (int)_num_cls; i++){
	       for(int j = 0; j < (int)instance[i].size(); j++){
		       std::cout << instance[i][j] << " ";
	       }
	       std::cout << "\n";
	}
}
/*
SAT set_literal(const SAT& formula, const int literal, const bool value){//derives the formula when the literal l is set to value v within the given formula
	unsigned int m = formula.num_cls();
	unsigned int n = formula.num_var();
	std::vector<std::vector<int>> new_instance;
	for(unsigned int i = 0; i < m; i++){//iterate over clauses
		std::vector<int> new_clause;
		bool yields_true = false;
		unsigned int k = formula.len(i);
		for(unsigned int j = 0; j < k and not yields_true; j++){//iterate over literals within the clause
			int l = formula.get(i,j);
			if(abs(l) != abs(literal)){new_clause.push_back(l);}
			else{
				if((l < 0 and value == false) or (l > 0 and value == true)){//clause set to true, delete clause
					yields_true = true;
				}
				//else the literal has the value false and therefore may be skipped
			}
		}
		if(not yields_true){new_instance.push_back(new_clause);}
	}
	SAT out(n,new_instance);
	return out;
}*/

bool empty_clauses(const SAT& formula){
	unsigned int m = formula.num_cls();
	for(unsigned int i = 0; i < m; i++){
		if(formula.len(i) == 0){return true;}
	}
	return false;
}

SAT read_SAT(char* filename){//reads SAT instance from an input file
	std::ifstream file(filename); //open file
	if(not file){throw std::runtime_error("Can not open file!");}
	std::string line;
	std::vector<std::vector<int>> pre_SAT;
	bool read_specs = false; //have read the number of variables
	unsigned int num_var;
	while(std::getline(file,line)){
		if(line[0] != 'c'){
			std::stringstream ss(line);
			if(not read_specs and line[0] == 'p'){
				std::string garb1, garb2; // the first 2 words in the first non comment line are unimportant
				ss >> garb1 >> garb2 >> num_var;
				if(not ss){throw std::runtime_error("Invalid file format!");}
				read_specs = true;//read number of variables
			}
			if(read_specs and line[0] != 'p'){
				bool end_of_clause = false;
				std::vector<int> clause;
				while(not end_of_clause){//read literals untill end of clause
					int literal;
					ss >> literal;
					if(not ss){throw std::runtime_error("Invalid file format!");}
					if(abs(literal) > num_var){throw std::runtime_error("Invalid literal in formula!");}
					if(literal != 0){
						clause.push_back(literal);
					}
					else{end_of_clause = true;}
				}
				pre_SAT.push_back(clause);//push the clause into instance
			}
		}
}
	file.close();
	SAT out(num_var,pre_SAT);
	return out;
}


//Functions of Assignment
//getters
unsigned int Assignment::num_var() const {return _num_var;}
bool Assignment::get(unsigned int n) const {return variables[n];}
//setters
void Assignment::set(unsigned int n,bool x){variables[n] = x;}
//constructors
Assignment::Assignment(std::vector<bool> var){
	_num_var = var.size();
	variables = var;
}
//print
void Assignment::print(){
	std::cout << "< ";
	for(unsigned int i = 0; i < _num_var; i++){
		if(variables[i]){std::cout << "T ";}
		else{std::cout << "F ";}
	}
	std::cout << ">\n";
}


//other functions
bool test(const SAT& Instance, const  Assignment& Values){//tests if a given assignment to the variables satisfies the formula or not
	bool out = true;//formula is assumed to be satisfied by a given assignment untill an unsatisfied clause is found
	unsigned int cls = Instance.num_cls();
	if(Instance.num_var() > Values.num_var()){throw std::runtime_error("Number of variables in the SAT Instance is greater than the number of variables in the assignment!");}
	for(unsigned int i = 0; i < cls and out; i++){//iterate over clauses
		unsigned int len = Instance.len(i);
		bool satisfied_cls = false;//the clause is assumed to be unsatisfied untill a satisfied literal is found
		for(unsigned int j = 0; j < len and not satisfied_cls; j++){//iterate over literals
			int literal = Instance.get(i,j);//read the j-th literal of the i-th clause
			int var_index = abs(literal) - 1;//variable indices in an Assignment start with 0 and not 1
			bool val = Values.get(var_index);
			if((literal > 0 and val) or (literal < 0 and not val)){
				satisfied_cls = true;
			}
		}
		if(not satisfied_cls){
			out = false;
		}

	}
	return out;
}

unsigned int first_wrong_clause(const SAT& Instance, const Assignment& Values){//returns the index of the first false clause under given assignment or the number of clause if the formula is satisfied
	unsigned int out = 0;
	bool is_sat = true;
	unsigned int m = Instance.num_cls();
	if(Instance.num_var() > Values.num_var()){throw std::runtime_error("Number of variables in the SAT Instance is greater than the number of variables in the assignment!");}
	for(unsigned int i = 0; i < m and is_sat; i++){//iterate over clauses
		unsigned int k = Instance.len(i);
		bool satisfied_cls = false;
		for(unsigned int j = 0; j < k and not satisfied_cls; j++){
			int literal = Instance.get(i,j);
			int var_index = abs(literal) - 1;
			bool var = Values.get(var_index);
			if((literal > 0 and var) or (literal < 0 and not var)){
				satisfied_cls = true;
			}
		}
		if(not satisfied_cls){
			is_sat = false;
			out = i;
		}
	}
	if(is_sat){return m;}//there are no clauses with index m as the first clause has index 0
	return out;
}
