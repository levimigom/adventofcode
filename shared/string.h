#include <stdlib.h>
#include <stdbool.h>

#ifndef STRING_H
#define STRING_H

typedef struct _string String;

struct _string {
	int length, capacity;
	char *characters;
};

String *string_create(){
	String *s = malloc(sizeof(String));

	s->length = 0;	
	s->capacity = 1;
	s->characters = calloc(sizeof(char), s->capacity);

	return s;
}

void string_free(String *s){
	free(s->characters);
	free(s);
}

void string_append(String *s, char c){
	if(s->length == s->capacity){
		s->capacity *= 2;
		s->characters = realloc(s->characters, sizeof(char) * s->capacity);
	}

	s->characters[s->length++] = c;
}

String *string_read_line(){
	int c;

	c = getchar();

	if(c == EOF){
		return 0;
	}

	String *s = string_create();
	do {
		string_append(s, c);
	} while((c = getchar()) != '\n' && c != EOF);

	return s;
}

char *string_get_characters(String *s){
	char *c = calloc(sizeof(char), s->length);
	int i;

	for(i = 0; i < s->length; i++){
		c[i] = s->characters[i];
	}

	return c;
}

#endif
