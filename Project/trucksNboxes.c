#include <stdio.h>
#include <math.h>
#include "trucksNboxes.h"
#include "mapping.h"

extern int debug;

// for debugging
void printDivRoute(struct Route* route) {
    struct Map testMap = populateMap();
    testMap = addRoute(&testMap, route);
    printMap(&testMap, 0, 0);
}

// starting the file

 int inputBox(struct Box* box, int id, double volume, double weight, struct Point dest)
{
    int valid = 0;

    if (box) {
        valid = id > 0 &&       // id is positive
            (volume == LARGE_BOX_VOL || volume == MED_BOX_VOL || volume == SMALL_BOX_VOL) && // box is of standard size
            weight > 0.0 && weight <= MAX_WEIGHT &&        // box weight is correct
            dest.row >= 0 && dest.row <= MAP_ROWS &&       // dest row is on the map
            dest.col >= 0 && dest.col <= MAP_COLS;         // dest col is on the map
        if (valid) {
            box->id = id;
            box->volume = volume;
            box->weight = weight;
            box->destination = dest;
        }
        else {

            if (!(dest.row >= 0 && dest.row <= MAP_ROWS &&       
                dest.col >= 0 && dest.col <= MAP_COLS)) {        
                printf("Invalid destination\n");
            }

            if (!(volume == LARGE_BOX_VOL || volume == MED_BOX_VOL || volume == SMALL_BOX_VOL)) {
                printf("Invalid size\n");
            }

            if (!(weight > 0.0 && weight <= MAX_WEIGHT)) {
                printf("Invalid weight (must be 1-1200 Kg.)\n");
            }

            box->id = 0;
            box->volume = 0.0;
            box->weight = 0.0;
            struct Point iPoint = { -1, -1 };
            box->destination = iPoint;
        }
    }
    else {
        valid = -1;
    }

    
    return valid;
}

int selectTruck(int shortList[],
    const struct Map* map,
    const struct Truck trucks[],
    const struct Box* box)
{
    int output = 0;

    // check if the box fit the truck
    for (int i = 0; i < NO_TRUCKS && output != -1; i++) {
        if (fitInTruck(&trucks[i], box) == -1) {    // -1 means invalid input
            output = -1;
        }
        else if (fitInTruck(&trucks[i], box) != 1) {
            shortList[i] = 0;
        }
    }
    if (debug) printf("fitInTruck(): %d %d %d\n", shortList[0], shortList[1], shortList[2]);		// print for debug


    // select by diversion path to dest
    if (output != -1) {
        output = selectByPath(shortList, map, trucks, box->destination);
        if (debug) printf("Select by path: %d %d %d\n", shortList[0], shortList[1], shortList[2]);		// print for debug

    }

    // select by weight load
    if (output != -1) {
        output = selectByWeightLoad(shortList, trucks);
        if (debug) printf("Select by weight: %d %d %d\n", shortList[0], shortList[1], shortList[2]);		// print for debug

    }

    // select by vol load
    if (output != -1) {
        output = selectByVolLoad(shortList, trucks);
        if (debug) printf("Select by load: %d %d %d\n", shortList[0], shortList[1], shortList[2]);		// print for debug

    }

    return output;
}

int fitInTruck(const struct Truck* truck, const struct Box* box)
{
    int exitCode = 0;
    if (validateTruck(truck) && validateBox(box)) {
        exitCode =
            box->volume <= (1.0 - truck->currVolLoad) * MAX_VOLUME &&
            box->weight <= (1.0 - truck->currWeightLoad) * MAX_WEIGHT;
    }
    else {
        exitCode = -1;
    }
    return exitCode;
}

int selectByPath(
        int shortList[],        
        const struct Map* map, 
        const struct Truck trucks[],
        const struct Point dest){
    int exitCode = 0;
    // validate arguments
    int valid = validateDest(dest) && map;
    for (int i = 0; i < NO_TRUCKS && valid; i++) {
        valid = validateTruck(&trucks[i]);
    }

    if (valid) {
        struct Route diverRoutes[NO_TRUCKS] = { 0 };
        for (int i = 0; i < NO_TRUCKS; i++) {
            if (shortList[i] == 1) {                // if the truck is selected
                // find the diver route for the selected truck

                diverRoutes[i] = shortestDiversion(map, &trucks[i].route, dest);
            }
        }

        // find the truck with shortest diversion path to dest
        //int selectedIndex = 0;                      // assuming the first truck is selected
        double shortestRouteLen = 99999.9;
        for (int i = 0; i < NO_TRUCKS; i++) {
            if (shortList[i] == 1 && shortestRouteLen > pathLen(&diverRoutes[i]) &&
                //pathLen(&diverRoutes[i]) - (-1) > 0.000000001) {
                validateRoute(&diverRoutes[i])){            // pathlen is not -1.0
                shortestRouteLen = pathLen(&diverRoutes[i]);
                //selectedIndex = i;
            }
        }

        // update the shortList[] array
        for (int i = 0; i < NO_TRUCKS; i++) {
            if (shortList[i] == 1) {
                // find the difference between pathlen(diverRoutes[i] and shortestRouteLen
                double difference = pathLen(&diverRoutes[i]) > shortestRouteLen ?
                    pathLen(&diverRoutes[i]) - shortestRouteLen :
                    shortestRouteLen - pathLen(&diverRoutes[i]);
                if (difference >= 0.000001) {   // check if two disances are equal
                    shortList[i] = 0;           // deselect the truck
                }
            }
        }
    }
    else {
        exitCode = -1;
    }

}

