#include "Passenger.h"

Passenger::Passenger(int id, int destinationFloor)
    : id(id), destinationFloor(destinationFloor), elevatorId(-1), remainingRides(0), waitTime(0), totalWaitTime(0) , startWaitTime(startWaitTime){}



Passenger::Passenger(int id, int destinationFloor, int remainingRides)
        : id(id), destinationFloor(destinationFloor), elevatorId(-1), remainingRides(remainingRides), waitTime(0), totalWaitTime(0), startWaitTime(startWaitTime) {}
// void Passenger::generateNewDestinationFloor() {
//     int newDestination = rand() % 40 + 1;
//     while (newDestination == destinationFloor) {
//         newDestination = rand() % 40 + 1;
//     }
//     destinationFloor = newDestination;
// }

