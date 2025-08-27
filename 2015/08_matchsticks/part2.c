/**
 *	author: levimigom
 *	created: 2025-08-27 17:17:03
 **/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define STRING_LEN 64

int count_characters_in_encoded_string(char *s){
	int i, count;

	count = 0;
	for(i = 0; s[i]; i++){
		count++;
		
		if(s[i] == '"' || s[i] == '\\'){
			count++;
		}
	}

	return count + 2;
}

int main(){
	char s[STRING_LEN];
	int solution;

	solution = 0;
	while(scanf("%s", s) != EOF){
		solution += count_characters_in_encoded_string(s) - strlen(s);
	}

	printf("%d\n", solution);

	return 0;
}
