/**
 *	author: levimigom
 *	created: 2025-09-11 21:08:39
 **/
#include <stdio.h>
#define SECONDS 2503

int max(int a, int b){ return(a < b ? b : a); }
int min(int a, int b){ return(a < b ? a : b); }

int calculate_distance(int speed, int fly, int rest, int seconds){
	return((seconds / (fly + rest) * fly * speed) + speed * min(seconds % (fly + rest), fly));
}

int main(){
	int speed, fly, rest, max_distance;

	max_distance = 0;
	while(scanf("%*s can fly %d km/s for %d seconds, but then must rest for %d seconds.", &speed, &fly, &rest) != EOF){
		max_distance = max(max_distance, calculate_distance(speed, fly, rest, SECONDS));
	}

	printf("%d\n", max_distance);
	
	return 0;
}
