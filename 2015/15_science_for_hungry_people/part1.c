/**
 *	author: levimigom
 *	created: 2025-09-17 20:23:01
 **/
#include <stdio.h>
#include <stdlib.h>
#define LIM 16
#define TEASPOONS 100

struct Properties {
	int capacity, durability, flavor, texture, calories;
};

struct Properties *properties_create(int capacity, int durability, int flavor, int texture, int calories){
	struct Properties *p = malloc(sizeof(struct Properties));
	p->capacity = capacity;
	p->durability = durability;
	p->flavor = flavor;
	p->texture = texture;
	p->calories = calories;
	return p;
}

void properties_add(struct Properties *a, struct Properties *b, int times){
	a->capacity += b->capacity * times;
	a->durability += b->durability * times;
	a->flavor += b->flavor * times;
	a->texture += b->texture * times;
	a->calories += b->calories * times;
}

struct Properties **get_ingredients(int *size){
	struct Properties **ingredients = calloc(sizeof(struct Properties*), LIM);
	int i, capacity, durability, flavor, texture, calories;

	for(i = 0; scanf("%*s capacity %d, durability %d, flavor %d, texture %d, calories %d", 
				&capacity, &durability, &flavor, &texture, &calories) != EOF; i++){
		ingredients[i] = properties_create(capacity, durability, flavor, texture, calories);
	}

	*size = i;	
	return ingredients;
}

int max(int a, int b){ return(a < b ? b : a); }

int score(struct Properties *p){
	if(p->capacity <= 0 || p->durability <= 0 || p->flavor <= 0 || p->texture <= 0){
		return 0;
	}

	return p->capacity * p->durability * p->flavor * p->texture;
}

int solve(struct Properties **ingredients, int ingredient_count, int current_ingredient,
		 int teaspoons, struct Properties *properties){
	int i, solution;

	solution = -1;
	for(i = 0; i <= teaspoons; i++){
		if(0 < i){
			properties_add(properties, ingredients[current_ingredient], 1);
		}

		if(current_ingredient < ingredient_count - 1){
			solution = max(solution, solve(ingredients, ingredient_count, current_ingredient + 1,
				teaspoons - i, properties));
		}
	}
	
	solution = max(solution, score(properties));

	properties_add(properties, ingredients[current_ingredient], -teaspoons);
	return solution;
}

int main(){
	int i, ingredient_count;
	struct Properties **ingredients = get_ingredients(&ingredient_count);
	struct Properties *properties = properties_create(0, 0, 0, 0, 0);

	printf("%d\n", solve(ingredients, ingredient_count, 0, TEASPOONS, properties));

	free(properties);
	for(i = 0; i < ingredient_count; i++){
		free(ingredients[i]);
	}
	free(ingredients);

	return 0;
}
