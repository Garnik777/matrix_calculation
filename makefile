.PHONY: all generate program1 program2 test

all: generate program1 program2 test

generate: gene.cpp
	g++ -pg --coverage gene.cpp -o generate
	./generate
	@gcov gene.cpp -m

program1:task_matrix_combination.cpp
	g++ -pg --coverage task_matrix_combination.cpp -o program1
	./program1
	@gcov task_matrix_combination.cpp -m

program2:main.cpp 
	g++ -pg --coverage main.cpp -o program2
	./program2
	@gcov main.cpp -m
test: test.cpp
	g++ -pg --coverage test.cpp -o test -ftime-report
	./test
	@gcov test.cpp -m
clean:
	rm -f generate program1 program2 test 
