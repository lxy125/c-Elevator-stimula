#ifndef PASSENGER_H
#define PASSENGER_H
#include <bits/stdc++.h>

class Passenger {
public:
    int id;
    int destinationFloor;
    int elevatorId;
    int remainingRides;//乘客需要乘坐电梯的次数
    int waitTime;
    int totalWaitTime;//记录乘客的等待时间
    int currentFloor;
    int ridesCount = 0;  // 乘坐次数



    time_t startWaitTime;


Passenger(int id, int destinationFloor, time_t startWaitTime) 
    : id(id), destinationFloor(destinationFloor), elevatorId(-1), remainingRides(remainingRides), waitTime(0), totalWaitTime(0), startWaitTime(startWaitTime)  {    
    }


    Passenger(int id, int destinationFloor);


    Passenger(int id, int destinationFloor, int remainingRides);
        
    bool operator==(const Passenger& other) const {
        return id == other.id;
    }
   void generateNewDestinationFloor() {
    // Generate a random number between 0 and 1
    double r = static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);

    if (r < 0.5) {
        // Half of the passengers go to floors 1-25
        destinationFloor = std::rand() % 25 + 1;
    } else {
        // The other half go to floors 26-40
        destinationFloor = std::rand() % 15 + 26;
    }
}

};




#endif

