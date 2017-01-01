#include "Light.hpp"
using namespace std;

void SimpleLight::UpdateLight(int ThisTime){
  int timeDiff=ThisTime>=12?ThisTime-12:12-ThisTime;     //time Diff
  float Lu=1.0;     //luminance
  Lu=1.0-timeDiff/15.0;
//  cout << "timeDiff = " << timeDiff << " Lu = " << Lu << endl;
  glm::vec3 LightColor(Lu,Lu,Lu);
  SetColor(LightColor);
}
