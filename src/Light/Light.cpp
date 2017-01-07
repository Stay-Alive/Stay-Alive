#include "Light.hpp"
using namespace std;

void SimpleLight::UpdateLight(double ThisTime, const glm::vec3& position){
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
    Lu = Lu<0.15?0.15:Lu; //or a special lighting


    glm::vec3 LightColor(Lu,Lu,Lu);
    SetColor(LightColor);

  if(ThisTime>0.33&&ThisTime<0.66){
    float x,y;
    x=LIGHT_HEIGHT*cos(ThisTime*PI);
    y=LIGHT_HEIGHT*sin(ThisTime*PI);
    glm::vec3 lightPosition(x,y,0.0);
    SetPosition(lightPosition);
  }
  else if(ThisTime>0.9||ThisTime<0.3){
    glm::vec3 lightPosition(position.x,15.0f,0.0);
    SetPosition(lightPosition);
    glm::vec3 nightColor(0.6,0.6,0.6);
    SetColor(nightColor);
  }
  else if(ThisTime>0.3){
    glm::vec3 lightPosition(LIGHT_HEIGHT*cos(0.33*PI),LIGHT_HEIGHT*sin(0.66*PI),0.0);
    SetPosition(lightPosition);
  }
}
