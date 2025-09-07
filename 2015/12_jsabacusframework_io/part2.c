/**
 *	author: levimigom
 *	created: 2025-08-31 20:06:00
 **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define LIM 50000

struct Object {
	int start_index, end_index, sum_of_numbers, children;
	bool contains_red;
};

struct Object *object_create(int start_index){
	struct Object *obj = malloc(sizeof(struct Object));
	obj->start_index = start_index;
	obj->end_index = -1;
	return obj;
}

void object_parse(struct Object *obj, char *s){
	int i, j, open_braces, closed_braces, number;

	open_braces = closed_braces = 0;
	obj->sum_of_numbers = 0;
	obj->contains_red = false;
	
	for(i = obj->start_index + 1; i < obj->end_index; i++){
		if(s[i] == '{'){
			open_braces++;
		}

		if(s[i] == '}'){
			closed_braces++;
		}

		if(open_braces == closed_braces){
			if(i + 5 < obj->end_index && strncmp(s + i, ":\"red\"", 6) == 0){
				obj->contains_red = true;
			}

			if('0' <= s[i] && s[i] <= '9'){
				number = s[i] - '0';
				for(j = 1; '0' <= s[i + j] && s[i + j] <= '9'; j++){
					number = (number * 10) + s[i + j] - '0';
				}

				if(s[i - 1] == '-'){
					obj->sum_of_numbers -= number;
				} else {
					obj->sum_of_numbers += number;
				}

				i += j - 1;
			}
		}
	}

	obj->children = open_braces;
}

struct Document {
	struct Object **objects;
	int size, capacity;
};

struct Document *document_create(){
	struct Document *doc = malloc(sizeof(struct Document));
	doc->size = 0;
	doc->capacity = 2;
	doc->objects = calloc(doc->capacity, sizeof(struct Object));
	return doc;
}

void document_add_object(struct Document *doc, int start_index){
	if(doc->size == doc->capacity){
		doc->capacity *= 2;
		doc->objects = realloc(doc->objects, sizeof(struct Object) * doc->capacity);
	}

	doc->objects[doc->size++] = object_create(start_index);
}

void document_close_last_opened_object(struct Document *doc, int end_index, char *s){
	int i;
	for(i = doc->size - 1; 0 <= i && doc->objects[i]->end_index != -1; i--);
	doc->objects[i]->end_index = end_index;
	object_parse(doc->objects[i], s);
}

struct Document *parse(char *s){
	struct Document *doc = document_create();
	int i, j;
	
	document_add_object(doc, 0);
	document_close_last_opened_object(doc, strlen(s) - 1, s);
	
	for(i = 0; s[i]; i++){
		if(s[i] == '{'){
			document_add_object(doc, i);
		} 

		else if(s[i] == '}'){
			document_close_last_opened_object(doc, i, s);
		}
	}

	return doc;
}

void document_free(struct Document *doc){
	int i;

	for(i = 0; i < doc->size; i++){
		free(doc->objects[i]);
	}
	free(doc->objects);
	free(doc);
}

int document_sum_objects_without_property_value_red(struct Document *doc){
	int i, sum;

	sum = 0;
	for(i = 0; i < doc->size; i++){
		if(doc->objects[i]->contains_red){
			i += doc->objects[i]->children;
		} else {
			sum += doc->objects[i]->sum_of_numbers;
		}
	}

	return sum;
}

int main(){
	char s[LIM];
	scanf("%s", s);

	struct Document *doc = parse(s);
	printf("%d\n", document_sum_objects_without_property_value_red(doc));
	document_free(doc);

	return 0;
}
