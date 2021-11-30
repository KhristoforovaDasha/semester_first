CXXFLAGS +=  -g -Og -fsanitize=address,undefined -Wall -Wextra
CC=g++

program: main.o  
	$(CC) main.o -o program

main.o: main.cpp string.h
	$(CC) -c  main.cpp

tester: tester.o tests.o
	$(CC) $(CXXFLAGS) -o tester tester.o tests.o -lasan

tests.o: tests.cpp tests.h
	$(CC) -c  $(CXXFLAGS) tests.cpp

tester.o: tester.cpp tests.h
	$(CC) -c  $(CXXFLAGS) tester.cpp

clean:
	rm *o
	rm program
	rm tester

test: tester
	./tester  
