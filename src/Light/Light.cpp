#include "Light.hpp"
using namespace std;

void SimpleLight::UpdateLight(double ThisTime){
  double timeDiff=ThisTime>=0.5?ThisTime-0.5:0.5-ThisTime;     //time Diff
  double t=(0.25-timeDiff)*100;
  float Lu=1 / (1 + powf(2, -t));     //luminance
//  Lu=1.0-timeDiff/15.0;
//  cout << "timeDiff = " << timeDiff << " Lu = " << Lu << endl;
  glm::vec3 LightColor(Lu,Lu,Lu);
  SetColor(LightColor);
}
