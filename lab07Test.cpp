#include "tddFuncs.h"
#include "WordCount.h"
#include <iostream>
using namespace std;

int main(){
    WordCount book = WordCount();

    cout << "Basic Tests" << endl << "____________" << endl;
    book.addAllWords("----&&8T^^##$$his  ,, th^^7&32is\nis    is **is a test  ,,\n\n\t, test test ,,,\n\ntest sente32923nc**9902e---\t\t");
    ASSERT_EQUALS(2, book.getWordCount("this"));
    ASSERT_EQUALS(3, book.getWordCount("is"));
    ASSERT_EQUALS(1, book.getWordCount("a"));
    ASSERT_EQUALS(4, book.getWordCount("test"));
    ASSERT_EQUALS(1, book.getWordCount("sentence"));

    cout << endl << "Sorted By Word" << endl;
    book.dumpWordsSortedByWord(cout);
    cout << endl << "Sorted By Occurence" << endl;
    book.dumpWordsSortedByOccurence(cout);
    book.decrWordCount("this");
    book.decrWordCount("this");
    book.decrWordCount("is");
    book.decrWordCount("is");
    book.decrWordCount("is");
    book.decrWordCount("a");
    book.decrWordCount("test");
    book.decrWordCount("test");
    book.decrWordCount("test");
    book.decrWordCount("test");
    book.decrWordCount("sentence");

    ASSERT_EQUALS(0, book.getTotalWords());

    cout << endl << "Edge Case Tests" << endl << "____________" << endl;

    book.addAllWords("----");
    book.addAllWords("     ");
    book.addAllWords("---This ____is--- is2**");
    ASSERT_EQUALS(2, book.getWordCount("is"));
    ASSERT_EQUALS(1, book.getWordCount("this"));

    cout << endl << "Sorted By Occurence" << endl;
    book.dumpWordsSortedByOccurence(cout);
    cout << endl << "Sorted By Word" << endl;
    book.dumpWordsSortedByWord(cout);

    book.addAllWords("\n\n\nNewLIne\n\n\n\n Testing\n\n\n\nWith\n\n\nNewline");
    ASSERT_EQUALS(1, book.getWordCount("testing"));
    ASSERT_EQUALS(2, book.getWordCount("newline"));
    ASSERT_EQUALS(1, book.getWordCount("with"));
}