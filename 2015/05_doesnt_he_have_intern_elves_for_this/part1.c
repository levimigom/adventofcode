/**
 *	author: levimigom
 *	created: 2025-08-27 14:19:17
 **/
#include <stdio.h>
#include <stdbool.h>
#define STRING_LEN 64

bool contains_three_vowels(char *s){
	int i, count;

	for(i = count = 0; s[i] && count < 3; i++){
		if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'){
			count++;
		}
	}

	return count == 3;
}

bool has_repeating_character(char *s){
	int i;

	for(i = 1; s[i]; i++){
		if(s[i] == s[i - 1]){
			return true;
		}
	}

	return false;
}

bool contains(char *s, char *needle){
	int i, j;

	for(i = 0; s[i]; i++){
		for(j = 0; needle[j] && s[i + j] && needle[j] == s[i + j]; j++);

		if(needle[j] == '\0'){
			return true;
		}
	}

	return false;
}

bool is_nice_string(char *s){
	return contains_three_vowels(s) && has_repeating_character(s) && !contains(s, "ab")
		&& !contains(s, "cd") && !contains(s, "pq") && !contains(s, "xy");
}

int main(){
	char s[STRING_LEN];
	int count;

	for(count = 0; scanf("%s", s) != EOF; count += is_nice_string(s));

	printf("%d\n", count);

	return 0;
}
