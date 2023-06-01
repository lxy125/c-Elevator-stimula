#include "Elevator.h"


Elevator::Elevator(int id, int maxCapacity)
    : id(id), currentFloor(1), direction(0), capacity(0), maxCapacity(maxCapacity), waitTime(0), isIdle(true), totalRunTime(0), totalIdleTime(0) {}
bool Elevator::canReachFloor(int floor) {
    switch (id % 10) {
        case 0:
        case 1:
            return true;
        case 2:
        case 3:
            return (floor == 1) || (floor >= 25 && floor <= 40);
        case 4:
        case 5:
            return (floor >= 1 && floor <= 25);
        case 6:
        case 7:
            return (floor == 1) || (floor % 2 == 0 && floor >= 2 && floor <= 40);
        case 8:
        case 9:
            return (floor % 2 == 1 && floor >= 1 && floor <= 39);
        default:
            return false;
    }
}