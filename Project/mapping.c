#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mapping.h"
#include "math.h"

void printDivRoute(struct Route* route);
double pathLen(const struct Route* route);
extern int debug;


struct Map populateMap()
{
	struct Map result = {
		//0	1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4
		//A B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y
		{
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//0
		{0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},	//1
		{0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},	//2
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//3
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//4
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//5
		{1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},	//6
		{1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1},	//7
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1},	//8
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//9
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//10
		{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//11
		{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//12
		{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//13
		{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//14
		{1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//15
		{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//16
		{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//17
		{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},	//18
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//19
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//20
		{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},	//21
		{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1},	//22
		{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},	//23
		{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}		//24
		},
		MAP_ROWS, MAP_COLS
	};
	return result;
}

int getNumRows(const struct Map* map)
{
	return map->numRows;
}

int getNumCols(const struct Map* map)
{
	return map->numCols;
}

void printMap(const struct Map* map, const int base1, const int alphaCols)
{
	//              01234567890123456
	//              1248F
	char sym[] = { " XB?G?.?Y?-?*?+?D" };
	int r, c, rowMax;

	rowMax = map->numRows + base1;

	printf("%4s", " ");
	for (c = 0; c < map->numCols; c++)
	{
		if (alphaCols) printf("%c", 'A' + c);
		else printf("%d", c % 10);
	}
	printf("\n");
	printf("%4s", " ");
	for (c = 0; c < map->numCols; c++)
	{
		printf("-");
	}
	printf("\n");

	for (r = base1; r < rowMax; r++)
	{
		printf("%3d|", r);
		for (c = 0; c < map->numCols; c++)
		{
			if (map->squares[r - base1][c] >= 16) {
				printf("\033[0;31m%c", sym[16]);	// ser color to red
				printf("\033[0m");					// reset the color
			}
			else {
				printf("%c", sym[map->squares[r - base1][c]]);
			}
		}
		printf("\n");
	}
}

struct Route getBlueRoute()
{
	struct Route result = {
		{
			{0, 0},
			{1, 0},
			{2, 0},
			{3, 0},
			{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {4, 8},{4, 9},
			{5, 9},
			{6, 9},
			{7, 9},
			{8, 9},
			{9, 9},
			{10, 9},{10, 10},
			{11, 10},
			{12, 10},
			{13, 10},
			{14, 10},
			{15, 10},
			{16, 10},
			{17, 10},{17, 11},{17, 12},{17, 13},{17, 14},{17, 15},{17, 16},{17, 17},{17, 18},{17, 19},{17, 20},
				{17, 21},{17, 22},{17, 23},{17, 24},
		},
			42, BLUE
	};
	return result;
}

struct Route getGreenRoute()
{
	struct Route result = {
		{
			{0, 0},
			{1, 0},
			{2, 0},
			{3, 0},
			{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {4, 8},{4, 9},{4, 10},{4, 11},
			{3, 11},
			{2, 11},
			{1, 11},
			{0, 11},{0, 12},{0, 13},{0, 14},{0, 15},{0, 16},{0, 17},{0, 18},{0, 19},
			{1, 19},
			{2, 19},
			{3, 19},
			{4, 19},
			{5, 19},
			{6, 19},
			{7, 19},
			{8, 19},
			{9, 19},{9, 20},{9, 21},{9, 22},{9, 23},{9, 24}

		},
			42, GREEN
	};
	return result;
}

struct Route getYellowRoute()
{
	struct Route result = {
		{
			{0, 0},
			{1, 0},
			{2, 0},
			{3, 0},
			{4, 0}, {4, 1}, {4, 2}, {4, 3},
			{5, 3},
			{6, 3},
			{7, 3},
			{8, 3},
			{9, 3},{9, 2},{9, 1},
			{10, 1},
			{11, 1},
			{12, 1},
			{13, 1},
			{14, 1},
			{15, 1},
			{16, 1},
			{17, 1},
			{18, 1},
			{19, 1},{19, 2},{19, 3},{19, 4},{19, 5},{19, 6},{19, 7},{19, 8},{19, 9},{19, 10},{19, 11},{19, 12},
				{19, 13},{19, 14},{19, 15},{19, 16},{19, 17},{19, 18},{19, 19},{19, 20},{19, 21},{19, 22},{19, 23},{19, 24}
		},
			48, YELLOW
	};
	return result;
}

struct Map addRoute(const struct Map* map, const struct Route* route)
{
	int r, c;
	struct Map result = { {0}, 0 };

	for (r = 0; r < map->numRows; r++)
	{
		for (c = 0; c < map->numCols; c++)
		{
			result.squares[r][c] = map->squares[r][c];
		}
	}
	result.numRows = map->numRows;
	result.numCols = map->numCols;

	for (r = 0; r < route->numPoints; r++)
	{
		result.squares[route->points[r].row][route->points[r].col] += route->routeSymbol;
	}

	return result;
}

void addPtToRoute(struct Route* route, struct Point pt)
{
	route->points[route->numPoints++] = pt;
}

void addPointToRoute(struct Route* route, const int row, const int col)
{
	struct Point pt = { row, col };
	addPtToRoute(route, pt);
}

//void addPointToRouteIfNot(struct Route* route, const int row, const int col, const struct Point notThis)
void addPointToRouteIfNot(struct Route* route, const int row, const int col, struct Route* backpath)
{
	struct Point pt = { row, col };
	int alreadyAdded = 0;

	// add pt to backpath is pt is not in backpath
	for (int i = 0; i < backpath->numPoints && !alreadyAdded; i++) {
		if (fabs(distance(&pt, &backpath->points[i])) < 0.0000001) {
			alreadyAdded = 1;
		}
	}
	//if (notThis.row != row || notThis.col != col) addPtToRoute(route, pt);
	if(!alreadyAdded) addPtToRoute(route, pt);

}

double distance(const struct Point* p1, const struct Point* p2)
{
	int deltaRow = p2->row - p1->row;
	int deltaCol = p2->col - p1->col;

	return sqrt((double)(deltaRow * deltaRow + deltaCol * deltaCol));
}

struct Route shortestPath(const struct Map* map, const struct Point start, const struct Point dest)
{
	int moveMode = 0;
	struct Route result = { {0,0}, 0, DIVERSION };
	struct Route result1 = { {0,0}, 0, DIVERSION };
	struct Route blackList = { {0,0}, 0, DIVERSION };	//can't go here next
	//struct Point last = { -1, -1 };
	struct Point current = start;
	struct Route possible = { {0,0},0,0 };
	int close = 0;

	addPtToRoute(&result, start);		// add the start point

	while (moveMode < 2) { // run the whole algorithm two times storing output in result1 and result
		// reset these so the loop can run the 2nd time
		current = start;
		result.numPoints = 1;
		blackList.numPoints = 0;

		// start the loop
		if (!(result.points[0].row == dest.row &&
			result.points[0].col == dest.col)) { // if dest is not start
			int windingStart = -1;			// this is for winding removal
			int windingStop = -1;			// this is for winding removal
			int noPoinstInWind = -1;			// this is for loop removal
			int goBackTo = -2;
			int windingRemoval = 1;				// toggle debug

			//while (!eqPt(current, dest) && close >= 0)
			while (fabs(distance(&current, &dest) - 1.0 > 0.0000001 /*&& goBackTo != -1*/ /*&& close >= 0*/))
			{
				//possible = getPossibleMoves(map, current, last);
				possible = getPossibleMoves(map, current, &blackList);
				close = getClosestPoint(&possible, dest);
				if (close >= 0) // if there are possible moves
				{
					// find 2 next possible best moves
					struct Route nextMoves = { 0 };
					nextMoves.numPoints = 0;
					for (int i = 0; i < 4; i++) {
						if (fabs(
							distance(&possible.points[close], &dest) -
							distance(&possible.points[i], &dest
							)) < 0.000001) {
							addPtToRoute(&nextMoves, possible.points[i]);
						}
					}
					// get a random number
					/*srand(time(NULL));
					int randNo = rand() % 2;*/
					current = nextMoves.numPoints > 1 ?
						nextMoves.points[moveMode] :
						nextMoves.points[0];

					//last = current;
					//current = possible.points[close];
					addPtToRoute(&result, current);
					if (debug) printDivRoute(&result);		//print for debugging
					addPointToRouteIfNot(&blackList, current.row, current.col, &blackList);		// this is more robust
				}
				else { // if there is no possible move,
					// go back to the point with possible move and is nearest to the dest
					goBackTo = blackList.numPoints - 2;
					struct Route possibleGoBackPoints = { 0 };
					possibleGoBackPoints.numPoints = 0;

					struct Map map1 = *map;		// for debugging

					while (goBackTo >= 0) {
						struct Point goBackPoint = blackList.points[goBackTo];

						// debugging
						if (debug) {
							map1 = addRoute(&map1, &blackList);
							map1.squares[goBackPoint.row][goBackPoint.col] = 15;
							printMap(&map1, 0, 0);
						}
						
						struct Route possible_ = getPossibleMoves(map, goBackPoint, &blackList);
						int close = getClosestPoint(&possible_, dest);
						if (close >= 0) {
							addPtToRoute(&possibleGoBackPoints, blackList.points[goBackTo]);
						}
						goBackTo--;
					}

					//if (goBackTo == -1) break;

					// select the point possibleGoBackPoints that is nearest to dest
					double min = 9999999.9;
					if (possibleGoBackPoints.numPoints) { //if there is possible move
						for (int i = 0; i < possibleGoBackPoints.numPoints; i++) {
							if (min > distance(&possibleGoBackPoints.points[i], &dest)) {
								min = distance(&possibleGoBackPoints.points[i], &dest);
								current = possibleGoBackPoints.points[i];

							}
						}
					}
					else {
					/*	struct Route invalidRoute = { 0 };
						return invalidRoute;*/
						if (moveMode == 0) {
							moveMode = 1;
							current = start;
							result.numPoints = 1;
							blackList.numPoints = 0;
						} else {
							if (validateRoute(&result1)) {
								return result1;
							}
							else {
								struct Route invalidRoute = { 0 };
								return invalidRoute;
							}
						}
					}

					//debugging
					if (debug) {
						map1.squares[current.row][current.col] = 10;
						printMap(&map1, 0, 0);
						printf("");
					}

					// update numPoints
					for (int i = 0; i < result.numPoints; i++) {
						if (result.points[i].row == current.row &&
							result.points[i].col == current.col) {
							result.numPoints = i + 1;
							break;
						}
					}
				}
			}
			if (!(result.points[result.numPoints - 1].row == dest.row &&
				result.points[result.numPoints - 1].col == dest.col)) {
				addPtToRoute(&result, dest);	// add the dest
			}

			if (windingRemoval) {
				int winding = 0;
				int noLoops = MAP_ROWS;
				for (int n = 0; n < noLoops; n++) {
					for (int i = 0; i < result.numPoints - 3; i++) { //not including the last point (dest)
						// find the 4 points on the path that squarely surrounds the current point
						struct Point currentP = result.points[i];
						struct Point pointsAroundCurrent[] = {	// array of size 4
							{currentP.row - 1, currentP.col},		//top
							{currentP.row, currentP.col + 1},		//right
							{currentP.row + 1, currentP.col},		// bottom
							{currentP.row, currentP.col - 1}		// left
						};

						// check if the third point is next to current point
						winding = 0;
						for (int j = 0; j < 4 && !winding; j++) {
							if (result.points[i + 3].row == pointsAroundCurrent[j].row &&
								result.points[i + 3].col == pointsAroundCurrent[j].col) {
								winding = 1;
								if (winding) {
									windingStart = i;
									windingStop = i + 3;
									noPoinstInWind = windingStop - windingStart - 1;
								}
							}
						}

						// removing winding
						if (winding) {
							//printDivRoute(&result);		// for debugging
							for (int i = windingStart + 1; i < result.numPoints - noPoinstInWind; i++) {
								result.points[i] = result.points[i + noPoinstInWind];
							}
							result.numPoints -= noPoinstInWind;
							//printDivRoute(&result);		// for debugging
						}
					}
				}
			}
		}
		//printDivRoute(&result);		//print for debugging

		if (moveMode == 0) {
			result1 = result;
		}
			
		moveMode++;
	}

	//compare result1 and result
	//printDivRoute(&result);			// print for debug
	//printDivRoute(&result1);		// print for debug
	if (validateRoute(&result1) && validateRoute(&result)) {
		if (pathLen(&result1) < pathLen(&result)) {
			result = result1;
		}
	}
	else if (!validateRoute(&result)) {
		result = result1;
	}
	

	return result;
}

//struct Route getPossibleMoves(const struct Map* map, const struct Point p1, const struct Point backpath)
struct Route getPossibleMoves(const struct Map* map, const struct Point p1, struct Route* backpath)
{
	struct Route result = { {0,0}, 0, DIVERSION };

	if (p1.row > 0)
	{
		if (map->squares[p1.row - 1][p1.col] != 1) addPointToRouteIfNot(&result, p1.row - 1, p1.col, backpath);	// square above
		//if (p1.col > 0 && map->squares[p1.row - 1][p1.col - 1] != 1) addPointToRouteIfNot(&result, p1.row - 1, p1.col - 1, backpath);	// top left
		//if (p1.col < (map->numCols - 1) && map->squares[p1.row - 1][p1.col + 1] != 1) addPointToRouteIfNot(&result, p1.row - 1, p1.col + 1, backpath);	// top right
	}
	if (p1.col > 0 && map->squares[p1.row][p1.col - 1] != 1)addPointToRouteIfNot(&result, p1.row, p1.col - 1, backpath);	// left
	if (p1.col < (map->numCols - 1) && map->squares[p1.row][p1.col + 1] != 1)addPointToRouteIfNot(&result, p1.row, p1.col + 1, backpath);	// right
	if (p1.row < (map->numRows - 1))
	{
		if (map->squares[p1.row + 1][p1.col] != 1) addPointToRouteIfNot(&result, p1.row + 1, p1.col, backpath);	// square below
		//if (p1.col > 0 && map->squares[p1.row + 1][p1.col - 1] != 1) addPointToRouteIfNot(&result, p1.row + 1, p1.col - 1, backpath);	// bot left
		//if (p1.col < (map->numCols - 1) && map->squares[p1.row + 1][p1.col + 1] != 1) addPointToRouteIfNot(&result, p1.row + 1, p1.col + 1, backpath);	// bot right
	}

	return result;
}

int eqPt(const struct Point p1, const struct Point p2)
{
	return p1.row == p2.row && p1.col == p2.col;
}

int getClosestPoint(const struct Route* route, const struct Point pt)
{
	int i, closestIdx = -1;
	double closestDist = 999999.99, dist;

	for (i = 0; i < route->numPoints; i++)
	{
		dist = distance(&pt, &route->points[i]);
		if (dist < closestDist)
		{
			closestDist = dist;
			closestIdx = i;
		}
	}
	return closestIdx;
}

int validateRoute(const struct Route* route)
{
	int valid = route->numPoints <= MAX_ROUTE;    //coerce _Bool to int
		//route->points[0].row == 0 &&                //route must start from {0,0}
		//route->points[0].col == 0;

	for (int i = 0; i < route->numPoints && valid; i++) {
		valid = route->points[i].row >= 0 &&
			route->points[i].row <= MAP_ROWS &&
			route->points[i].col >= 0 &&
			route->points[i].col <= MAP_COLS;       //all points must be in the map
		if (i > 0 && valid) {
			valid = abs(route->points[i].row - route->points[i - 1].row) <= 1 &&
					abs(route->points[i].col - route->points[i - 1].col) <= 1 && //two consecutive points must be next to each other
					(abs(route->points[i].row - route->points[i - 1].row) > 0 ||
					abs(route->points[i].col - route->points[i - 1].col) > 0);	// no duplicate points
		}
			
	}
	return valid;
}

int validateDest(const struct Point dest)
{
	struct Map map = populateMap();

	int output = 1;
	
	output = dest.col >= 0 &&
		dest.col < MAP_COLS &&
		dest.row >= 0 &&
		dest.row < MAP_ROWS;
	if (output) {
		struct Route blackList = { 0 };
		struct Route surroundPoints = getPossibleMoves(&map, dest, &blackList);
		int connected = 0;	//connected means it's not surrounded by buildings
		for (int i = 0; i < surroundPoints.numPoints; i++) {
			if (map.squares[surroundPoints.points[i].row][surroundPoints.points[i].col] != 1) {
				connected = 1;
				break;
			}
		}
		output = connected;
	}
		
	if (!output) printf("Invalid destination\n");
	return output;
}
