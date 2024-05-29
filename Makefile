CXX = g++
CXXFLAGS = 
BINARIES = lab07Test lab07Test2

all: ${BINARIES}

lab07Test: WordCount.o lab07Test.o tddFuncs.o
	${CXX} $^ -o $@

lab07Test2: WordCount.o lab07Test2.o tddFuncs.o
	${CXX} $^ -o $@

tests:
	./lab07Test
	./lab07Test2

clean:
	rm ${BINARIES} *.o