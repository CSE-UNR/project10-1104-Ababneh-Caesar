/*
 * Author: Caesar Ababneh
 * Date: 5/2/2025
 * Purpose: This program plays a text-based Great Value version of Wordle against the user.
 */

#include <stdio.h>

#define WORD_LENGTH 6
#define MAX_GUESSES 6


void input (int, char [MAX_GUESSES] [WORD_LENGTH]);
void loadWord (char [WORD_LENGTH]);
void lowerCaseify (char [WORD_LENGTH]);
void upperCaseify (char [WORD_LENGTH]);
void compareWords(char [WORD_LENGTH], char [WORD_LENGTH]);
int match(char [WORD_LENGTH], char [WORD_LENGTH]);
void bar();


int main () {
	const char exclamation [6][12] = {"\t\tGOATED!", "\t\tAmazing!", "\t\tNice!", "\t\tNice!", "\t\tNice!", "" };
	char mystery_word [WORD_LENGTH];
	char entries [MAX_GUESSES] [WORD_LENGTH] = {"\0","\0","\0","\0","\0","\0"};
	/* This looks weird but it is necessary. */

	loadWord(mystery_word);
	if (!mystery_word) printf("The File couldn't be opened or something.");
	else {
		int trigger = 0, guess;
		for (guess = 0; guess < MAX_GUESSES && !trigger; guess++) {
			input (guess, entries);
			bar();
			for (int i = 0; i < MAX_GUESSES; i++) {
				if (entries[i][0] > 0) {
					trigger = match(mystery_word, entries[i]);
					if (!trigger) compareWords(mystery_word, entries[i]);
				}
			}
		}
		if (trigger) {
			upperCaseify(mystery_word);
			printf("\t\t%s\n\t", mystery_word);
			printf("You won in %d guess", guess);
			if (guess > 0) printf("es");
			printf("!\n%s\n", exclamation[guess - 1]);
		} else {
			printf("You lost, better luck next time!\n");
		}
	}
	return 0;
}

void bar() {
	printf("================================\n");
}

void cleanStdin() {
	char trash;
	while (scanf("%c", &trash) > -1 && trash != '\n') printf("\nFIXIN STUFF\n");
}
void input (int guess_num, char list [MAX_GUESSES] [WORD_LENGTH]) {
	char word [WORD_LENGTH + 1] = "\0";
	if (guess_num < 5) printf("GUESS %d! Enter your guess: ", guess_num + 1);
	else printf("FINAL GUESS : ");
	int end, flag;
	do {	
		flag = 1;
		fgets(word, WORD_LENGTH + 1, stdin);
		for (end = 0; word [end] != '\0'; end++);
		if (end < WORD_LENGTH || word [WORD_LENGTH - 1] != '\n') {
			printf("Your guess must be 5 letters long.\nPlease try again: ");
			flag = 0;
			char trash;
			while (scanf("%c", &trash) > -1 && trash != '\n');
		} else for (int i = 0; i < WORD_LENGTH - 1; i++) {
			char c = word[i];
			if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
				flag = 0;
				printf("Your guess must contain only letter.\nPlease try again: ");
				i = WORD_LENGTH;
			}
		}
	} while (!flag);
	lowerCaseify (word);
	for (int i = 0; i < WORD_LENGTH; i++) list [guess_num] [i] = word [i];
	list [guess_num] [WORD_LENGTH - 1] = '\0';
}

void loadWord (char word [WORD_LENGTH]) {
	FILE* fp = fopen("word.txt", "r");
	if (fp == NULL) word [0] = '\0';
	else fgets (word, WORD_LENGTH, fp);
	lowerCaseify (word);
	fclose(fp);
}

void lowerCaseify (char word [WORD_LENGTH]) {
	for (int i = 0; i < WORD_LENGTH - 1; i++) {
		if (word [i] < 'a') word [i] += 'a' - 'A';
	}
	/* ASCII codes 97 and 65 respectively */
}

void upperCaseify (char word [WORD_LENGTH]) {
	for (int i = 0; i < WORD_LENGTH - 1; i++) {
		if (word [i] > 'a' - 1) word [i] -= 'a' - 'A';
	}
	/* ASCII codes 97 and 65 respectively */
}

void compareWords (char a [WORD_LENGTH], char b [WORD_LENGTH]) {
	char pointers [5] = {' ', ' ', ' ', ' ', ' '};
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (a[i] == b[j]) {
			       	if (i == j) b[j] -= 'a' - 'A';
				else pointers[j] = '^';
			}
		}
	}
	printf("%s\n%s\n", b, pointers);
}

int match (char a [WORD_LENGTH], char b [WORD_LENGTH]) {
	lowerCaseify(b);
	int matches = 0;
	for (int i = 0; i < WORD_LENGTH -1; i++) {
		if (a [i] == b [i]) matches ++;
	}
	return (matches == WORD_LENGTH - 1);
}

