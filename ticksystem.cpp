#include "ticksystem.h"


void TickControl::sleep(unsigned int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds) );
}



void TickControl::Timer() {
    time_t startTime;

    while (running) {
        startTime = time(0);
        for (int tickInd = 0; tickInd < toTick.size(); tickInd++) {
            tickInterface* tickInt = toTick[tickInd];
            std::thread tick(tickBuffer, tickInt);
            tick.detach();
        }
        time_t endTime = time(&startTime);

        std::cout << "TickControl: " + std::to_string(endTime) << std::endl;

        sleep(2000);
    }


    // FIXME: Timer
}



void TickControl::tickBuffer(tickInterface *anInterface) {
    anInterface->doTick();
}




void TickControl::doTick() {
    // TODO: what to do at a tick
    std::cout << "TickControl: doing tick!" << std::endl;
}



void TickControl::addTicker(tickInterface *ticker) {
    toTick.push_back(ticker);
}



void TickControl::setRunning(bool run) {
    running = run;
}



void TickControl::start() {
    std::thread ticking(Timer);
    ticking.detach();
}