int selectByWeightLoad(int shortList[], const struct Truck trucks[])
{
    int exitCode = 0;
    // validate trucks  
    int valid = 1;
    for (int i = 0; i < NO_TRUCKS && valid; i++) {
        if (!validateTruck(&trucks[i])) {
            valid = 0;
        }
    }

    if (valid) {
        // find the lowest weight load
        double lowest = 999999.99;
        for (int i = 0; i < NO_TRUCKS; i++) {
            if ((trucks[i].currWeightLoad < lowest) && shortList[i] == 1) {
                lowest = trucks[i].currWeightLoad;
            }
        }

        // de-select the trucks with weightLoad > lowest
        for (int i = 0; i < NO_TRUCKS; i++) {
            double diff = lowest - trucks[i].currWeightLoad > 0 ?
                lowest - trucks[i].currWeightLoad :
                trucks[i].currWeightLoad - lowest;
            if (diff > 0.000001 && shortList[i] == 1) {
                shortList[i] = 0;
            }
        }
    }
    else {
        exitCode = -1;
    }

    return exitCode;
   
}

int selectByVolLoad(int shortList[], const struct Truck trucks[])
{
    int exitCode = 0;
    // validate trucks
    int valid = 1;
    for (int i = 0; i < NO_TRUCKS && valid; i++) {
        if (!validateTruck(&trucks[i])) {
            valid = 0;
        }
    }
    
    if (valid) {
        // find the lowest vol load
        double lowest = 999999.99;
        for (int i = 0; i < NO_TRUCKS; i++) {
            if (trucks[i].currVolLoad < lowest && shortList[i] == 1) {
                lowest = trucks[i].currVolLoad;
            }
        }

        // de-select the trucks with VolLoad > lowest
        for (int i = 0; i < NO_TRUCKS; i++) {
            double diff = lowest - trucks[i].currVolLoad > 0 ?
                lowest - trucks[i].currVolLoad :
                trucks[i].currVolLoad - lowest;
            if (diff > 0.000001 && shortList[i] == 1) {
                shortList[i] = 0;
            }
        }
    }
    else {
        exitCode = -1;
    }

    return exitCode;
}

struct Route shortestDiversion(const struct Map* map, const struct Route* route, const struct Point dest)
{
    struct Route output = { {0,0}, 0, 16};    // this will be an invalid route if we run validateRoute(output)
    // validate route and dest
    if (validateRoute(route) && validateDest(dest) && map) {
        output = shortestPath(map, route->points[0], dest);     // set inital output
        
        // make sure the output route is valid and move the dest by 1 cell
        int i = 0;
        while (!validateRoute(&output) && i < route->numPoints) {
            i++;
            output = shortestPath(map, route->points[i], dest);
        }

        if (validateRoute(&output)) {
            //// find the point squarely next to dest
            //struct Point dest_ = dest;
            //if (output.numPoints > 1 &&
            //    map->squares[output.points[output.numPoints - 1].row][output.points[output.numPoints - 1].col] == 1) { // if dest is a building
            //    dest_ = output.points[output.numPoints - 2];  // dest_ is 1 cell next to dest
            //}
            ////else {
            ////    dest_ = output.points[output.numPoints - 1];  // dest_ is the only point on the route
            ////}
            output = shortestPath(map, route->points[0], dest);     // remove dest from output

            // Loop all the points on the route and find the shortest diversion
            for (int i = 1; i < route->numPoints; i++) {
                struct Route currentPath = shortestPath(map, route->points[i], dest);
                if (pathLen(&output) > pathLen(&currentPath) &&
                    validateRoute(&currentPath)) {      // current path is valid
                    output = currentPath;

                }
            }
        }

        // add back the dest if it's not in the out put
        if (output.points[output.numPoints - 1].row != dest.row || 
            output.points[output.numPoints - 1].col != dest.col) {
            addPtToRoute(&output, dest);
        }
    }



    return output;
}

double pathLen(const struct Route* route)
{
    double result = 0.0;
    if (validateRoute(route)) {
        for (int i = 1; i < route->numPoints; i++) {
            result += distance(&route->points[i], &route->points[i - 1]);
        }
    }
    else {
        result = -1.0;
    }
    return result;
}

int loadBox(struct Truck* truck, const struct Box* box)
{
    int exitCode = 0;

    if (validateTruck(truck) && validateBox(box)) { 
        if (fitInTruck(truck, box)) {
            truck->loadedBoxes[truck->boxCount++] = *box;
            truck->currWeightLoad += (box->weight / MAX_WEIGHT);
            truck->currVolLoad += (box->volume / MAX_VOLUME);
            exitCode = 1;
        }
    }
    else {
        exitCode = -1;
    }

    return exitCode;
}

int validateBox(const struct Box* box)
{
    return box && 
        box->id > 0 && 
        box->weight > 0.0 &&
        (box->volume == SMALL_BOX_VOL ||
            box->volume == LARGE_BOX_VOL ||
            box->volume == MED_BOX_VOL) &&
        validateDest(box->destination);
}

int validateTruck(const struct Truck* truck)
{
    int output = truck &&
        truck->currWeightLoad >= 0.0 && truck->currWeightLoad <= 1.0 &&
        truck->boxCount >= 0 && truck->boxCount <= MAX_NO_BOXES &&
        truck->currVolLoad >= 0.0 && truck->currVolLoad <= 1.0 &&
        validateRoute(&truck->route);

    if (!output) printf("Invalid truck\n");

    return output;
}
