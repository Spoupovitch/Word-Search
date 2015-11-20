//Trevor Jenkins
//T3672510
//TR566203

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WordSearch.h"

#define DEBUG 0

void buildStrings(Dictionary *dict, WordSearchPuzzle *puzzle);

int main (void) {
	int row, col, i, max;
	char *str = malloc(sizeof(char) * (MAX_WORD_LENGTH + 1));
	char temp[2];
	Dictionary *dict = malloc(sizeof(Dictionary));
	WordSearchPuzzle *puzzle = malloc(sizeof(WordSearchPuzzle));
	
	readDictionary(dict);
	
	readPuzzle(puzzle);
	
	//set bigger dimension of puzzle, use for determining
	//length of diagonal for() loops
	if (puzzle->height > puzzle->width) {
		max = puzzle->height;
	} else {
		max = puzzle->width;
	}
	
	temp[1] = '\0';
	
	for (row = 0; row < puzzle->height; row++) {
		for (col = 0; col < puzzle->width; col++) {
			
			//clear array, except for char at index 0
			for (i = 1; i < MAX_WORD_LENGTH + 1; i++) {
				str[i] = '\0';
			}
			
			//single char strings
			*str = puzzle->grid[row][col];
			checkString(dict, str);
			//printf("S-C str %d: %s\n",row + 1, str);
			
			//build strings horizontally-right
			for (i = 1; i < puzzle->width; i++) {
				//make sure not to go too far!
				if (col + i < puzzle->width) {
					temp[0] = puzzle->grid[row][col + i];
					str = strcat(str, temp);
					checkString(dict, str);
					//printf("H-R str %d: %s\n", i, str);
				}
			}
			
			//clear array, except for char at index 0
			for (i = 1; i < MAX_WORD_LENGTH + 1; i++) {
				str[i] = '\0';
			}
			
			//build strings horizontally-left
			for (i = 1; i < puzzle->width; i++) {
				//make sure not to go too far!
				if (col - i > 0) {
					temp[0] = puzzle->grid[row][col - i];
					str = strcat(str, temp);
					checkString(dict, str);
					//printf("H-L str %d: %s\n", i, str);
				}
			}
			
			//clear array, except for char at index 0
			for (i = 1; i < MAX_WORD_LENGTH + 1; i++) {
				str[i] = '\0';
			}
			
			//build strings vertically-down
			for (i = 1; i < puzzle->height; i++) {
				if (row + i < puzzle->height) {
					temp[0] = puzzle->grid[row + i][col];
					str = strcat(str, temp);
					checkString(dict, str);
					//printf("V-D str %d: %s\n", i, str);
				}
			}
			
			//clear array, except for char at index 0
			for (i = 1; i < MAX_WORD_LENGTH + 1; i++) {
				str[i] = '\0';
			}
			
			//build strings vertically-up
			for (i = 1; i < puzzle->height; i++) {
				//why is this >=? top row of puzzle (height/width ints)hindering correct reading?
				if (row - i >= 0) {
					temp[0] = puzzle->grid[row - i][col];
					str = strcat(str, temp);
					checkString(dict, str);
					//printf("V-U str %d: %s\n", i, str);
				}
			}
			
			//clear array, except for char at index 0
			for (i = 1; i < MAX_WORD_LENGTH + 1; i++) {
				str[i] = '\0';
			}
			
			//build string diagonally up-left
			for (i = 1; i <= max; i++) {
				if (row - i >= 0 && col - i >= 0) {
					temp[0] = puzzle->grid[row - i][col - i];
					str = strcat(str, temp);
					checkString(dict, str);
					//printf("Dg-UL str %d: %s\n", i, str);
				}
			}
			
			//clear array, except for char at index 0
			for (i = 1; i < MAX_WORD_LENGTH + 1; i++) {
				str[i] = '\0';
			}
			
			//build string diagonally up-right
			for (i = 1; i < max; i++) {
				if (row - i >= 0 && col + i < puzzle->width) {
					temp[0] = puzzle->grid[row - i][col + i];
					str = strcat(str, temp);
					checkString(dict, str);
					//printf("Dg-UR str %d: %s\n", i, str);
				}
			}
			
			//clear array, except for char at index 0
			for (i = 1; i < MAX_WORD_LENGTH + 1; i++) {
				str[i] = '\0';
			}
			
			//build string diagonally down-left
			for (i = 1; i < max; i++) {
				if (row + i < puzzle->height && col - i >= 0) {
					temp[0] = puzzle->grid[row + i][col - i];
					str = strcat(str, temp);
					checkString(dict, str);
					//printf("Dg-DL str %d: %s\n", i, str);
				}
			}
			
			//clear array, except for char at index 0
			for (i = 1; i < MAX_WORD_LENGTH + 1; i++) {
				str[i] = '\0';
			}
			//build string diagonally down-right
			for (i = 1; i < max; i++) {
				if (row + i < puzzle->height && col + i < puzzle->width) {
					temp[0] = puzzle->grid[row + i][col + i];
					str = strcat(str, temp);
					checkString(dict, str);
					//printf("Dg-DR str %d: %s\n", i, str);
				}
			}
		}
	}
	
	for (i = 0; i < dict->size; i++) {
		if (dict->counts[i] > 0) {
			printf("%s (%d)\n", dict->words[i], dict->counts[i]);
		}
	}
	
	destroyDictionary(dict);
	destroyPuzzle(puzzle);
	
	free(str);
	str = NULL;
	
	return 0;
}

