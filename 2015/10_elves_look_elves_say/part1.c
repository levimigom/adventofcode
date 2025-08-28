/**
 *	author: levimigom
 *	created: 2025-08-29 00:01:15
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRING_LEN 32

struct String {
	char *characters;
	int size, capacity;
};

struct String *string_create(){
	struct String *s = malloc(sizeof(struct String));
	s->size = 0;
	s->capacity = 2;
	s->characters = calloc(sizeof(char), s->capacity);
	return s; 
}

void string_append(struct String *s, char c){
	if(s->size == s->capacity){
		s->capacity *= 2;
		s->characters = realloc(s->characters, sizeof(char) * s->capacity);
	}

	s->characters[s->size++] = c;
}

void string_append_number(struct String *s, int n){
	char digits[8];
	sprintf(digits, "%d", n);

	int i;

	for(i = 0; digits[i]; i++){
		string_append(s, digits[i]);
	}
}

char *encode(char *src){
	struct String *encoded = string_create();
	int i, count;

	count = 1;
	for(i = 1; src[i]; i++){
		if(src[i] != src[i - 1]){
			string_append_number(encoded, count);
			string_append(encoded, src[i - 1]);
			count = 0;
		}
		
		count++;
	}

	string_append_number(encoded, count);
	string_append(encoded, src[i - 1]);	
	string_append(encoded, '\0');

	char *result = encoded->characters;
	free(encoded);	
	return result;
}

char *generate_look_and_say_sequence(char *s, int iterations){
	char *src, *dst;
	int i;

	src = calloc(sizeof(char), strlen(s) + 1);
	strcpy(src, s);

	for(i = 0; i < iterations; i++){
		dst = encode(src);
		free(src);
		src = dst;
	}

	return dst;
}

int main(){
	char s[STRING_LEN];
	scanf("%s", s);
	char *sequence = generate_look_and_say_sequence(s, 40);
	printf("%ld\n", strlen(sequence));
	free(sequence);

	return 0;
}
