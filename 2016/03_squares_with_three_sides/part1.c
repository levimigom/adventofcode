#include <stdio.h>
#define bool char

bool is_valid_triangle(int a, int b, int c){
	return(a < b + c && b < a + c && c < a + b);
}

int main(){
	int a, b, c, valid_triangles;

	valid_triangles = 0;
	while(scanf("%d %d %d", &a, &b, &c) != EOF){
		if(is_valid_triangle(a, b, c)){
			valid_triangles++;
		}
	}

	printf("%d\n", valid_triangles);

	return 0;
}
