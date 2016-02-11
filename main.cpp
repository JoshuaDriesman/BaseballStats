/*
 * main.c
 *
 *  Created on: Jun 10, 2013
 *      Author: joshua
 */

#include <stdio.h>
#include <string.h>
#include "parsers.h"
#include <vector>


int menu(void) {
	char input[20]; //Holds user input
	char *input_pnt = input;
	int compareLimit = 10; //Sets compare limit for string compare

	//Provide list of options
	printf("\n\nPlease enter one of the following choices:\n");
	printf("p: print data about a specific player (from a list available on the next screen)\n");
	printf("y: print data about a specific year (to be chosen on the next screen)\n");
	printf("s: print statistics about average number of assists, errors, games, games started, and double plays\n");
	printf("i: select file\n");
	printf("q: quit\n");
	printf("?:");
	scanf("%19s", input_pnt);

	//Test for each option
	int length = strlen(input_pnt);
	if (length > 1 || length < 1) {
		return 0;
	} else {
		if(!(strncmp(input_pnt, "p", compareLimit))) {
			//Test for p (player lookup)
			return 1;
		} else if (!strncmp(input_pnt, "y", compareLimit)) {
			//Test for y (year lookup)
			return 2;
		} else if (!strncmp(input_pnt, "s", compareLimit)) {
			//Test for s (average statistics lookup)
			return 3;
		} else if (!strncmp(input_pnt, "i", compareLimit)) {
			//Test for i (insert data)
			return 4;
		} else if(!strncmp(input_pnt, "q", compareLimit)) {
			//Test for q (quit)
			return 5;
		} else {
			//If no valid input found, return error code.
			return 0;
		}
	}
}

int main(void) {
	printf("Welcome to Baseball Stats Finder!");
	vector<int> averagesData;
	char nameOfFile[50] = "Stats.csv";
	//Ask user for what they want to do.
	int input = menu();
	while (1){
		switch(input){
		case 0:
			//Invalid input
			printf("Your input was not valid, please try again.\n");
			input = menu();
			break;
		case 1:
			//Lookup player
			printf("Please enter a playerID to search by: ");
			char name[50];
			scanf("%49s", &name);
			if (strcmp(name, "")){
				vector<databaseLine> database = findByName(name,nameOfFile);
				if(!database.empty()) {
					int i;
					printf("\nName -- Year -- Stint -- Team -- League -- ");
					printf("Position -- Games -- Games Started -- InnOuts -- ");
					printf("Put Outs -- Assists -- Error -- Double Plays\n");
					for (i=0; i<((short)database.size()); i=i+1) {
						printf("%s -- ", database[i].playerID);
						printf("%d -- ", database[i].year);
						printf("%d -- ", database[i].stint);
						printf("%s -- ", database[i].team);
						printf("%s -- ", database[i].leagueID);
						printf("%s -- ", database[i].position);
						printf("%d -- ", database[i].games);
						printf("%d -- ", database[i].gamesStarted);
						printf("%d -- ", database[i].inOuts);
						printf("%d -- ", database[i].putOuts);
						printf("%d -- ", database[i].assists);
						printf("%d -- ", database[i].errors);
						printf("%d\n", database[i].doublePlays);
					}
				} else {
					printf("\n\nNo data found with that playerID! Please try again.\n\n");
				}
			} else {
				printf("\n\nPlease enter a valid playerID!\n\n");
			}
			input = menu();
			break;
		case 2:
			//Lookup year
			printf("Please enter a year: ");
			int year;
			scanf("%d", &year);
			if (year != 0) {
				vector<databaseLine> database = findByYear(year,nameOfFile);
				if(!database.empty()) {
					int i;
					printf("\nName -- Year -- Stint -- Team -- League -- ");
					printf("Position -- Games -- Games Started -- InnOuts -- ");
					printf("Put Outs -- Assists -- Error -- Double Plays\n");
					for (i=0; i<((short)database.size()); i=i+1) {
						printf("%s -- ", database[i].playerID);
						printf("%d -- ", database[i].year);
						printf("%d -- ", database[i].stint);
						printf("%s -- ", database[i].team);
						printf("%s -- ", database[i].leagueID);
						printf("%s -- ", database[i].position);
						printf("%d -- ", database[i].games);
						printf("%d -- ", database[i].gamesStarted);
						printf("%d -- ", database[i].inOuts);
						printf("%d -- ", database[i].putOuts);
						printf("%d -- ", database[i].assists);
						printf("%d -- ", database[i].errors);
						printf("%d\n", database[i].doublePlays);
					}
				} else {
					printf("\n\nNo data found with that year! Please try again.\n\n");
				}

			} else {
				printf("\n\nPlease enter a valid year!\n\n");
			}

			input = menu();
			break;
		case 3:
			//Lookup overall info
			averagesData = findAverages(nameOfFile);
			if(!averagesData.empty()){
				printf("\nAverage assists: %d\n", averagesData[0]);
				printf("Average errors: %d\n", averagesData[1]);
				printf("Average games: %d\n", averagesData[2]);
				printf("Average games started: %d\n", averagesData[3]);
				printf("Average double plays: %d\n", averagesData[4]);
			}
			input = menu();
			break;
		case 4:
			//Add data
			printf("Please enter a file name: ");
			scanf("%49s", nameOfFile);
			input = menu();
			break;
		case 5:
			//Quit
			printf("Goodbye, come back soon!");
			return 0;
			break;
		}

	}

	return 0;
}
