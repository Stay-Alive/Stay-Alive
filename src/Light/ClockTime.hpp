#ifndef ClockTIME_H
#define ClockTIME_H

#include "../config.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

class ClockTime
{
public:
    ClockTime():ThisHour(12), ThisDay(1), pause(false){}
    ~ClockTime(){};

    inline int GetHour(){
      currentTime = glfwGetTime();
      int DayTime=currentTime/CLOKC_HOUR;
      ThisHour=(12+DayTime)%24;
      return ThisHour;
    };

    inline int GetDay(){
      currentTime = glfwGetTime();
      ThisDay=currentTime/(CLOKC_HOUR*24);
      return ThisDay;
    }

    inline void PauseTime(bool pause){
	     this->pause=pause;
	  }

private:
    int ThisHour;
    int ThisDay;
    bool pause;
//    static double previousTime = glfwGetTime();  // Set the initial time to now
    double currentTime;
    const int InitHour=12;
};

#endif
