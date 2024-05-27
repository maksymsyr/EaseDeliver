#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "mapping.h"
#include "trucksNboxes.h"

// debug
int debug = 0;
// print map
int printOutMap = 1;

int main(void)
{
	//test shortestPath - showcase the functionality
	//FILE* f = NULL;
	//f = fopen("lastData.txt", "w");
	//srand(time(NULL));
	//int randNo1 = rand() % 25;
	//int randNo2 = rand() % 25;
	//int randNo3 = rand() % 25;
	//int randNo4 = rand() % 25;
	//struct Map m = populateMap();
	//struct Point s = { randNo1, randNo2 };
	//struct Point e = { randNo3, randNo4 };
	////struct Point s = { 23, 23 };
	////struct Point e = { 24, 4 };
	//struct Route d;
	//if (validateDest(s) && validateDest(e)) {
	//	if (f) {
	//		fprintf(f, "s{%d,%d}, e{%d,%d}\n", randNo1, randNo2, randNo3, randNo4);
	//		fclose(f);
	//	}
	//	d = shortestPath(&m, s, e);

	//}
	//m = addRoute(&m, &d);
	//printMap(&m, 1, 1);

	
	//start main

	struct Truck blue = { .0, 0, .0, getBlueRoute(), {0} };
	struct Truck green = { .0, 0, .0, getGreenRoute(), {0} };
	struct Truck yellow = { .0, 0, .0, getYellowRoute(), {0} };
	struct Truck trucks[] = {blue, green, yellow};

	struct Map basemap = populateMap();

	// add route to map
	basemap = addRoute(&basemap, &blue.route);
	basemap = addRoute(&basemap, &green.route);
	basemap = addRoute(&basemap, &yellow.route);

	//struct Point s = { 19,17 };
	//struct Point e = { 11,24 };

	//struct Route a = shortestPath(&basemap, s, e);
	//basemap = addRoute(&basemap, &a);
	//printMap(&basemap,0,0);

	struct Box box = { 0 };
	double weight = 0;
	double size = 0;
	int destX = 0;
	char destY = 0;
	int id = 1;

	

	printf(
		"=================\n"
		"Seneca College Deliveries\n"
		"=================\n");
	int read = 0;
	do {
		struct Map basemap = populateMap();

		// add route to map
		basemap = addRoute(&basemap, &blue.route);
		basemap = addRoute(&basemap, &green.route);
		basemap = addRoute(&basemap, &yellow.route);

		int shortList[] = { 1, 1, 1 };

		printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
		read = scanf(" %lf %lf %d %c", &weight, &size, &destX, &destY);

		// flush the instream
		char ch = 0;
		while ((ch = getchar(ch)) && ch != '\n');

		if (read == 4) {
			if (destX == 0 && destY == 0 && read == 4) {
				printf("Invalid destination\n");
			}

			struct Point dest = { destX - 1, (int)destY - 65 };
			if (inputBox(&box, id++, size, weight, dest)) {
				if (selectTruck(shortList, &basemap, trucks, &box) != -1) {

					if (debug) printf("selectTrucks: %d %d %d\n", shortList[0], shortList[1], shortList[2]);		// print for debug

					int selected = -1;
					for (int i = 0; i < NO_TRUCKS; i++) {
						if (shortList[i] == 1) {
							selected = i;
							break;
						}
					}

					if (selected != -1) {

						// load the truck
						if (loadBox(&trucks[selected], &box) != 1) {
							printf("Trouble loading the box\n");
						};

						// set the symbol
						char symbol[10] = { 0 };
						if (trucks[selected].route.routeSymbol == 2) {
							strcpy(symbol, "BLUE");
						}
						else if (trucks[selected].route.routeSymbol == 4) {
							strcpy(symbol, "GREEN");
						}
						else if (trucks[selected].route.routeSymbol == 8) {
							strcpy(symbol, "YELLOW");
						}
						else if (trucks[selected].route.routeSymbol == 16) {
							strcpy(symbol, "DIVERSION");
						}

						printf("Ship on %s LINE, ", symbol);

						// check if the dest is en route
						int enRoute = 0;
						int start = 0;
						for (int i = 0; i < trucks[selected].route.numPoints && !enRoute; i++) {
							if (fabs(distance(&trucks[selected].route.points[i], &dest)) < 0.0000001 ||
								fabs(distance(&trucks[selected].route.points[i], &dest) - 1.0) < 0.0000001) {
								enRoute = 1;
								start = i;
							}
						}

						if (enRoute) {
							printf("no diversion\n");

							// print the map
							if (printOutMap) {
								//struct Route divRoute = { {0}, 0, 16 };
								struct Route divRoute = shortestDiversion(&basemap, &trucks[selected].route, dest);
								addPtToRoute(&divRoute, trucks[selected].route.points[start]);
								addPtToRoute(&divRoute, dest);
								basemap = addRoute(&basemap, &divRoute);
								printMap(&basemap, 1, 1);
							}

						}
						else {
							// find and print the diversion route
							struct Route divRoute = shortestDiversion(&basemap, &trucks[selected].route, dest);

							printf("divert:");

							for (int i = 0; i < divRoute.numPoints; i++) {
								printf(" %d%c", divRoute.points[i].row + 1, divRoute.points[i].col + 65);

								if (i == divRoute.numPoints - 1) {
									printf("\n");			// add a newline
								}
								else {
									printf(",");
								}
							}

							// add diversion to map
							basemap = addRoute(&basemap, &divRoute);

							// if print map
							if (printOutMap) printMap(&basemap, 1, 1);
						}
					}
					else {
						printf("No truck was selected.\n");
					}
				}
				else {	// if selectTruct returns -1
					printf("No truck was selected.\n");
				}
			}
		}
		else if(!(weight == 0 && size == 0)){   //if read !=4
			printf("Invalid input.\n");
			}

	//} while (weight > 0.0000001 && size > 0.000001);
	} while (!(read == 2 && weight == 0 && size == 0));

	printf("Thanks for shipping with Seneca!\n");

	return 0;
}