#include <stdio.h>
#include <stdbool.h>

bool can_get_capsule(int time, int discs, int *disc_position_count, int *disc_starting_position){
	int i;

	for(i = 0; i < discs; i++){
		if((disc_starting_position[i] + time + i + 1) % disc_position_count[i] != 0){
			return false;
		}
	}

	return true;
}

void solve(int discs, int *disc_position_count, int *disc_starting_position){
	int time = 0;

	while(!can_get_capsule(time, discs, disc_position_count, disc_starting_position)){
		time++;
	}	

	printf("You can get the capsule if you press the button at time %d\n", time);
}

int main(){
	int discs = 7;
	int disc_position_count[7] = { 17, 7, 19, 5, 3, 13, 11 };
	int disc_starting_position[7] = { 1, 0, 2, 0, 0, 5, 0 };

	solve(discs, disc_position_count, disc_starting_position);

	return 0;
}
