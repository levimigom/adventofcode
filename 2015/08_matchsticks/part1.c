/**
 *	author: levimigom
 *	created: 2025-08-27 17:17:03
 **/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define STRING_LEN 64
char *hex_digits = "0123456789abcdefABCDEF";

bool is_hex_digit(char c){
	int i;

	for(i = 0; hex_digits[i]; i++){
		if(c == hex_digits[i]){
			return true;
		}
	}
	
	return false;
}

bool starts_with_hex_escape_sequence(char *s){
	return(s[0] == '\\' && s[1] && s[1] == 'x' && s[2] && is_hex_digit(s[2]) && s[3] && is_hex_digit(s[3]));
}

bool starts_with_escape_sequence(char *s){
	return(s[0] == '\\' && s[1] && (s[1] == '\\' || s[1] == '"'));
}

int count_characters_in_memory(char *s){
	int i, skip, count;

	count = skip = 0;
	for(i = 0; s[i]; i += skip + 1){
		skip = 0;
		count++;

		if(starts_with_escape_sequence(s + i)){
			skip = 1;
		} else if(starts_with_hex_escape_sequence(s + i)){
			skip = 3;
		}
	}

	return count - 2;
}

int main(){
	char s[STRING_LEN];
	int solution;

	solution = 0;
	while(scanf("%s", s) != EOF){
		solution += strlen(s) - count_characters_in_memory(s);
	}

	printf("%d\n", solution);

	return 0;
}
