.PHONY: all generate program1 program2 test

all: generate program1 program2 test

generate: gene.cpp
	g++ -pg gene.cpp -o generate
	./generate

program1:task_matrix_combination.cpp
	g++ -pg task_matrix_combination.cpp -o program1
	./program1

program2:main.cpp 
	g++ -pg main.cpp -o program2
	./program2
test: test.cpp
	g++ -pg test.cpp -o test -ftime-report
	./test	
clean:
	rm -f generate program1 program2 test 
