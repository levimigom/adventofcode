#include <stdlib.h>

#ifndef LIST_H
#define LIST_H

typedef struct _list List;

struct _list {
	int count, capacity;
	size_t item_size;
	void **items;
};

struct _list *list_create(size_t item_size){
	List *list = malloc(sizeof(List));
	
	list->count = 0;
	list->capacity = 1;
	list->item_size = item_size;
	list->items = calloc(sizeof(void *), list->capacity);

	return list;	
}

void list_add(List *list, void *item){
	if(list->count == list->capacity){
		list->capacity *= 2;
		list->items = realloc(list->items, list->item_size * list->capacity);
	}

	list->items[list->count] = item;
	list->count += 1;
}

void list_free(List *list){
	int i;

	for(i = 0; i < list->count; i++){
		free(list->items[i]);
	}

	free(list->items);
	free(list);
}

void list_sort(List *list, int (*compare)(const void *, const void *)){
	int compare_wrapper(const void * a, const void * b){
		void ** x = (void**) a;
		void ** y = (void**) b;

		return compare(*x, *y);
	}

	qsort(list->items, list->count, sizeof(void *), compare_wrapper);
}

#endif
