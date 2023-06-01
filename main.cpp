#include "Building.h"
#include <windows.h>
#include <ctime>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    // 初始化随机数生成器
    std::srand(std::time(0));

    // 设定参数
    int numElevators = 10;
    int maxCapacity = 15;
    int numPassengers = 100;
    int maxTime = 100;

    // 创建建筑物对象
    Building building(numElevators, maxCapacity,numPassengers);

    // 运行仿真
    building.runSimulation(numPassengers, maxTime);
    
    system("pause");
    
    return 0;
}
