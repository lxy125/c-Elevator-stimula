#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>
#include "Passenger.h"

class Elevator {
public:
    int id;
    int currentFloor;
    int direction;
    int capacity;
    int maxCapacity;
     int waitTime;
     int totalRunTime;//记录电梯的运行时间
    int totalIdleTime;//记录电梯的空闲时间
     bool isIdle; 
    std::vector<Passenger> passengers;
   

   bool isHighTraffic() const {
   return passengers.size() > static_cast<size_t>(maxCapacity) / 2;

}


    Elevator(int id, int maxCapacity);
    bool canReachFloor(int floor);//用于判断不同组的电梯能否到达某一楼层
};

#endif
