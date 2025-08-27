/**
 *	author: levimigom
 *	created: 2025-08-27 14:19:17
 **/
#include <stdio.h>
#include <stdbool.h>
#define STRING_LEN 64

bool contains_two_repeated_letters(char *s){
	int i, j;

	for(i = 1; s[i]; i++){
		for(j = i + 1; s[j] && s[j + 1]; j++){
			if(s[i - 1] == s[j] && s[i] == s[j + 1]){
				return true;
			}
		}
	}

	return false;
}

bool contains_letter_repeated_with_one_letter_between(char *s){
	int i;

	for(i = 2; s[i]; i++){
		if(s[i - 2] == s[i]){
			return true;
		}
	}

	return false;
}

bool is_nice_string(char *s){
	return contains_two_repeated_letters(s) && contains_letter_repeated_with_one_letter_between(s);
}

int main(){
	char s[STRING_LEN];
	int count;

	for(count = 0; scanf("%s", s) != EOF; count += is_nice_string(s));

	printf("%d\n", count);

	return 0;
}
