/**
 *	author: levimigom
 *	created: 2025-08-29 00:01:15
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRING_LEN 32
#define BUFFER 16

void append(char **s, int *size, int *capacity, char digit, int count){
	if(*capacity - *size < BUFFER){
		*capacity = 2 * *capacity + BUFFER;
		*s = realloc(*s, sizeof(char) * *capacity);
	}

	sprintf(*s + *size, "%d%c", count, digit);
	while((*s)[*size]) (*size)++;
}

char *encode(char *src){
	int i, count, size, capacity;
	char *dst;

	size = 0;
	capacity = 2 + BUFFER;
	dst = calloc(sizeof(char), capacity);

	count = 1;
	for(i = 1; src[i]; i++){
		if(src[i] != src[i - 1]){
			append(&dst, &size, &capacity, src[i - 1], count);
			count = 0;
		}
		
		count++;
	}

	append(&dst, &size, &capacity, src[i - 1], count);
	return dst;
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
	char *sequence = generate_look_and_say_sequence(s, 50);
	printf("%ld\n", strlen(sequence));
	free(sequence);

	return 0;
}
