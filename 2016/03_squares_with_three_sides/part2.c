#include <stdio.h>
#define bool char
#define TRIANGLES 3
#define SIDES 3

bool is_valid_triangle(int a, int b, int c){
	return(a < b + c && b < a + c && c < a + b);
}

int main(){
	int i, triangles[TRIANGLES][SIDES], valid_triangles;

	valid_triangles = 0;
	while(scanf("%d %d %d", &triangles[0][0], &triangles[1][0], &triangles[2][0]) != EOF){
		for(i = 1; i < SIDES; i++){
			scanf("%d %d %d", &triangles[0][i], &triangles[1][i], &triangles[2][i]);
		}

		for(i = 0; i < TRIANGLES; i++){
			if(is_valid_triangle(triangles[i][0], triangles[i][1], triangles[i][2])){
				valid_triangles++;
			}
		}
	}

	printf("%d\n", valid_triangles);

	return 0;
}
