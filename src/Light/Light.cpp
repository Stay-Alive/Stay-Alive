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
//  Lu=1.0-timeDiff/15.0;
//  cout << "ThisTime " << ThisTime << "t = " << t << " Lu = " << Lu << endl;
  glm::vec3 LightColor(Lu,Lu,Lu);
  SetColor(LightColor);
}
