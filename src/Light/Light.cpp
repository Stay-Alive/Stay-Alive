#include "Light.hpp"
using namespace std;

void SimpleLight::UpdateLight(double ThisTime){
  double t;
  float Lu;
  if(ThisTime<0.5){
    t=(ThisTime - 0.25)*100;
    Lu =1 / (1 + powf(2, -t));     //luminance
  }
  else{
    t=(ThisTime - 0.85)*100;
    Lu =1 - 1 / (1 + powf(2, -t));     //luminance
  }

  if(ThisTime>0.33&&ThisTime<0.66){
    float x,y;
    x=LIGHT_HEIGHT*cos(ThisTime*PI);
    y=LIGHT_HEIGHT*sin(ThisTime*PI);
    glm::vec3 lightPosition(x,y,0.0);
    SetPosition(lightPosition);
//    cout << " x = " << x << " y = " << y << endl;
  }
  else if(ThisTime>0.9){
    glm::vec3 lightPosition(LIGHT_HEIGHT*cos(0.33*PI),LIGHT_HEIGHT*sin(0.66*PI),0.0);
    SetPosition(lightPosition);
  }

//  Lu=1.0-timeDiff/15.0;
//  cout << "ThisTime " << ThisTime << "t = " << t << " Lu = " << Lu << endl;
  glm::vec3 LightColor(Lu,Lu,Lu);
  SetColor(LightColor);
}
