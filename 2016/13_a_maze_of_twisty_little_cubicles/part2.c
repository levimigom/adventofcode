#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define FAVOURITE_NUMBER 1364
#define MAX_STEPS 50

struct queue_item {
	int x, y, steps;
	struct queue_item *previous, *next;
};

struct queue {
	struct queue_item *first, *last;	
};

struct queue_item *create_queue_item(int x, int y, int steps){
	struct queue_item *item = malloc(sizeof(struct queue_item));
	item->x = x;
	item->y = y;
	item->steps = steps;
	item->previous = 0;
	item->next = 0;
	return item;
}

struct queue *create_queue(){
	struct queue *queue = malloc(sizeof(struct queue));
	queue->first = queue->last = 0;
	return queue;
}

void destroy_queue(struct queue *queue){
	struct queue_item *item, *next;
       
	item = queue->first;
	while(item != 0){
		next = item->next;
		free(item);
		item = next;
	}

	free(queue);
}

void add_to_queue(struct queue *queue, int x, int y, int steps){
	struct queue_item *item = create_queue_item(x, y, steps);

	if(queue->last != 0){
		item->previous = queue->last;
		queue->last->next = item;
		queue->last = item;
	} else {
		queue->first = queue->last = item;
	}
}

struct queue_item *get_from_queue(struct queue *queue){
	struct queue_item *item = queue->first;

	queue->first = queue->first->next;
	
	if(queue->first == 0){
		queue->last = 0;
	}

	return item;
}

bool queue_is_empty(struct queue *queue){
	return queue->first == 0;
}

int active_bits(int n){
	int power_of_two, count;

	power_of_two = 1;	
	count = 0;

	while(0 < power_of_two && power_of_two <= n){
		if(power_of_two & n){
			count++;
		}

		power_of_two <<= 1;
	}
	
	return count;
}

bool location_is_open(int x, int y){
	if(x < 0 || y < 0){
		return false;
	}
	
	int sum = x*x + 3*x + 2*x*y + y + y*y + FAVOURITE_NUMBER;
	return active_bits(sum) % 2 == 0;
}

int main(){
	struct queue *queue = create_queue();
	struct queue_item *item;
	bool visited[MAX_STEPS + 2][MAX_STEPS + 2] = { 0 };
	int i, visited_count, neighbour_x, neighbour_y;
	int xp[] = { 0, 0, -1, 1 };
	int yp[] = { -1, 1, 0, 0 };

	visited_count = 0;
	add_to_queue(queue, 1, 1, 0);
	visited[1][1] = true;
	while(!queue_is_empty(queue)){
		item = get_from_queue(queue);
		visited_count++;

		if(item->steps < MAX_STEPS){
			for(i = 0; i < 4; i++){
				neighbour_x = item->x + xp[i];
				neighbour_y = item->y + yp[i];
			
				if(location_is_open(neighbour_x, neighbour_y) && !visited[neighbour_x][neighbour_y]){
					add_to_queue(queue, neighbour_x, neighbour_y, item->steps + 1);
					visited[neighbour_x][neighbour_y] = true;
				}
			}		
		}
			
		free(item);
	}
	
	destroy_queue(queue);

	printf("%d\n", visited_count);

	return 0;
}
