/*
 * parsers.c
 *
 *  Created on: Jun 10, 2013
 *      Author: joshua
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parsers.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include "strsepcompatible.h"
using namespace std;

vector<databaseLine> findByYear(int year, char *fileName) {
	FILE *stats;
	stats = fopen(fileName, "r");
	vector<databaseLine> dataLines;
	if(stats!=NULL){
		//Skips first line which is the column definition
		char line[100];
		fscanf(stats, "%s", line);

		//Continues on rest of lines
		while(feof(stats)==0){
			if(feof(stats)==0){
				char *tempYear;
				char copyofline[100];
				fscanf(stats, "%s", line);
				strcpy(copyofline, line);
				char *copyoflinepnt = copyofline;
				char *lineBufferPnt = strdup(line);

				//Skips first value (Player ID)
				strsepcompatible(&lineBufferPnt, ",");

				//Gets year of line
				tempYear = strsepcompatible(&lineBufferPnt, ",");
				int fileYear = atoi(tempYear);


				//Checks input year against line year
				if (fileYear == year) {
					databaseLine currentPlayer;
					char tempText[50];

					//Looks for and adds Player ID if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? strcpy(currentPlayer.playerID, tempText) : strcpy(currentPlayer.playerID, "N/A");

					//Looks for and adds year if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.year = atoi(tempText) : currentPlayer.year = 0;

					//Looks for and adds stint if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.stint = atoi(tempText) : currentPlayer.stint = 0;

					//Looks for and adds team if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? strcpy(currentPlayer.team, tempText) : strcpy(currentPlayer.team, "N/A");

					//Looks for and adds league if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? strcpy(currentPlayer.leagueID, tempText) : strcpy(currentPlayer.leagueID, "N/A");

					//Looks for and adds position if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? strcpy(currentPlayer.position, tempText) : strcpy(currentPlayer.position, "N/A");

					//Looks for and adds games if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.games = atoi(tempText) : currentPlayer.games = 0;

					//Looks for and adds games started if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.gamesStarted = atoi(tempText) : currentPlayer.gamesStarted = 0;

					//Looks for and adds in outs if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.inOuts = atoi(tempText) : currentPlayer.inOuts=0;

					//Looks for and adds putOuts if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.putOuts = atoi(tempText) : currentPlayer.putOuts=0;

					//Looks for and adds assists if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.assists = atoi(tempText) : currentPlayer.assists=0;

					//Looks for and adds errors if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.errors = atoi(tempText) : currentPlayer.errors=0;

					//Looks for and adds double plays if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.doublePlays = atoi(tempText) : currentPlayer.doublePlays=0;

					//Looks for and adds passed balls if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.passedBalls = atoi(tempText) : currentPlayer.passedBalls=0;

					//Looks for and adds wild pitches if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.wildPitches = atoi(tempText) : currentPlayer.wildPitches = 0;

					//Looks for and adds opponent stolen basses if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.opponentStolenBases = atoi(tempText) : currentPlayer.opponentStolenBases=0;

					//Looks for and adds opponent caught stealing if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.opponentCaughtStealing = atoi(tempText) : currentPlayer.opponentCaughtStealing=0;

					//Looks for and adds zone rating if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.zoneRating = atoi(tempText) : currentPlayer.zoneRating = 0;

					dataLines.push_back(currentPlayer);
				}

			}
		}
		//Closes file
		clearerr(stats);
		fclose(stats);
	} else {
		printf("\nInvalid file!");
	}
	//Returns vector of found data
	return dataLines;
}

vector<databaseLine> findByName(char *name, char *fileName) {
	FILE *stats;
	stats = fopen(fileName, "r");
	vector<databaseLine> dataLines;

	//Skips first line which is the column definition
	if(stats!=NULL) {
		char line[100];
		fscanf(stats, "%s", line);

		//Continues on rest of lines
		while(feof(stats)==0){
			if(feof(stats)==0){
				char copyofline[100];
				fscanf(stats, "%s", line);
				strcpy(copyofline, line);
				char *copyoflinepnt = copyofline;
				char *lineBufferPnt = strdup(line);
				//Gets first value (Player ID)
				char *playerName = strsepcompatible(&lineBufferPnt, ",");

				//Checks input year against line year
				if (strcmp(playerName, name)==0) {
					databaseLine currentPlayer;
					char tempText[50];

					//Looks for and adds Player ID if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? strcpy(currentPlayer.playerID, tempText) : strcpy(currentPlayer.playerID, "N/A");

					//Looks for and adds year if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.year = atoi(tempText) : currentPlayer.year = 0;

					//Looks for and adds stint if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.stint = atoi(tempText) : currentPlayer.stint = 0;

					//Looks for and adds team if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? strcpy(currentPlayer.team, tempText) : strcpy(currentPlayer.team, "N/A");

					//Looks for and adds league if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? strcpy(currentPlayer.leagueID, tempText) : strcpy(currentPlayer.leagueID, "N/A");

					//Looks for and adds position if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? strcpy(currentPlayer.position, tempText) : strcpy(currentPlayer.position, "N/A");

					//Looks for and adds games if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.games = atoi(tempText) : currentPlayer.games = 0;

					//Looks for and adds games started if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.gamesStarted = atoi(tempText) : currentPlayer.gamesStarted = 0;

					//Looks for and adds in outs if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.inOuts = atoi(tempText) : currentPlayer.inOuts=0;

					//Looks for and adds putOuts if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.putOuts = atoi(tempText) : currentPlayer.putOuts=0;

					//Looks for and adds assists if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.assists = atoi(tempText) : currentPlayer.assists=0;

					//Looks for and adds errors if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.errors = atoi(tempText) : currentPlayer.errors=0;

					//Looks for and adds double plays if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.doublePlays = atoi(tempText) : currentPlayer.doublePlays=0;

					//Looks for and adds passed balls if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.passedBalls = atoi(tempText) : currentPlayer.passedBalls=0;

					//Looks for and adds wild pitches if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.wildPitches = atoi(tempText) : currentPlayer.wildPitches = 0;

					//Looks for and adds opponent stolen basses if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.opponentStolenBases = atoi(tempText) : currentPlayer.opponentStolenBases=0;

					//Looks for and adds opponent caught stealing if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.opponentCaughtStealing = atoi(tempText) : currentPlayer.opponentCaughtStealing=0;

					//Looks for and adds zone rating if not null
					strcpy(tempText, strsepcompatible(&copyoflinepnt, ","));
					(strcmp(tempText, "")) ? currentPlayer.zoneRating = atoi(tempText) : currentPlayer.zoneRating = 0;

					dataLines.push_back(currentPlayer);
				}

			}
		}
		//Closes file
		clearerr(stats);
		fclose(stats);
	} else {
		printf("\nInvalid file!");
	}
	//Returns vector of found data
	return dataLines;
}

vector<int> findAverages(char *fileName) {
	vector<int>  averages;
	FILE *stats;
	stats = fopen(fileName, "r");
	int averageAssists=0;
	int averageErrors=0;
	int averageGames=0;
	int averageGamesStarted=0;
	int averageDoublePlays=0;
	int i = 0;

	//Skips first line which is the column definition
	if(stats!=NULL) {
		char line[100];
		fscanf(stats, "%s", line);

		//Continues on rest of lines
		while(feof(stats)==0){
			i++;
			if(feof(stats)==0){
				fscanf(stats, "%s", line);
				char *lineBufferPnt = strdup(line);

				if(strcmp(line, "") != 0) {
					strsepcompatible(&lineBufferPnt, ",");
					strsepcompatible(&lineBufferPnt, ",");
					strsepcompatible(&lineBufferPnt, ",");
					strsepcompatible(&lineBufferPnt, ",");
					strsepcompatible(&lineBufferPnt, ",");
					strsepcompatible(&lineBufferPnt, ",");

					int games = atoi(strsepcompatible(&lineBufferPnt, ","));
					int gamesStarted = atoi(strsepcompatible(&lineBufferPnt, ","));

					strsepcompatible(&lineBufferPnt, ",");
					strsepcompatible(&lineBufferPnt, ",");

					int assists = atoi(strsepcompatible(&lineBufferPnt, ","));
					int errors = atoi(strsepcompatible(&lineBufferPnt, ","));
					int doublePlays = atoi(strsepcompatible(&lineBufferPnt, ","));

					averageAssists = averageAssists+assists;
					averageErrors = averageErrors+errors;
					averageGames = averageGames+games;
					averageGamesStarted = averageGamesStarted+gamesStarted;
					averageDoublePlays = averageDoublePlays+doublePlays;
				}

			}
		}
		averageAssists = averageAssists/i;
		averages.push_back(averageAssists);
		averageErrors = averageErrors/i;
		averages.push_back(averageErrors);
		averageGames = averageGames/i;
		averages.push_back(averageGames);
		averageGamesStarted = averageGamesStarted/i;
		averages.push_back(averageGamesStarted);
		averageDoublePlays = averageDoublePlays/i;
		averages.push_back(averageDoublePlays);
		//Closes file
		clearerr(stats);
		fclose(stats);
	} else {
		printf("\nInvalid file!");
	}
	//Returns vector of found data
	return averages;
}
