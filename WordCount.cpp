// WordCount.cpp

#include "WordCount.h"
#include <set>

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int wordCount = 0;
	//Iterate through entries in table
	for(size_t i = 0; i < CAPACITY; i++){
		int size = table[i].size();
		//Iterate through entries in vector
		for(int j = 0; j < size; j++){
			//Add the number of occurances of each word to total
			wordCount += table[i][j].second;
		}
	}
	return wordCount;
}

int WordCount::getNumUniqueWords() const {
	int uniqueCount = 0;
	//Iterate through entries
	for(size_t i = 0; i < CAPACITY; i++){
		//Increment for every pair entry in a vector
		uniqueCount += table[i].size();
	}
	return uniqueCount;
}

int WordCount::getWordCount(std::string word) const {
	//Make word a valid word
	word = makeValidWord(word);

	//Check if word is empty after making valid
	if(word.length() == 0) return 0;

	//Hash to get position in table
	int pos = hash(word);
	if(table[pos].empty()){
		return 0;
	}

	//Look through vector at hash position
	for(size_t i = 0; i < table[pos].size(); i++){
		//If word exists, return its number of occurances
		if(table[pos][i].first == word){
			return table[pos][i].second;
		}
	}
	//If word isn't found return 0
	return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	//Make word a valid word
	word = makeValidWord(word);
	//If word is empty after becoming valid, return 0
	if(word == "") return 0;

	//Find position with hash function
	int pos = hash(word);

	//Iterate through vector at hash pos
	for(size_t i = 0; i < table[pos].size(); i++){
		//If word found, increment count
		if(table[pos][i].first == word){
			table[pos][i].second++;
			return table[pos][i].second;
		}
	}
	//If not found, add the word to the table with 1 occurance
	table[pos].push_back({word, 1});
	return 1;
}

int WordCount::decrWordCount(std::string word) {
	//Make word valid
	word = makeValidWord(word);
	//Check if empty string
	if(word.length() == 0) return -1;

	//Find hash pos
	int pos = hash(word);
	if(table[pos].empty()) return -1;

	auto it = table[pos].begin(); //Iterator through vector

	//Iterate through entries in vector
	while(it != table[pos].end()){
		if(word == it->first){
			//If word is found check occurances, if > 1 decrement
			if(it->second > 1){
				it->second--;
				return it->second;
			} else{
				//If 0, remove word from table
				table[pos].erase(it);
				return 0;
			}
		}
		it++;
	}
	return -1;
}


bool WordCount::isWordChar(char c) {
	if(isalpha(c) == 0){
		return false;
	}
	return true;
}

std::string WordCount::makeValidWord(std::string word) {
	int length = word.length();
	std::string validWord = "";
	int validEnd;

	//Iterate through chars of word
	for(int i = 0; i < length; i++){
		//Find end pos of valid word, if length is 0 should be 0, otherwise length - 1
		validEnd = (validWord.length() == 0) ? 0 : validWord.length() - 1;
		//Check if current char is alpha letter
		if(!isWordChar(word[i])){
			//If not, look at most recent addition to validWord, if - or ' don't add another
			if((validWord[validEnd] == '-' || validWord[validEnd] == '\'') && (word[i] == '-' || word[i] == '\'')){
				continue;
			} else if((i != 0 && i != length - 1) && ((word[i] == '-' || word[i] == '\''))){
				//If not in first or last pos, add to validWord
				validWord += word[i];
			}
		} else{
			validWord += word[i];
		}
	}
	//Make all lowercase
	std::transform(validWord.begin(), validWord.end(), validWord.begin(), ::tolower);
	if(validWord == word){
		return validWord; //If no changes to word, return validWord
	}
	return makeValidWord(validWord); //If changes made, run again to check for additional changes
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	set<pair<string, int>, greater<pair<string, int>>> wordList;

	for(size_t i = 0; i < CAPACITY; i++){
		for(size_t j = 0; j < table[i].size(); i++){
			wordList.insert(table[i][j]);
		}
	}
	for(auto word : wordList){
		out << word.first << "," << word.second << endl;
	}
	return;
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	set<pair<int, string>> wordList;

	for(size_t i = 0; i < CAPACITY; i++){
		for(size_t j = 0; j < table[i].size(); i++){
			wordList.insert({table[i][j].second, table[i][j].first});
		}
	}
	for(auto word : wordList){
		out << word.second << "," << word.first << endl;
	}
	return;
}

void WordCount::addAllWords(std::string text) {
	size_t find = text.find_first_of(" ,\n\t");
	while(find < text.length()){
		incrWordCount(makeValidWord(text.substr(0, find + 1)));
		text.erase(0, find + 1);
		find = text.find_first_of(" \n\t");
		if(find == string::npos){
			incrWordCount(makeValidWord(text.substr(0)));
		}
	}
	return;
}
