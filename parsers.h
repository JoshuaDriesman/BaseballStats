/*
 * stats.h
 *
 *  Created on: Jun 10, 2013
 *      Author: joshua
 */

#ifndef STATS_H_
#define STATS_H_
#include <vector>
using namespace std;
typedef struct {
	char playerID[13];
	int year;
	int stint;
	char team[4];
	char leagueID[3];
	char position[3];
	int games;
	int gamesStarted;
	int inOuts;
	int putOuts;
	int assists;
	int errors;
	int doublePlays;
	int passedBalls;
	int wildPitches;
	int opponentStolenBases;
	int opponentCaughtStealing;
	int zoneRating;

} databaseLine;

vector<databaseLine> findByYear(int year, char *fileName);
vector<databaseLine> findByName(char *name, char *fileName);
vector<int> findAverages(char *fileName);
char* mystrsep(char** stringp, const char* delim);

#endif /* STATS_H_ */
