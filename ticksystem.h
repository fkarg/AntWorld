#ifndef TICKSYSTEM_H
#define TICKSYSTEM_H


// defines the tickInterface - It's only one method so it's not that big a deal
class tickInterface {
public:
    virtual void doTick() = 0;
};

class TickControl : public tickInterface {
protected:
    int tickCount = -1;
    bool running = false;
    float interval = 0.2;

public:
    void doTick();
    void startTicks();
    void pauseTicks();
    void reset();
    void setInterval(float interval);
    void getInterval();
    void getTickCount();
};




#endif