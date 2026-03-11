#include <iostream>
#include <vector>
#include "sat.h"
#include "local_search.h"
#include "covering_code.h"
#include "is_satisfiable.h"

int main(int argc, char** argv){
	if(argc > 1){
		SAT formula = read_SAT(argv[1]);
		if(is_satisfiable(formula)){
			std::cout<<"The given SAT instance is satisfiable.\n";
		}
		else{
			std::cout<<"The given SAT instance is NOT satisfiable.\n";
		}
	}
	else{
		std::cout << "No input is given. Correct usage is as follows:\nsolve FILENAME\nwhere FILENAME is the name of the file, in which the SAT instance is contained.\n";
	}
	return 0;
}
