//sat.h ~ Implementation of Satisfiability Instances and related functions by Onat Tevfik Bilgili
#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

class SAT{
	public:
	
		//Getters
		unsigned int num_var() const;//returns number of variables
		unsigned int num_cls() const;//returns number of clauses
		unsigned int len(unsigned int x) const;//returns the size of the x-th clause
		unsigned int get_k() const;//returns the size of the largest clause
		std::vector<int> get_cls(unsigned int x) const;//returns the x-th clause
		int get(unsigned int x,unsigned int y) const;//returns the y-th variable of the x-th clause


		//Constructors
		SAT(unsigned int n, std::vector<std::vector<int>> inst);//number of variables and the instance as a vector of vectors

		//Instance Methods
		void print();

	private:
		unsigned int _num_var;//Number of variables in the instance
		unsigned int _num_cls;//Number of clauses in the instance
		std::vector<std::vector<int>> instance;//SAT instance as a nested vector of integers
};

SAT read_SAT(char* filename);//reads SAT instance from an input file
//SAT set_literal(const SAT& formula, const int literal, const bool value);//derives the formula when the literal l is set to value v within the given formula
bool empty_clauses(const SAT& formula);//tests if the formula has empty clauses

class Assignment{
	public:
		//getters
		unsigned int num_var() const;//returns the number of variables
		bool get(unsigned int n) const;//returns the value of n-th variable

		//setters
		void set(unsigned int n,bool x);//sets the value of n-th variable to x

		//constructor
		Assignment(std::vector<bool> var);//takes a vector of boolean variables as an input

		//print
		void print();
	private:
		unsigned int _num_var;
		std::vector<bool> variables;
};

bool test(const SAT& Instance, const  Assignment& Values);
unsigned int first_wrong_clause(const SAT& Instance, const Assignment& Values);//returns the index of the first false clause under given assignment or the number of clause if the formula is satisfied
