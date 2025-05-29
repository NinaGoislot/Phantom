#pragma once

class LoopTime
{
private:
    double previousTime{0};
    double currentTime{0};
    double deltaTime{0};
    // double startTime;

public:
    // void initTime();
    // void setTime();
    void updateTime();

    double getDeltaTime() const { return deltaTime; }
    double getTime() const { return currentTime; }
};

inline LoopTime& get_loop_time()
{
    static LoopTime instance;
    return instance;
}