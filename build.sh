#!/bin/sh
g++ -O3 -Wall -Wextra -Wpedantic -Werror -o solve main.cpp sat.cpp local_search.cpp covering_code.cpp is_satisfiable.cpp
#mv solve ~/.local/bin/
