#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 10

typedef struct product
{
	char type;
	int amount;
	char unit;
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void innitMilk(item *smt) {
	smt->type = 0;
	smt->amount = 0;
	smt->unit = 0;
}

void innitCheese(item *smt) {
	smt->type = 1;
	smt->amount = 0;
	smt->unit = 1;
}

void produce(item *i){
	while ((first + 1) % BUFFER_SIZE == last){
		printf("No free buffer item\n");
		return;
	}
	memcpy(&buffer[first], i, sizeof(item));
	i->amount += 1;
	first = (first + 1) % BUFFER_SIZE;
	printf("First = %d\n", first);
}

item *consume(){
	item *i = malloc(sizeof(item));
	while (first == last){
		printf("Nothing to consume\n");
	}
	memcpy(i, &buffer[last], sizeof(item));
	i->amount -= 1;
	last = (last + 1) % BUFFER_SIZE;
	printf("Last = %d\n", last);
	return i;
}

int main(){
	int option = 0;
	item *milk, cans, *chesse, boxes;
	milk = &cans;
	chesse = &boxes;
	printf("Please choose\n");
	printf("1 for Milk Cans, 2 for Cheese Boxes:");
	while(true){
		scanf("%d", &option);
		if (option == 1){
			printf("Milk Cans are ready to serve!\n");
			innitMilk(milk);
			produce(milk);
			produce(milk);
			printf("Consuming...\n");
			milk = consume();
			break;
		} else if (option == 2){
			printf("Cheese Boxes are ready to serve!\n");
			innitCheese(chesse);
			produce(chesse);
			produce(chesse);
			printf("Consuming...\n");
			chesse = consume();
			break;
		} else {
			printf("Try again!\n");
			printf("1 for Milk Cans, 2 for Cheese Boxes\n");
			scanf("%d", &option);
		}
	}
	return 0;
}