#include "mapping.h"

#ifndef _SENECA_TRUCK_N_BOX_H
#define _SENECA_TRUCK_N_BOX_H

#define MAX_NO_BOXES 100
#define MAX_WEIGHT 1200.0
#define MAX_VOLUME 50.0
#define SMALL_BOX_VOL 0.5
#define MED_BOX_VOL 1.0
#define LARGE_BOX_VOL 5.0
#define NO_TRUCKS 3

//we need a struct for weight, we need a struct for size of the boxes
//struct for the box => the weight and the size, the destination
//the struct to save the alterations to build the route

/// <summary>
/// A box has an id, weight in kg, volume in cubic meter, and a destination of type Point
/// </summary>
struct Box {
    int id;
    double weight;
    double volume;
    struct Point destination;
};

/// <summary>
/// A truck has a route of type Route, weight and volume capacity, as well as the current load.
/// </summary>
struct Truck {
    double currWeightLoad;                         //current weight load (0-1)
    int boxCount;
    double currVolLoad;                         // current volume load (0-1)
    struct Route route;         
    struct Box loadedBoxes[MAX_NO_BOXES];       // should be stored on the heap?   
};


// the functions

/// <summary>
/// Prompt and read box info
/// </summary>
void readBox();

/// <summary>
/// input the box information
/// </summary>
/// <param name="box">the pointer to a box of type Box</param>
/// <param name="id">the box ID</param>
/// <param name="volume">the box volume</param>
/// <param name="weight"> the box weight</param>
/// <param name="dest"> the box destination, of type Point</param>
/// <returns>return -1 if box is null. Else, return 1 if the input data are valid. 
/// Otherwise, return 0.</returns>
int inputBox(struct Box* box, int id, double volume, double weight, struct Point dest);

/// <summary>
/// Select the best truck based on the box destination, size and weight by
/// modifying the shortList array
/// </summary>
/// <param name="shortList"> the short list array (return via parameter)</param>
/// <param name="map"> the map</param>
/// <param name="trucks"> the array of trucks to choose from</param>
/// <param name="box">the pointer to the box to be loaded</param>
/// <returns> Return 0 if there if all argument is valid. 
/// Return -1 if any argument is invalid</returns>
int selectTruck(int shortList[], const struct Map* map, const struct Truck trucks[], const struct Box* box);

/// <summary>
/// Check if a box fits in a truck by checking its size and weight
/// </summary>
/// <param name="truck">a pointer to the truck</param>
/// <param name="box"> a pointer to the box</param>
/// <returns>-1 if the any pointer is null. Else, return 1 if the box fits,
///  0 otherwise</returns>
int fitInTruck(const struct Truck* truck, const struct Box* box);

/// <summary>
/// Compare the shortest diversion paths from each route to the destination and select the truck(s)/route(s)
/// with the shortest path by modifying the shortList[] array
/// </summary>
/// <param name="shortList"> a boolean paralel array showing with truck in
/// the trucks arrayis selected</param>
/// <param name="map">the pointer to the map</param>
/// <param name="trucks">the array of trucks to choose from</param>
/// <param name="dest">the destination point</param>
/// <returns>-1 if the any pointer is null or invalid. Else, return 0</returns> 
int selectByPath(int shortList[], const struct Map* map, const struct Truck trucks[], const struct Point dest);

/// <summary>
/// Compare the current weight load of the trucks and select the truck(s)
/// with the least weight load by modifying the shortList[] array
/// </summary>
/// <param name="shortList"> a boolean paralel array showing which truck in
/// the trucks array is selected</param>
/// <param name="trucks">the array of trucks to choose from</param>
/// <returns>-1 if the any pointer is null or invalid. Else, return 0</returns>  
int selectByWeightLoad(int shortList[], const struct Truck trucks[]);

/// <summary>
/// Compare the current volume load and select the truck(s)
/// with the least volume load by modifying the shortList[] array
/// </summary>
/// <param name="shortList"> a boolean paralel array showing which truck in
/// the trucks array is selected</param>
/// <param name="trucks">the array of trucks to choose from</param>
/// <returns>-1 if the any pointer is null or invalid. Else, return 0</returns> 
int selectByVolLoad(int shortList[], const struct Truck trucks[]);

/// <summary>
/// Find the shortest diversion from a route to a destination
/// </summary>
/// <param name="map">a pointer to the map</param>
/// <param name="route">a pointer to the route</param>
/// <param name="dest">the destination of type Point</param>
/// <returns>the shortest diversion from the route to the destination, of type Route</returns>
struct Route shortestDiversion(const struct Map* map, const struct Route* route, const struct Point dest);

/// <summary>
/// Calculate the length of a route
/// </summary>
/// <param name="route"> The route</param>
/// <returns> the length of the route of type double. 
/// Return -1.0 if input is invalid</returns>
double pathLen(const struct Route* route);

/// <summary>
/// Load a box onto a truck and update the truck's current boxCount,
/// volume and weight load accordingly
/// </summary>
/// <param name="truck"> A pointer to the truck where the box is to be loaded</param>
/// <param name="box"> A pointer to the box to be loaded</param>
/// <returns>return -1 if any of the pointer is null. Else, return 1 if the box was 
/// loaded successfully. 0 otherwise.</returns>
int loadBox(struct Truck* truck, const struct Box* box);

/// <summary>
/// Validate a Box pointer
/// </summary>
/// <param name="box">the Box pointer</param>
/// <returns>1 if valid, 0 otherwise</returns>
int validateBox(const struct Box* box);

/// <summary>
/// Validate a Truck pointer
/// </summary>
/// <param name="truck">the Truck pointer</param>
/// <returns>1 if valid, 0 otherwise</returns>
int validateTruck(const struct Truck* truck);

#endif
