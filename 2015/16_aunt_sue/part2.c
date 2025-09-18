/**
 *	author: levimigom
 *	created: 2025-09-18 23:16:01
 **/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define PROPERTIES 10
char *property_keys[] = { "children:", "cats:", "samoyeds:", "pomeranians:", "akitas:", "vizslas:", "goldfish:", "trees:", "cars:", "perfumes:" };
int property_counts[] = { 3, 7, 2, 3, 0, 0, 5, 3, 2, 1 };

bool property_matches(char *property, int count){
	int i;

	for(i = 0; i < PROPERTIES; i++){
		if(strcmp(property, property_keys[i]) == 0){
			if(strcmp(property, "cats:") == 0 || strcmp(property, "trees:") == 0){
				return property_counts[i] < count;
			}

			if(strcmp(property, "pomeranians:") == 0 || strcmp(property, "goldfish:") == 0){
				return count < property_counts[i];
			}

			return count == property_counts[i];
		}
	}

	return false;
}

void solve(){
	int number, count;
	char property[32];
	bool matches;

	while(scanf("Sue %d: ", &number) != EOF){
		matches = true;

		scanf("%s %d,", property, &count);
		matches &= property_matches(property, count);

		scanf("%s %d,", property, &count);
		matches &= property_matches(property, count);
		
		scanf("%s %d\n", property, &count);
		matches &= property_matches(property, count);

		if(matches){
			printf("%d\n", number);
		}
	}
}

int main(){
	solve();

	return 0;
}
