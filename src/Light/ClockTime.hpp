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
    ~ClockTime(){
      glfwSetTime(0);
    };

    inline int GetHour(){
      if(pause==false)
        currentTime = glfwGetTime();
      int DayTime=currentTime/CLOKC_HOUR;
      ThisHour=(12+DayTime)%24;
      return ThisHour;
    };

    inline double GetTimeofDay(){
      if(pause==false)
        currentTime=glfwGetTime();
      double DayTime=currentTime/(CLOKC_HOUR*24.0)+0.5;
      return DayTime=DayTime-(int)DayTime;
    }

    inline int GetDay(){
      if(pause==false)
        currentTime = glfwGetTime();
      ThisDay=(InitHour+currentTime)/(CLOKC_HOUR*24);
      return ThisDay;
    }

    inline void PauseTime(bool pause){
	     this->pause=pause;
       if(this->pause==true)
         currentTime = glfwGetTime();
       else
        glfwSetTime(currentTime);
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
