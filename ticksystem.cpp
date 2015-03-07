#include "ticksystem.h"

// the interval of how many seconds are between two ticks (at least)
// float TickControl::interval;

// can't be resolved for whatever the reason, working though
// std::vector<tickInterface*> Ticker;


void TickControl::sleep(unsigned int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds) );
}


void TickControl::Timer() {

    do {

        doTick();
        sleep( (unsigned int) interval * 1000 );

    } while (running);

}


// 'calling' the other Ticks
void TickControl::doTick() {
    // what to do at a Tick?
    for(int k = 0; k < Ticker.size(); k++) {
        std::thread doTicks( (*Ticker[k]).doTick());
        doTicks.detach();
    }
}


// starting the ticks at the given interval
void TickControl::startTicks() {
    running = true;

    std::thread t0(task1);

    t0.join();

    std::thread t1(Timer);

    t1.detach();

}


void TickControl::task1(std::string msg) {

    std::cout << "TickSystem: " << msg << std::endl;

}

void TickControl::task1() {
    std::cout << "Ticksyste: second task1" << std::endl;
}


// pausing the ticks temporary
void TickControl::pauseTicks() {
    running = false;
}


// setting the state of 'running' to @param newState
void TickControl::setState(bool newState) {
    running = newState;
}


// resetting - whatever
void TickControl::reset() {
    // FIXME: dunno what to do yet
}


// setting the @param interval: new interval - must be bigger than zero
void TickControl::setInterval(float interval) {
    TickControl::interval = interval;
}


// adding a @param newTick: new object to get 'ticked'
void TickControl::addTicker(tickInterface *newTick) {
    Ticker.push_back(newTick);
}


// returns if the TickSystem is currently running
bool TickControl::isRunning() {
    return running;
}


// returns the currently set interval
float TickControl::getInterval() {
    return interval;
}

// returns of how many ticks there have been since the last reset
int TickControl::getTickCount() {
    return tickCount;
}
