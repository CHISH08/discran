flag = 

Lw2 : main.o RB_tree.o
	g++ -Wall -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -o L2 main.o RB_tree.o $(flag)
main.o : main.cpp RB_tree.hpp
	g++ -std=c++14 -c main.cpp $(flag)
rb.o : RB_tree.cpp RB_tree.hpp
	g++ -std=c++14 -c RB_tree.cpp $(flag)
clear :
	rm *.o L2