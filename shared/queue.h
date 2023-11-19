#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct queue_item {
	void *item;
	struct queue_item *next;
} queue_item;

typedef struct queue {
	int items;
	queue_item *first, *last;
} queue;

queue* create_queue(){
	queue* q = malloc(sizeof(queue));
	q->first = q->last = 0;
	q->items = 0;
	return q;
}

void enqueue(queue *q, void* item){
	queue_item *i = malloc(sizeof(queue_item));
	i->item = item;
	i->next = 0;
	
	if(q->items == 0){
		q->first = q->last = i;
	} else {
		q->last->next = i;
		q->last = q->last->next;
	}
	q->items++;
}

void* dequeue(queue *q){
	queue_item *first = q->first;
	void* item = first->item;

	q->first = q->first->next;
	free(first);
	q->items--;
	return item;
}

bool is_empty(queue *q){
	return q->items == 0;
}
#endif
