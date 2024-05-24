CXX = g++
CXXFLAGS = 
BINARIES = lab07Test

all: ${BINARIES}

lab07Test: WordCount.o lab07Test.o tddFuncs.o
	${CXX} $^ -o $@

tests:
	./lab07Test

clean:
	rm ${BINARIES} *.o