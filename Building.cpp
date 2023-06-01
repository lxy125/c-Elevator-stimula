#include "Building.h"
#include <bits/stdc++.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <algorithm> 
using namespace std;

Building::Building(int numElevators, int numFloors, int numPassengers)
    : numElevators(numElevators), numFloors(numFloors), numPassengers(numPassengers) {

    // 创建电梯
    for (int i = 0; i < numElevators; ++i) {
        elevators.emplace_back(i, numFloors);
    }

    // 创建乘客
    for (int i = 0; i < numPassengers; ++i) {
        int destinationFloor = std::rand() % (numFloors - 1) + 2;
        int remainingRides = std::rand() % 10 + 1;
        passengers.emplace_back(i, destinationFloor, remainingRides);
    }

    // for (int i = 0; i < numPassengers; i++) {
    //     int destinationFloor = rand() % 40 + 1;
    //     Passenger passenger(i, destinationFloor);
    //     passengers.push_back(passenger);

    //     for (Elevator &elevator : elevators) {
    //         if (elevator.canReachFloor(destinationFloor)) {//判断乘客目的地是否符合要求
    //             waitingPassengers[destinationFloor].push_back(passenger);
    //             break;
    //         }
    //     }
    // }

    // 假设 passengers 是所有乘客的列表， elevators 是所有电梯的列表
for (Passenger& passenger : passengers) {
    if (elevators[2].canReachFloor(passenger.destinationFloor) && elevators[2].capacity < elevators[2].maxCapacity) {
        // 将乘客分配给2号电梯
        elevators[2].passengers.push_back(passenger);
        elevators[2].capacity++;
    } else if (elevators[3].canReachFloor(passenger.destinationFloor) && elevators[3].capacity < elevators[3].maxCapacity) {
        // 将乘客分配给3号电梯
        elevators[3].passengers.push_back(passenger);
        elevators[3].capacity++;
    } else {
        // 将乘客分配给其他电梯
        for (int i = 0; i < numElevators; i++) {
            if (i != 2 && i != 3 && elevators[i].canReachFloor(passenger.destinationFloor) && elevators[i].capacity < elevators[i].maxCapacity) {
                elevators[i].passengers.push_back(passenger);
                elevators[i].capacity++;
                break;
            }
        }
    }
}



    // 在开始时给电梯分配乘客
    for (auto &passenger : passengers) {
        int randomElevatorIndex = std::rand() % elevators.size();//将电梯随机
        Elevator &selectedElevator = elevators[randomElevatorIndex];
        if (selectedElevator.capacity < selectedElevator.maxCapacity&&selectedElevator.canReachFloor(passenger.destinationFloor)) {
            passenger.elevatorId = selectedElevator.id;
            selectedElevator.passengers.push_back(passenger);
            selectedElevator.capacity++;
        } else {
            waitingPassengers[1].push_back(passenger);
        }
    }
}


// 实现其他成员函数，如生成乘客、更新乘客状态、更新电梯状态、显示仿真信息等。

void Building::generatePassengers(int numPassengers) {
    for (int i = 0; i < numPassengers; i++) {
        int destinationFloor = rand() % 40 + 1;
        Passenger passenger(i, destinationFloor, time(0));
        passengers.push_back(passenger);

        for (Elevator &elevator : elevators) {
            if (elevator.canReachFloor(destinationFloor)) {//判断乘客目的地是否符合要求
                waitingPassengers[destinationFloor].push_back(passenger);
                break;
            }
        }
    }
}




void Building::displaySimulationInfo(int currentTime)
{
    std::cout << "Simulation Info:" << std::endl;
    std::cout << "Current time: " << currentTime << std::endl;
    for (const auto &elevator : elevators) {
        std::cout << "Elevator " << elevator.id << ": ";
        std::cout << "Floor " << elevator.currentFloor << ", ";
        std::cout << "Direction ";
        if (elevator.direction == 1) {
            std::cout << "Up, ";
        } else if (elevator.direction == -1) {
            std::cout << "Down, ";
        } else {
            std::cout << "Idle, ";
        }
        std::cout << "Passengers ";
        for (const auto &passenger : elevator.passengers) {
            std::cout << passenger.id << "-" << passenger.destinationFloor << " ";
        }


        std::cout << std::endl;
    }
}



