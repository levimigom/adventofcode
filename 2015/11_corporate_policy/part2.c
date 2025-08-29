/**
 *	author: levimigom
 *	created: 2025-08-29 09:42:55
 **/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define STRING_LEN 32

bool contains_three_straight_letters(char *s){
	int i;

	for(i = 0; s[i]; i++){
		if(2 <= i && s[i] - s[i - 1] == 1 && s[i - 1] - s[i - 2] == 1){
			return true;
		}
	}

	return false;
}

bool does_not_contain_iol(char *s){
	while(*s){
		if(*s == 'i' || *s == 'o' || *s == 'l'){
			return false;
		}
		s++;
	}
	
	return true;
}

bool contains_two_non_overlapping_pairs_of_letters(char *s){
	int i, len, pairs;
	
	len = strlen(s);
	for(i = pairs = 0; i < len; i++){
		if(0 < i && s[i] == s[i - 1]){
			pairs++;
			i++;
		}
	}

	return 2 <= pairs;
}

bool is_valid_password(char *s){
	return contains_three_straight_letters(s) && does_not_contain_iol(s)
		&& contains_two_non_overlapping_pairs_of_letters(s);
}

void increment(char *s){
	int i;

	for(i = strlen(s) - 1; 0 <= i && s[i] == 'z'; i--){
		s[i] = 'a';
	}
	
	if(0 <= i){
		s[i]++;
	}
}

int main(){
	char s[STRING_LEN];
	scanf("%s", s);

	int i;

	for(i = 0; i < 2; i++){
		do {
			increment(s);
		} while(!is_valid_password(s));
	}

	printf("%s\n", s);

	return 0;
}