int readDictionary(Dictionary *dict) {
	int row, col;
	//---------------CHANGE DICTIONARY HERE!------//
	FILE *ifp = fopen("dictionary.txt", "r");
	//---------------CHANGE DICTIONARY HERE!------//
	
	//use temp_array to figure out strlen()
	char array[MAX_WORD_LENGTH + 1];
	
	fscanf(ifp, "%d", &dict->size);
	
	//malloc() first dimension of words[][]
	dict->words = malloc(sizeof(char *) * (dict->size));
	
	//return 0 if pointer remains NULL after calling malloc()
	if (dict->words == NULL) {
		return 0;
	}
	
	//malloc() second dimension of words[][]
	for (row = 0; row < dict->size; row++) {
		//set array equal to current line of dictionary.txt
		fscanf(ifp, "%s", array);
		
		//malloc() just enough space on current row of dict->words[][]
		dict->words[row] = malloc(sizeof(char) * (strlen(array) + 1));
		
		//return 0 if pointer remains NULL after calling malloc()
		if (dict->words[row] == NULL) {
			destroyDictionary(dict);
			return 0;
		}
		//read in words from array into dict->words
		strcpy(dict->words[row], array);
	}
	
	//malloc() counts[] array
	dict->counts = malloc(sizeof(int) * dict->size);
	
	//clear memory and return 0 if malloc() fails
	if (dict->counts == NULL) {
		destroyDictionary(dict);
		return 0;
	}
	
	//print dictionary
	if (DEBUG) {
		printf("___________DICTIONARY____________\n");
		for (row = 0; row < dict->size; row++) {
				printf("%s\n", dict->words[row]);
		}
		printf("_________________________________\n\n");
	}
	
	fclose(ifp);
	return 1;
}

void destroyDictionary(Dictionary *dict) {
	int row;
	
	//free 2nd dimension's pointers first
	for (row = 0; row < dict->size; row++) {
		free(dict->words[row]);
		dict->words[row] = NULL;
	}
	
	//can now free pointer to 1st dimension
	free(dict->words);
	dict->words = NULL;
	
	free(dict->counts);
	dict->counts = NULL;
	
	dict->size = 0;
	
	//print out pointers
	if (DEBUG) {
		printf("____________FREE DICT____________\n");
		for (row = 0; row < dict->size; row++) {
			printf("dict->words[%d]: %p", row, dict->words[row]);
		}
		printf("dict->words: %p\ndict->counts: %p\ndict->size: %d\n", dict->words, dict->counts, dict->size);
		printf("_________________________________\n\n");
	}
}

int readPuzzle(WordSearchPuzzle *puzzle) {
	int row, col;
	
	scanf("%d %d", &puzzle->height, &puzzle->width);
	
	//malloc() 1st dimension of grid[][]
	puzzle->grid = malloc(sizeof(char *) * (puzzle->height));
	
	//catch any failed malloc()
	if (puzzle->grid == NULL) {
		destroyPuzzle(puzzle);
		return 0;
	}
	
	//malloc() 2nd dimension of grid[][]
	for (row = 0; row < puzzle->height; row++) {
		puzzle->grid[row] = malloc(sizeof(char) * (puzzle->width + 1));
	
	//catch any failed malloc() calls
		if (puzzle->grid[row] == NULL) {
			destroyPuzzle(puzzle);
			return 0;
		}
	}
	
	//populate grid[][] with puzzle
	for (row = 0; row < puzzle->height; row++) {
			scanf("%s", puzzle->grid[row]);
	}
	
	//print puzzle
	if (DEBUG) {
		printf("____________PUZZLE____________\n");
		for (row = 0; row < puzzle->height; row++) {
				printf("%s\n", puzzle->grid[row]);
		}
		printf("_______________________________\n\n");
	}
	return 1;
}

void destroyPuzzle(WordSearchPuzzle *puzzle) {
	int row;
	
	//free 2nd dimension of grid[][] first
	for (row = 0; row < puzzle->height; row++) {
		free(puzzle->grid[row]);
		puzzle->grid[row] = NULL;
	}
	
	//free 1st dimension pointer
	free(puzzle->grid);
	puzzle->grid = NULL;
	
	puzzle->height = 0;
	puzzle->width = 0;
	
	//print out pointers
	if (DEBUG) {
		printf("___________FREE PUZZLE____________\n");
		for (row = 0; row < puzzle->height; row++) {
			printf("puzzle->grid[%d]: %p", row, puzzle->grid[row]);
		}
		printf("puzzle->grid: %p\npuzzle->height: %d\npuzzle->width: %d\n", puzzle->grid, puzzle->height, puzzle->width);
		printf("__________________________________\n\n");
	}
}

int checkString(Dictionary *dict, char *str) {
    int min = 0, mid, max = dict->size-1;
	
	while (min <= max) {
		mid = min + (max - min)/2;

		if (strcmp(dict->words[mid], str) < 0) {
			min = mid + 1;
		
		} else if (strcmp(dict->words[mid], str) > 0) {
			max= mid - 1;
		
		} else {
			//change dict->counts index corresponding to found string
			dict->counts[mid]++;
			return 1;
		}
	}
	return 0;
}
