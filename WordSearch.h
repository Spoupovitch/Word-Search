#ifndef __WORD_SEARCH_H
#define __WORD_SEARCH_H


// Maximum length of any word in the dictionary. You should not hard code the
// number 20 into any of your code. You should instead use the MAX_WORD_LENGTH
// identifier, in case we decide to tweak this value while testing your code.
#define MAX_WORD_LENGTH 20

typedef struct WordSearchPuzzle
{
	// 2D array of characters (i.e., an array of char arrays) for storing the
	// word grid for this puzzle. Must be dynamically allocated at runtime.
	char **grid;

	// Height of the puzzle grid (number of lines).
	int height;

	// Width of the puzzle grid (number of characters per line).
	int width;

} WordSearchPuzzle;

typedef struct Dictionary
{
	// A 2D char array (i.e., an array of strings; an array of char arrays) for
	// storing the words in the dictionary file.
	char **words;

	// A 1D integer array to track how many times each word from the dictionary
	// is found in the word grid for a given puzzle. Must be dynamically
	// allocated at runtime.
	int *counts;

	// The number of words in the dictionary.
	int size;
} Dictionary;


// Functional prototypes. See assignment PDF for descriptions.

int readDictionary(Dictionary *dict);

void destroyDictionary(Dictionary *dict);

int readPuzzle(WordSearchPuzzle *puzzle);

void destroyPuzzle(WordSearchPuzzle *puzzle);

int checkString(Dictionary *dict, char *str);


#endif