void Building::updatePassengers()
{
    for (auto &passenger : passengers) {//遍历所有乘客
        if (passenger.elevatorId == -1) {
            passenger.totalWaitTime++;//乘客等待时间+1
        }



        if (passenger.elevatorId == -1) {
            if (passenger.waitTime > 0) {//乘客在上下电梯
                passenger.waitTime--;
            } else {
                // 将等待中的乘客添加到 waitingPassengers
                waitingPassengers[passenger.currentFloor].push_back(passenger);

                // 获取朝向乘客目标楼层方向的未满载电梯列表
                std::vector<size_t> nonFullElevators;
                for (size_t i = 0; i < elevators.size(); ++i) {
                    if (elevators[i].capacity < elevators[i].maxCapacity &&
                        ((elevators[i].direction == 1 && passenger.destinationFloor > elevators[i].currentFloor) ||
                         (elevators[i].direction == -1 && passenger.destinationFloor < elevators[i].currentFloor))) {
                        nonFullElevators.push_back(i);
                    }
                }

                //当乘客在电梯里时，用当前时间来更新他们的startWaitTime：
                if (!nonFullElevators.empty()) {
                    size_t randomIndex = std::rand() % nonFullElevators.size();
                    size_t selectedElevator = nonFullElevators[randomIndex];
                    passenger.elevatorId = selectedElevator;
                    elevators[selectedElevator].passengers.push_back(passenger);
                    elevators[selectedElevator].capacity++;
                    


                   double waitTimeInSeconds = std::difftime(std::time(0), passenger.startWaitTime);
               if (waitTimeInSeconds > 1) {  // 如果等待时间过长
                     std::cout << "Warning: Passenger " << passenger.id << " waited for " << waitTimeInSeconds << " seconds.\n";
                }

                       // 更新 startWaitTime 为当前时间
                        passenger.startWaitTime = std::time(0);









                    // 乘客上了电梯，从 waitingPassengers 中移除已经分配给电梯的乘客
                    auto &waitingPassengersAtFloor = waitingPassengers[passenger.currentFloor];
                    auto it = std::find(waitingPassengersAtFloor.begin(), waitingPassengersAtFloor.end(), passenger);
                    if (it != waitingPassengersAtFloor.end()) {
                        waitingPassengersAtFloor.erase(it);
                    }
                } else {
                    passenger.waitTime = std::rand() % 111 + 10; // 随机等待时间（10-120秒）
                }
            }
        } else {
            // 如果乘客在电梯内，检查是否到达目标楼层
            Elevator &elevator = elevators[passenger.elevatorId];
            
            if (elevator.currentFloor == passenger.destinationFloor) {
                if (passenger.remainingRides > 1) {
                    passenger.remainingRides--;
                    passenger.generateNewDestinationFloor();
                    passenger.waitTime = std::rand() % 111 + 10; // 随机等待时间（10-120秒）
                    passenger.elevatorId = -1;

                    // 将乘客添加回 waitingPassengers
                    waitingPassengers[passenger.currentFloor].push_back(passenger);

                    // 从电梯中移除乘客
                    auto it = std::find(elevator.passengers.begin(), elevator.passengers.end(), passenger);
                    if (it != elevator.passengers.end()) {
                        elevator.passengers.erase(it);
                        elevator.capacity--;
                    }
                } else {
                    passenger.remainingRides--;
                    passenger.destinationFloor = 1;
                    passenger.elevatorId = -1;
                    auto it = std::find(elevator.passengers.begin(), elevator.passengers.end(), passenger);
                    if (it != elevator.passengers.end()) {
                        elevator.passengers.erase(it);
                        elevator.capacity--;
                    }
                }
            }
        }
    }
}

