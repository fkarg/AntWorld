#ifndef TICKSYSTEM_H
#define TICKSYSTEM_H

#include <vector>
#include <thread>


// defines the tickInterface - It's only one method so it's not that big a deal
class tickInterface {
public:
    virtual void doTick() = 0;
};

/*
 * the TickControl for the tickInterface
 */
class TickControl : public tickInterface {
protected:
    int tickCount = -1, tickerSize = 0;
    bool running = false, started = false;
    float interval = 0.2;
    vector<*tickInterface> Ticker;

    void aspfioh () {
        Ticker.size();
    }

public:
    void doTick();
    void startTicks();
    void pauseTicks();
    void setState(bool newState);
    void reset();
    void setInterval(float interval);
    void addTicker(tickInterface *newTick);

    bool isRunning();
    float getInterval();
    int getTickCount();
};


#endif