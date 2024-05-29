#include "tddFuncs.h"
#include "WordCount.h"
#include <iostream>
using namespace std;

int main(){
    WordCount book = WordCount();
    book.addAllWords("and,1 example,1 newlines,1 \
    sentence,1 spaces,1 \n\n\n\nsome,2 with,2 Actual: an,1 \
    example,1 newlines,1 \n\nsentence,1 spaces,1\n\n some,2 with,2");
    ASSERT_EQUALS(2, book.getWordCount("sentence"));
    ASSERT_EQUALS(2, book.getWordCount("newlines"));
    ASSERT_EQUALS(2, book.getWordCount("an"));
    ASSERT_EQUALS(2, book.getWordCount("actual"));
    ASSERT_EQUALS(2, book.getWordCount("with"));
    ASSERT_EQUALS(2, book.getWordCount("some"));
}