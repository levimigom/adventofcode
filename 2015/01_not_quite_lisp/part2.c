/**
 *	author: levimigom
 *	created: 2025-08-25 17:38:01
 **/
#include <stdio.h>
#define BASEMENT -1

int main(){
	int c, position, floor = 0;
	
	for(position = 1; (c = getchar()) != EOF; position++){
		if(c == '('){
			floor++;
		} else if(c == ')'){
			floor--;
		}

		if(floor == BASEMENT){
			break;
		}
	}

	printf("%d\n", position);

	return 0;
}