void Building::updateElevators()
{
  



    for (auto &elevator : elevators) {
        if (elevator.isIdle) {
            elevator.totalIdleTime++;//电梯时间
        } else {
            elevator.totalRunTime++;
        }



        if (elevator.waitTime > 0) {
            elevator.waitTime--;
            continue;
        }

       if (!elevator.passengers.empty()) {
        elevator.isIdle = false; // 电梯正在运行
            elevator.direction = elevator.passengers.front().destinationFloor > elevator.currentFloor ? 1 : -1;//电梯方向
            elevator.currentFloor += elevator.direction;

            for (auto it = elevator.passengers.begin(); it != elevator.passengers.end();) {//遍历电梯内的乘客
                if (it->destinationFloor == elevator.currentFloor) {
                    it = elevator.passengers.erase(it);
                    elevator.capacity--;

                    // 当有乘客上下电梯时，增加等待时间
                    elevator.waitTime = 2; // 假设上下电梯需要 2 个时间单位
                } else {
                    ++it;
                }
            }

            if (elevator.passengers.empty()) {
                elevator.direction = 0;
                elevator.isIdle = true; // 电梯处于空闲状态
            }
        }else{
            elevator.isIdle = true; // 电梯处于空闲状态
        }
        

        //检查有没有乘客在当前楼层等待电梯
        auto waitingPassengersAtFloor = waitingPassengers.find(elevator.currentFloor);
        if (waitingPassengersAtFloor != waitingPassengers.end()) {//有乘客在当前楼层等待电梯
            for (auto it = waitingPassengersAtFloor->second.begin(); it != waitingPassengersAtFloor->second.end();) {//
                if (elevator.capacity < elevator.maxCapacity &&
                    ((it->destinationFloor > elevator.currentFloor && elevator.direction == 1) ||
                     (it->destinationFloor < elevator.currentFloor && elevator.direction == -1))) {

                    elevator.passengers.push_back(*it);
                    elevator.capacity++;
                    it->elevatorId = elevator.id;
                    elevator.isIdle = false; // 电梯正在运行
                    // 从 waitingPassengers 中移除该乘客
                    it = waitingPassengersAtFloor->second.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
}









// void Building::updateElevators()
// {
//     for (auto &elevator : elevators) {
//         if (elevator.waitTime > 0) {
//             elevator.waitTime--;
//             continue;
//         }

//         if (!elevator.passengers.empty()) {
//             elevator.direction = elevator.passengers.front().destinationFloor > elevator.currentFloor ? 1 : -1;
//             elevator.currentFloor += elevator.direction;

//             for (auto it = elevator.passengers.begin(); it != elevator.passengers.end();) {
//                 if (it->destinationFloor == elevator.currentFloor) {
//                     it = elevator.passengers.erase(it);
//                     elevator.capacity--;

//                     // 当有乘客上下电梯时，增加等待时间
//                     elevator.waitTime = 2; // 假设上下电梯需要 2 个时间单位
//                 } else {
//                     ++it;
//                 }
//             }
//         } else {
//             elevator.direction = 0;
//         }

//         // 检查有没有乘客在当前楼层等待电梯
//         auto waitingPassengersAtFloor = waitingPassengers.find(elevator.currentFloor);
//         if (waitingPassengersAtFloor != waitingPassengers.end()) {
//             for (auto it = waitingPassengersAtFloor->second.begin(); it != waitingPassengersAtFloor->second.end();) {
//                 if (elevator.capacity < elevator.maxCapacity) {
//                     if ((it->destinationFloor > it->currentFloor && elevator.direction == 1) ||
//                         (it->destinationFloor < it->currentFloor && elevator.direction == -1)) {
//                         elevator.passengers.push_back(*it);
//                         elevator.capacity++;
//                         it->elevatorId = elevator.id;

//                         // 从等待乘客列表中移除已进入电梯的乘客
//                         it = waitingPassengersAtFloor->second.erase(it);
//                     } else {
//                         ++it;
//                     }
//                 }
//             }
//         }
//     }
// }


bool Building::simulationFinished()
{
    for (const auto &passenger : passengers) {
        if (passenger.remainingRides > 0) {
            return false;
        }
    }
    return true;
}


void Building::runSimulation(int numPassengers, int maxTime)
{
    // 生成乘客
    generatePassengers(numPassengers);

    // 运行仿真
    for (int t = 0; t < maxTime; t++) {
        // 更新乘客状态
        updatePassengers();
        // 更新电梯状态
        updateElevators();
        // 显示仿真信息
        displaySimulationInfo(t);

        for (Elevator &elevator : elevators) {
        // 如果电梯处于高峰期，显示警告信息
        if (elevator.isHighTraffic()) {
           cout << "Warning: Elevator " << elevator.id << " is in high traffic period at time " << t << endl;


        }
        }

        
     

   






        // 对乘客分配电梯的原有代码...
        for (auto &passenger : passengers) {
            //如果乘客不在电梯中
            if (passenger.elevatorId == -1) {
                // 寻找当前乘客最少的电梯

                int recommendedElevatorId = -1;
                for (auto &elevator : elevators) {
                    if (elevator.passengers.size() < 6 && elevator.canReachFloor(passenger.destinationFloor)) {
                        recommendedElevatorId = elevator.id;
                    }
                }
            }
        }

        cout<<"______________________________________________________"<<endl;

        //Sleep(1000);

        if (simulationFinished()) {
            std::cout << "Simulation finished at time: " << t << std::endl;
            break;
        }
    }


    for (const auto& elevator : elevators) {
        std::cout << "Elevator " << elevator.id
                  << " run time: " << elevator.totalRunTime
                  << ", idle time: " << elevator.totalIdleTime << '\n';
    }
    for (const auto& passenger : passengers) {
        std::cout << "Passenger " << passenger.id
                  << " wait time: " << passenger.totalWaitTime << '\n';
    }


}

