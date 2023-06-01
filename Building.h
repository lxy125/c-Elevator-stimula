#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include "Elevator.h"
#include "Passenger.h"
#include <map>
using namespace std;

class Building {
private:
    int numElevators;
    int numFloors;
    int numPassengers;

public:
    std::vector<Elevator> elevators;
    std::vector<Passenger> passengers;
    Building(int numElevators, int numFloors, int numPassengers);
    void runSimulation(int numPassengers, int maxTime);
    void generatePassengers(int numPassengers);
    void updatePassengers();
    void updateElevators();
    void displaySimulationInfo();
    bool simulationFinished();
    void displaySimulationInfo(int currentTime);
    map<int, vector<Passenger>> waitingPassengers;//等待乘坐电梯的乘客
    void displayStats();
};
#endif
