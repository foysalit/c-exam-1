#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct producer_s producer;
typedef struct model_s model;
typedef struct car_s car;

typedef struct producer_s
{
	char *name;
	char *filename;
	producer *next;
	model *models;
} producer;

typedef struct model_s
{
	char *name;
	char *filename;
	model *next;
	car *cars;
} model;

typedef struct car_s
{
	char *name;
	float price;
	car *next;
} car;

producer *get_producers_list(char *filename);
model *get_models_list(char *filename);
car *get_cars_list(char *filename);

void find_model(char *model_name, producer *prodlist);


int main(int argc, char const *argv[])
{
	producer *prodlist;
	char model_query[20];

	if(argc < 2){
		printf("too few arguments!\n");
		exit(EXIT_FAILURE);
	}

	prodlist = get_producers_list(argv[1]);

	printf("Which model are you looking for?\n");
	scanf("%s", model_query);

	find_model(model_query, prodlist);

	return 0;
}

producer *get_producers_list(char *filename){
	producer *tproducer, *producers;
	char name[MAX_LINE_LENGTH], producers_file[MAX_LINE_LENGTH];
	FILE *fp = fopen(filename, "r");

	if(fp == NULL){
		printf("sorry the file isn't accessible!\n");
		exit(EXIT_FAILURE);
	}

	producers = NULL;
	while(fscanf(fp, "%s %s", name, producers_file) != EOF){
		tproducer = malloc(sizeof(producer));

		tproducer->name = malloc(sizeof(char) * strlen(name) + 1);
		tproducer->filename = malloc(sizeof(char) * strlen(producers_file) + 1);
		
		strcpy(tproducer->name, name);
		strcpy(tproducer->filename, producers_file);

		tproducer->models = get_models_list(tproducer->filename);

		if(producers != NULL){
			tproducer->next = producers;
		}

		producers = tproducer;
	}

	return producers;
}

model *get_models_list(char *filename){
	model *tmodel, *models;
	char name[MAX_LINE_LENGTH], models_file[MAX_LINE_LENGTH];
	FILE *fp = fopen(filename, "r");

	if(fp == NULL){
		printf("sorry the file isn't accessible!\n");
		exit(EXIT_FAILURE);
	}

	models = NULL;
	while(fscanf(fp, "%s %s", name, models_file) != EOF){
		tmodel = malloc(sizeof(model));

		tmodel->name = malloc(sizeof(char) * strlen(name) + 1);
		tmodel->filename = malloc(sizeof(char) * strlen(models_file) + 1);
		
		strcpy(tmodel->name, name);
		strcpy(tmodel->filename, models_file);

		tmodel->cars = get_cars_list(tmodel->filename);

		if(models != NULL){
			tmodel->next = models;
		}

		models = tmodel;
	}

	return models;
}

car *get_cars_list(char *filename){
	car *tcar, *cars;
	char name[MAX_LINE_LENGTH];
	float price;
	FILE *fp = fopen(filename, "r");

	if(fp == NULL){
		printf("sorry the file isn't accessible!\n");
		exit(EXIT_FAILURE);
	}

	cars = NULL;
	while(fscanf(fp, "%s %f", name, &price) != EOF){
		tcar = malloc(sizeof(car));

		tcar->name = malloc(sizeof(char) * strlen(name) + 1);
		strcpy(tcar->name, name);

		tcar->price = price;

		if(cars != NULL){
			tcar->next = cars;
		}

		cars = tcar;
	}

	return cars;
}

void find_model(char *model_name, producer *prodlist){
	producer *tproducer;
	model *tmodel;
	car *tcar;
	int found = 0;

	printf("Looking for - %s\n", model_name);

	tproducer = prodlist;
	while(tproducer != NULL && found == 0){
		//printf("Producer: %s\n", tproducer->name);
		//printf("-----------------------------\n");

		tmodel = tproducer->models;
		while(tmodel != NULL && found == 0){
			if(strcmp(tmodel->name, model_name) == 0){
				found = 1;
			}else{
				tmodel = tmodel->next;
			}
		}

		tproducer = tproducer->next;
	}

	if(found == 1){
		printf("Found the model!\n");
		tcar = tmodel->cars;
		while(tcar != NULL){
			printf("%s price: %0.2f\n", tcar->name, tcar->price);
			tcar = tcar->next;
		}
	}else{
		printf("Sorry the model isn't in our database!\n");
	}
}