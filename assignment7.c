//Author Peter Adamson

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 500

typedef struct words Words;
struct words{
	char* word;
	int freq;
	Words* next;
};

Words *addWord(Words* headPtr, char* newWord);
void printWords(Words* headPtr);
void deleteList(Words** headPtr);
char *readWord(); 

int main(){
	Words* list = NULL;
	char newWord[MAXLEN];
	while(scanf("%s",newWord) == 1){
		list = addWord(list,newWord);
	}
	printWords(list);
	deleteList(&list);
	return 1;
}

//Inserts a copy of newWord into the list, in lexicographical order.  if newWord is already in the list, increments the freq member of the node.  The function returns a pointer to the list.
Words *addWord(Words* headPtr, char* newWord){
	Words* tmp = headPtr;
	if(headPtr == NULL){
		headPtr = malloc(sizeof(Words));
		headPtr->word = malloc(strlen(newWord) + 1);
		strcpy(headPtr->word, newWord);
		headPtr->freq = 1;
		headPtr->next = NULL;
	}
	else if(strcmp(newWord, headPtr->word) < 0){
		headPtr->word = newWord;
		headPtr->next = tmp;
	}
	else if(strcmp(newWord, headPtr->word) > 0){
		if(headPtr->next == NULL){
			headPtr->next = addWord(headPtr->next, newWord);
		}
		else{
			addWord(headPtr->next, newWord);
		}
	}
	else{
		headPtr->freq++;
	}
	return headPtr;
}

//Prints the words in the list, along with the frequency of each word
void printWords(Words *headPtr){
	while(headPtr != NULL){
		printf("%s: %d\n",headPtr->word, headPtr->freq);
		headPtr = headPtr->next;
	}
}

//frees the entire list
void deleteList(Words** headPtr){
	Words* curr = *headPtr;
	Words* tmp;
	while(curr != NULL){
		tmp = curr;
		curr = curr->next;
		free(tmp->word);
		free(tmp);
	}
	*headPtr = NULL;
}
