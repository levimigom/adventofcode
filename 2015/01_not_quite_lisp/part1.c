/**
 *	author: levimigom
 *	created: 2025-08-25 17:38:01
 **/
#include <stdio.h>

int main(){
	int c, floor = 0;
	
	while((c = getchar()) != EOF){
		if(c == '('){
			floor++;
		} else if(c == ')'){
			floor--;
		}
	}

	printf("%d\n", floor);

	return 0;
}
