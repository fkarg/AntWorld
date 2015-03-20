#ifndef TICKSYSTEM_H
#define TICKSYSTEM_H

#include <vector>
#include <thread>
#include <chrono>

#include <string>
#include <iostream>

// defines the tickInterface - It's only one method so it's not that big a deal
class tickInterface {
public:
    virtual void doTick() = 0;
};

#endif