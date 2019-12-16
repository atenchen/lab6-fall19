FLAGS = -Wall -Werror -g -std=c++14
FILE1 = Trie
FILE2 = ProbSearch
FILE3 = lab6

all: $(FILE1)

$(FILE1): $(FILE1).o $(FILE3).o
	g++ $(FLAGS) $(FILE1).o $(FILE3).o -o $(FILE1)

$(FILE1).o: $(FILE1).cpp $(FILE2).h
	g++ -c $(FLAGS) $(FILE1).cpp -o $(FILE1).o

$(FILE3).o: $(FILE3).cpp
	g++ -c $(FLAGS) $(FILE3).cpp -o $(FILE3).o

.PHONY: clean run all
run: all
	./$(FILE1)

memcheck: all
	valgrind --leak-check=full ./$(FILE1)

clean:
	rm -rf *.o $(FILE1)
